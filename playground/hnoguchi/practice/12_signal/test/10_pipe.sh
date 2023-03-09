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

## Pipe
assert 'cat Makefile | grep minishell'
assert 'cat | cat | ls\n\n'
assert 'cat Makefile | notcommand'
assert 'notcommand | cat Makefile'
assert 'notcommand | notcommand '
assert 'cat Makefile | grep mini | wc -l'
assert 'notcommand | cat Makefile | grep mini | wc -l'
assert 'cat Makefile | notcommand | grep mini | wc -l'
assert 'cat Makefile | grep mini | notcommand | wc -l'
assert 'cat Makefile | grep mini | wc -l | notcommand'
assert 'cat Makefile | cat | cat | ls '
assert 'cat <Makefile | grep minishell >f1'
assert 'cat <Makefile | grep minishell | wc -l >>f1'
# assert 'cat <<EOF | grep minishell | wc -l >>f1'
rm -f f1

cleanup
# echo 'all OK'
