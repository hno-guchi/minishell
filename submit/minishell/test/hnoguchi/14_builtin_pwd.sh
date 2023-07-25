#!/bin/bash
source ./test/test_functions.sh

## Mr.usami test case

assert 'pwd'
assert 'cd\npwd'
assert 'cd src\npwd'
assert 'cd /etc\npwd'
assert 'cd . \n pwd \n echo $PWD $OLDPWD'
assert 'cd .. \n pwd \n echo $PWD $OLDPWD'
assert 'cd /// \n pwd \n echo $PWD $OLDPWD'
assert 'cd /tmp/// \n pwd \n echo $PWD $OLDPWD'
assert 'unset PWD\npwd\ncd /etc\npwd'

rm a.out cmp exit42 out print_args
