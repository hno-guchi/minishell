#!/bin/bash
source ./test/test_functions.sh

## Mr.usami test case
assert 'env' # order of variables, default variables differs...
assert 'env | grep hoge | sort'

rm a.out cmp exit42 out print_args
