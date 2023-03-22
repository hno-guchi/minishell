#!/bin/bash
source ./test/test_functions.sh

# Redirect
## Redirecting output
assert 'echo hello >hello.txt' 'hello.txt'
assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'
assert 'echo >f1' 'f1'
assert 'echo hello >'

## Redirecting input
assert 'cat <Makefile'
echo hello>f1
echo world>f2
echo 42Tokyo>f3
assert 'cat <f1<f2<f3'
rm -f f1 f2 f3
assert 'cat <hoge'
assert 'ls <'

## Appending Redirecting output
assert 'pwd >>pwd.txt' 'pwd.txt'
assert 'pwd >>pwd.txt \n pwd >>pwd.txt' 'pwd.txt'
assert 'echo >>f1' 'f1'
assert 'echo hello >>'
rm -f f1

## Here document
assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
assert 'cat <<E"O"F<<eof\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<'

# REDIRECTIONS(sola tester)
assert 'echo test > ls \n cat ls'
assert 'echo test > ls >> ls >> ls \n echo test >> ls \n cat ls'
assert '> lol echo test lol \n cat lol'
assert '>lol echo > test1>lol>test1>>lol>test1 mdr >lol test1 >test1 \n cat test1'
assert 'cat < ls'
assert 'cat < ls > ls'
