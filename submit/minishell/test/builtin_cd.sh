#!/bin/bash
source ./test/test_functions.sh

export print_diff=0

assert 'cd'
assert 'cd .'
assert 'cd ..'
assert 'cd -'
assert 'cd /tmp'
assert 'cd -'
assert 'cd a a a'
assert 'cd . | cd .. | cd - | cd /tmp | cd - | cd a a a'

assert 'cd \n echo $PWD $OLDPWD'
assert 'cd . \n echo $PWD $OLDPWD'
assert 'cd .. \n echo $PWD $OLDPWD'
assert 'cd - \n echo $PWD $OLDPWD'
assert 'cd /tmp \n echo $PWD $OLDPWD'
assert 'cd - \n echo $PWD $OLDPWD'
assert 'cd a a a \n echo $PWD $OLDPWD'
assert 'cd . | cd .. | cd - | cd /tmp | cd - | cd a a a \n echo $PWD $OLDPWD'
