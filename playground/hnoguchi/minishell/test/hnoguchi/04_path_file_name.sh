#!/bin/bash
source ./test/test_functions.sh

# 4.Path Filename
## Search command path without args
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'
assert 'ping'
assert 'lpinfo'
assert 'tree'
assert 'k'

## No such command
assert 'a.out'
assert 'nosuchfile'
assert 'eco'
