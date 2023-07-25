#!/bin/bash
source ./test/test_functions.sh

export print_diff=0

assert 'echo'
assert 'echo -n'
assert 'echo asdf'
assert 'echo -n asdf'
assert 'echo -n -n asdf'
assert 'echo -n -nz -n asdf'
assert 'echo asdf -n'
assert 'echo -nz'
assert 'echo -nz asdf'
assert 'echo -nz asdf -n'
assert 'echo -nz asdf -nz'
assert 'echo -nnnnn -nnnn asdf -nz'
assert 'echo -nnnnnz asdf -nz'
assert 'echo -nznnn asdf -nz'
assert 'echo $ASDSDFLSDKJG'

assert 'echo -nnnnnz asdf -nz | echo -nznnn asdf -nz | echo $ASDSDFLSDKJG | echo'
