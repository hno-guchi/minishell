#!/bin/bash
source ./test/test_functions.sh

export print_diff=0

assert 'pwd'
assert $'cd\npwd'
assert 'cd src\npwd'
assert 'cd /etc\npwd'
assert 'cd . \n pwd \n echo $PWD $OLDPWD'
assert 'cd .. \n pwd \n echo $PWD $OLDPWD'
assert 'cd /// \n pwd \n echo $PWD $OLDPWD'
assert 'cd /tmp/// \n pwd \n echo $PWD $OLDPWD'
assert 'cd /tmp/// | cd . | cd .. | cd ..|cd/// \n pwd \n echo $PWD $OLDPWD'
