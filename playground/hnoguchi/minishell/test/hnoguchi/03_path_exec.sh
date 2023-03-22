#!/bin/bash

source ./test/test_functions.sh

# Empty line (EOF)
assert ''

# 3.Path Exec
## Absolute path commands without args
assert '/bin/pwd'
assert '/bin/echo'
assert '/bin/ls'
assert 'bin/ls'
assert '/ban/pwd'
assert '/bin/l'
assert '/binls'
assert '/bin/'
assert '/ban'
assert './test'
assert './test/'
assert './test/nofile'
assert './test/sample.txt'
assert './Makefile'

assert '/usr/local/bin/tree'
assert 'usr/local/bin/tree'
assert '/usr/loca/bin/tree'
assert '/usr/local/bin/tre'
assert '/usr/localbin/tre'

assert '/usr/bin/env'
assert 'usr/bin/env'
assert '/us/bin/env'
assert '/usr/bin/ev'
assert '/usrbin/env'

assert '/usr/sbin/lpinfo'
assert 'usr/sbin/lpinfo'
assert '/usr/sin/lpinfo'
assert '/usr/sbin/lpifo'
assert '/usrsbin/lpinfo'

assert '/sbin/ping'
assert 'sbin/ping'
assert '/sin/ping'
assert '/sbin/pig'
assert '/sbinping'
