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
	echo -e -n "$COMMAND" | ./minishell >out 2>&-
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

cleanup
# echo 'all OK'
