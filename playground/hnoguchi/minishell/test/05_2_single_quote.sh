#!/bin/bash

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
	printf '%-50s:' "[$1]"
	# exit status
	echo -n -e "$1" | bash >cmp 2>&-
	expected=$?
	echo -n -e "$1" | ./minishell >out 2>&-
	actual=$?

	diff cmp out >/dev/null && echo -n '	diff OK' || echo -n '	diff NG'

	if [ "$actual" = "$expected" ]; then
		echo -n '	status OK'
	else
		echo -n "	status NG, expected $expected but got $actual"
	fi
	echo
}

# Tokenizer
## Single quote
assert "./print_args 'hello world' '42Tokyo'"
assert "echo 'hello world' '42Tokyo'"
assert "echo '\"hello world\"' '42Tokyo'"
assert "echo hello'   world'"
## my
assert "echo 'hello world"
assert "echo hello world'"

#[NG] Not treat \t readline();
#assert "echo 'hello	world'"
#assert "echo 'hello world	'"
#assert "echo 'hello world 	'"

cleanup
echo 'all OK'
