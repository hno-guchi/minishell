#!/bin/bash
source ./test/test_functions.sh

## Mr.usami test case
assert 'exit'
assert 'exit 42'
assert 'exit ""'
assert 'exit hello'
assert 'exit 42Tokyo'
assert 'exit 1 2'

rm a.out cmp exit42 out print_args
