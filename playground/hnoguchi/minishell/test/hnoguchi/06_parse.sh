#!/bin/bash
source ./test/test_functions.sh

# Parse
# SYNTAX ERROR(sola tester)
assert '\n\n test'
assert '| test'
assert 'echo > <'
assert 'echo | |'
assert '<'
