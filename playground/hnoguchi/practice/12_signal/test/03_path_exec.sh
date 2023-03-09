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

# Empty line (EOF)
assert ''

# 3.Path Exec
## Absolute path commands without args
assert '/bin/pwd'
assert '/bin/echo'
assert '/bin/ls'
assert 'bin/ls'
assert '/ban/pwd'
assert '/bin/l'
assert '/binls'

assert '/usr/local/bin/tree'
assert 'usr/local/bin/tree'
assert '/usr/loca/bin/tree'
assert '/usr/local/bin/tre'
assert '/usr/localbin/tre'

assert '/usr/bin/env'
assert 'usr/bin/env'
assert '/us/bin/env'
assert '/usr/bin/ev'
assert '/usrbin/env'

assert '/usr/sbin/lpinfo'
assert 'usr/sbin/lpinfo'
assert '/usr/sin/lpinfo'
assert '/usr/sbin/lpifo'
assert '/usrsbin/lpinfo'

assert '/sbin/ping'
assert 'sbin/ping'
assert '/sin/ping'
assert '/sbin/pig'
assert '/sbinping'

cleanup
# echo 'all OK'
