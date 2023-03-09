#!/bin/bash

RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
RESET="\033[0m"
OK=$GREEN"OK"$RESET
NG=$RED"NG"$RESET

cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int	main()
{
	printf("hello from a.out\n");
}
EOF

cat <<EOF | gcc -xc -o print_args -
#include <stdio.h>
int	main(int argc, char *argv[])
{
	for (int i = 0; argv[i]; i++)
	{
		printf("argv[%d] = %s\n", i, argv[i]);
	}
}
EOF

cat <<EOF | gcc -xc -o exit42 -
int main() { return 42; }
EOF

print_desc() {
	echo -e $YELLOW"$1"$RESET
}

cleanup() {
	rm -f cmp out a.out print_args exit42 infinite_loop
}

assert() {
	COMMAND="$1"
	shift
	printf '%-50s:' "[$COMMAND]"
	# exit status
	echo -e -n "$COMMAND" | bash >cmp 2>&-
	expected=$?
	for arg in "$@"
	do
		mv "$arg" "$arg"".cmp"
	done
	echo -e -n "$COMMAND" | ./signal >out 2>&-
	actual=$?
	for arg in "$@"
	do
		mv "$arg" "$arg"".out"
	done

	diff cmp out >/dev/null && echo -e -n "	diff $OK" || echo -e -n "	diff $NG"

	if [ "$actual" = "$expected" ]; then
		echo -e -n "	status $OK"
	else
		echo -e -n "	status $NG, expected $expected but got $actual"
	fi
	for arg in "$@"
	do
		echo -n "	[$arg] "
		diff "$arg"".cmp" "$arg"".out" >/dev/null && echo -e -n "$OK" || echo -e -n "$NG"
		rm -f "$arg"".cmp" "$arg"".out"
	done
	echo
}

# Empty line (EOF)
assert ''

# 3.Path Exec
## Absolute path commands without args
assert '/bin/pwd'
assert '/bin/echo'
assert '/bin/ls'

# 4.Path Filename
## Search command path without args
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'
## No such command
assert 'a.out'
assert 'nosuchfile'

# Tokenizer
## Unquoted word
assert 'ls /'
assert 'echo hello     world     '
assert 'echo hello world  '
assert 'echo hello  world'
assert 'echo hello world	'
assert 'echo hello world 	'
assert 'nosuchfile\n\n'

## Single quote
assert "./print_args 'hello world' '42Tokyo'"
assert "echo 'hello world' '42Tokyo'"
assert "echo '\"hello world\"' '42Tokyo'"
## my
assert "echo 'hello world"
assert "echo hello world'"
assert "'"

## Double quote
assert "echo hello \"world!\""
assert "\""

## Mixed
assert "echo hello'    world'"
assert "echo hello'    world  '\"  42tokyo  \""
# my
assert "echo \"hello 'world!'\""
assert "echo 'hello \"42Tokyo!\"'"
assert "echo 'hello'\"42Tokyo'Bonjour'\""
assert "echo '\"'Hello'\",' '\"\"'This is a \"'pen'\""

# Redirect
## Redirecting output
assert 'echo hello >hello.txt' 'hello.txt'
assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'

## Redirecting input
assert 'cat <Makefile'
echo hello>f1
echo world>f2
echo 42Tokyo>f3
assert 'cat <f1<f2<f3'
rm -f f1 f2 f3
assert 'cat <hoge'

## Appending Redirecting output
assert 'pwd >>pwd.txt' 'pwd.txt'
assert 'pwd >>pwd.txt \n pwd >>pwd.txt' 'pwd.txt'

## Here document
assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
assert 'cat <<E"O"F<<eof\nhello\nworld\nEOF\nNOPRINT'

## Pipe
assert 'cat Makefile | grep minishell'
assert 'cat | cat | ls\n\n'
assert 'cat Makefile | notcommand'
assert 'cat Makefile | notcommand | cat | ls'
assert 'cat Makefile | cat | cat | ls '
assert 'notcommand | notcommand '
assert 'notcommand | cat Makefile'
assert 'cat <Makefile | grep minishell >f1'
rm -f f1

## Expand variable
assert 'echo $USER'
assert 'echo hello$USER'
assert 'echo $USERhello'
assert 'echo $NOT'
assert 'echo $USER$PATH$NOT'
assert 'echo $USER $PATH $NOT'
assert 'echo $NOT$USER$NOT'
assert 'echo $NOT $USER $NOT'
assert 'echo $USER $PATH a$NOT'
assert 'echo $USER $PATH a$NOT a'
assert 'echo "$USER"'
assert 'echo "hello$USER"'
assert 'echo "$USERhello"'
assert 'echo "$NOT"'
assert 'echo "$USER$PATH$NOT"'
assert 'echo "$USER $PATH $NOT"'
assert 'echo "$NOT$USER$NOT"'
assert 'echo "$NOT $USER $NOT"'
assert 'echo "$USER $PATH a$NOT"'
assert 'echo "$USER $PATH a$NOT a"'

