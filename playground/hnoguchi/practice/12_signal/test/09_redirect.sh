#!/bin/bash

RED="\033[31m"
GREEN="\033[32m"
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

cleanup() {
	rm -f cmp out a.out print_args
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

# Redirect
## Redirecting output
assert 'echo hello >hello.txt' 'hello.txt'
assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'
assert 'echo hello >f>f>f' 'f'

## Redirecting input
assert 'cat <Makefile'
echo hello>f1
echo world>f2
echo 42Tokyo>f3
assert 'cat <f1<f2<f3'
rm -f f f1 f2 f3
assert 'cat <hoge'

## Appending Redirecting output
assert 'pwd >>pwd.txt' 'pwd.txt'
assert 'pwd >>pwd.txt \n pwd >>pwd.txt' 'pwd.txt'

## Here document
assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
assert 'cat <<E"O"F<<eof\nhello\nworld\nEOF\nNOPRINT'

cleanup
# echo 'all OK'
