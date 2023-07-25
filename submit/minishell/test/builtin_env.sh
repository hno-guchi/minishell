#!/bin/bash
export print_diff=0
source ./test/test_functions.sh

print_desc "Output of 'env' differs, but it's ok."
assert 'env' # order of variables, default variables differs...
assert 'env | grep hoge | sort'

export ASDF1=1
assert 'env | sort'
unset ASDF1

export ASDF1=
assert 'env | sort'
unset ASDF1

export ASDF1=1 ASDF2=2
assert 'env | sort'
unset ASDF1 ASDF2

export ASDF1= ASDF2=2
assert 'env | sort'
unset ASDF1 ASDF2

export ASDF1 ASDF2
assert 'env | sort'
unset ASDF1 ASDF2

export ASDF1 ASDF2
assert 'env | env | env | sort'
unset ASDF1 ASDF2

unset print_diff