## Special Parameter $?
assert 'echo $?'
assert 'invalid\necho $?\necho $?'
assert 'exit42\necho $?\necho $?'
assert 'exit42\n\necho $?\necho $?'

# Signal handling
echo "int main() { while (1) ; }" | gcc -xc -o infinite_loop -

## Signal to shell processes
print_desc "SIGTERM to SHELL"
(sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGTERM minishell) &
# Redirect stderr to suppress signal terminated message
assert './infinite_loop' 2>/dev/null

print_desc "SIGQUIT to SHELL"
# SIGQUIT should not kill the shell
(sleep 0.01; pkill -SIGQUIT bash;
 sleep 0.01; pkill -SIGTERM bash;
# SIGQUIT should not kill the minishell
 sleep 0.01; pkill -SIGQUIT minishell;
 sleep 0.01; pkill -SIGTERM minishell) &
# Redirect stderr to suppress signal terminated message
assert './infinite_loop' 2>/dev/null

print_desc "SIGINT to SHELL"
# SIGINT should not kill the shell
(sleep 0.01; pkill -SIGINT bash;
 sleep 0.01; pkill -SIGTERM bash;
# SIGINT should not kill the minishell
 sleep 0.01; pkill -SIGINT minishell;
 sleep 0.01; pkill -SIGTERM minishell) &
# Redirect stderr to suppress signal terminated message
assert './infinite_loop' 2>/dev/null

## Signal to child processes
print_desc "SIGTERM to child process"
(sleep 0.01; pkill -SIGTERM infinite_loop;
 sleep 0.01; pkill -SIGTERM infinite_loop) &
assert './infinite_loop'

print_desc "SIGINT to child process"
(sleep 0.01; pkill -SIGINT infinite_loop;
 sleep 0.01; pkill -SIGINT infinite_loop) &
# Redirect stderr to suppress signal terminated message
assert './infinite_loop'

print_desc "SIGQUIT to child process"
(sleep 0.01; pkill -SIGQUIT infinite_loop;
 sleep 0.01; pkill -SIGQUIT infinite_loop) &
assert './infinite_loop'

print_desc "SIGUSER1 to child process"
(sleep 0.01; pkill -SIGUSR1 infinite_loop;
 sleep 0.01; pkill -SIGUSR1 infinite_loop) &
assert './infinite_loop'

# Manual Debug
# $ ./minishell
# $ 
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ hogehoge
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF
# >
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF
# > hoge
# > fuga
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D

# Builtin
## exit
# assert 'exit'
# assert 'exit 42'
# assert 'exit ""'
# assert 'exit hello'
# assert 'exit 42Tokyo'
# assert 'exit 1 2'

## export
# print_desc "Output of 'export' differs, but it's ok."
# assert 'export' # order of variables, default variables differs...
# assert 'export | grep nosuch | sort'
# assert 'export nosuch\n export | grep nosuch | sort'
# assert 'export nosuch=fuga\n export | grep nosuch | sort'
# assert 'export nosuch=fuga hoge=nosuch\n export | grep nosuch | sort'
# assert 'export [invalid]'
# assert 'export [invalid_nosuch]\n export | grep nosuch | sort'
# assert 'export [invalid]=nosuch\n export | grep nosuch | sort'
# assert 'export [invalid] nosuch hoge=nosuch\n export | grep nosuch | sort'
# assert 'export nosuch [invalid] hoge=nosuch\n export | grep nosuch | sort'
# assert 'export nosuch hoge=nosuch [invalid]\n export | grep nosuch | sort'
# assert 'export nosuch="nosuch2=hoge"\nexport $nosuch\n export | grep nosuch | sort'

## unset
# export hoge fuga=fuga
# assert 'unset'
# assert 'unset hoge'
# assert 'unset fuga'
# assert 'unset nosuch'
# assert 'unset [invalid]'
# assert 'unset hoge fuga'
# assert 'unset hoge nosuch fuga'
# assert 'unset fuga \n export | echo $fuga'
# assert 'unset [invalid] fuga \n echo $fuga'

## env
# print_desc "Output of 'env' differs, but it's ok."
# assert 'env' # order of variables, default variables differs...
# assert 'env | grep hoge | sort'

## cd
# assert 'cd'
# assert 'cd .'
# assert 'cd ..'
# assert 'cd ///'
# assert 'cd /tmp'
# assert 'cd /tmp/'
# assert 'cd /tmp///'
# assert 'cd /../../../././.././'
# assert 'cd src'

# assert 'cd \n echo $PWD'
# unset HOME
# assert 'cd \n echo $PWD'
# assert 'cd .\n echo $PWD'
# assert 'cd ..\n echo $PWD'
# assert 'cd ///\n echo $PWD'
# assert 'cd /tmp\n echo $PWD'
# assert 'cd /tmp/\n echo $PWD'
# assert 'cd /tmp///\n echo $PWD'
# assert 'cd /../../../././.././\n echo $PWD'
# assert 'cd src\n echo $PWD'

cleanup
# echo 'all OK'
