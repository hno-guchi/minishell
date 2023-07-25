#!/bin/bash
source ./test/test_functions.sh

## Mr.usami test case
## unset
export hoge fuga=fuga
assert 'unset'
assert 'unset hoge'
assert 'unset fuga'
assert 'unset nosuch'
assert 'unset [invalid]'
assert 'unset hoge fuga'
assert 'unset hoge nosuch fuga'
assert 'unset fuga \n export | echo $fuga'
assert 'unset [invalid] fuga \n echo $fuga'
rm a.out cmp exit42 out print_args
