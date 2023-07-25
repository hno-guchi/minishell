#!/bin/bash
source ./test/test_functions.sh

export print_diff=0

assert 'exit'
assert 'exit 1'
assert 'exit -1'
assert 'exit 0'
assert 'exit asdf'
assert 'exit 123 123'
assert 'exit 123 aaa'
assert 'exit aaa 123'
assert 'exit aaa bbb'
assert 'exit 9223372036854775807' # long max
assert 'exit -9223372036854775808' # long min

assert 'exit 1 | exit 2'
