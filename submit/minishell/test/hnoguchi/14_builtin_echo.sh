#!/bin/bash
source ./test/test_functions.sh

## Mr.usami test case
assert 'echo'
assert 'echo hello'
assert 'echo hello "    " world'
assert 'echo -n'
assert 'echo -n hello'
assert 'echo -n hello world'
assert 'echo hello -n'

## hnoguchi test case
assert 'echo '
assert 'echo ""'
assert 'echo " "'
assert 'echo -nnnnnnnnn nnnnnnn hello world'
assert 'echo -nnnnhellonnnnn nnnnnnn hello world'
assert 'echo hello -nnnnnnnn nnnnnnn world'
assert 'echo hello -nnnn42tokyonnnn nnnnnnn world'
assert 'echo -n-n-n hello'
assert 'echo -nnnnn-n-n hello'
assert 'echo -nnnnn -n-n hello'
assert 'echo -nnnnn -n -n hello'

rm a.out cmp exit42 out print_args
