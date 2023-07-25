#!/bin/bash
source ./test/test_functions.sh

## Mr.usami test case
assert 'cd'
assert 'cd .'
assert 'cd ..'
assert 'cd ///'
assert 'cd /tmp'
assert 'cd /tmp/'
assert 'cd /tmp///'
assert 'cd /../../../././.././'
assert 'cd src'

assert 'cd \n echo $PWD'
unset HOME
assert 'cd \n echo $PWD'
assert 'cd .\n echo $PWD'
assert 'cd ..\n echo $PWD'
assert 'cd ///\n echo $PWD'
assert 'cd /tmp\n echo $PWD'
assert 'cd /tmp/\n echo $PWD'
assert 'cd /tmp///\n echo $PWD'
assert 'cd /../../../././.././\n echo $PWD'
assert 'cd src\n echo $PWD'

rm a.out cmp exit42 out print_args
