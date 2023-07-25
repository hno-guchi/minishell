#!/bin/bash
source ./test/test_functions.sh

export print_diff=0

assert 'echo bb\necho aaa'
