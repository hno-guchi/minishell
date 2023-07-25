#!/bin/bash
source ./test/test_functions.sh

export print_diff=0

assert 'unset'
assert 'unset NON_EXISTENT_VARIABLE'

export NULL_VARIABLE=
assert 'unset NULL_VARIABLE'
unset NULL_VARIABLE

export ASDF=1
assert 'unset ASDF'
unset ASDF

assert 'unset INVALID+IDENTIFIER'

assert 'unset 123INVALID'

export ASDF1=1 ASDF2=2
assert 'unset ASDF1 123INVALID ASDF2 \n env | sort'
unset ASDF1 ASDF2

export ASDF1=1 ASDF2=2
assert 'unset 123INVALID ASDF1 ASDF2 \n env | sort'
unset ASDF1 ASDF2

export ASDF1=1 ASDF2=2
assert 'unset ASDF1 ASDF2 123INVALID \n env | sort'
unset ASDF1 ASDF2

export ASDF1=1 ASDF2=ASDF1
assert 'unset $ASDF2 \n env | sort'
unset ASDF1 ASDF2

export ASDF1=1 ASDF2=2 ASDF3=3 ASDF=4
assert 'unset ASDF1 | unset ASDF2 | unsert ASDF3 | unset | unset 123INVALID | unsert ASDF4 \n env | sort'
unset ASDF1 ASDF2
