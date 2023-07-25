#!/bin/bash
source ./test/test_functions.sh

## Expand variable
assert 'echo $USER'
assert 'echo hello$USER'
assert 'echo $USERhello'
assert 'echo $NOT'
assert 'echo $USER$PATH$NOT'
assert 'echo $USER $PATH $NOT'
assert 'echo $NOT$USER$NOT'
assert 'echo $NOT $USER $NOT'
assert 'echo $USER $PATH a$NOT'
assert 'echo $USER $PATH a$NOT a'
assert 'echo "$USER"'
assert 'echo "hello$USER"'
assert 'echo "$USERhello"'
assert 'echo "$NOT"'
assert 'echo $"PATH"'
assert 'echo "$USER$PATH$NOT"'
assert 'echo "$USER $PATH $NOT"'
assert 'echo "$NOT$USER$NOT"'
assert 'echo "$NOT $USER $NOT"'
assert 'echo "$USER $PATH a$NOT"'
assert 'echo "$USER $PATH a$NOT a"'
## sola_tester
assert 'echo test         test'
assert "echo \"test"
assert 'echo $TEST'
assert "echo \"$TEST\""
assert "echo \"'$TEST'"
assert "echo \"$TEST$TEST$TEST\""
assert "echo \"$TEST$TEST=lol$TEST\""
assert "echo \"   $TEST lol $TEST\""
assert 'echo $TEST$TEST$TEST'
assert "echo $TEST$TEST=lol$TEST\"\"lol"
assert 'echo    $TEST lol $TEST'
assert "echo test \"\" test \"\" test"
assert "echo \"$TEST\""
assert "echo \"$=TEST\""
assert "echo \"$\""
assert "echo \"$?TEST\""
assert 'echo $TEST $TEST'
assert "echo \"$1TEST\""
assert "echo \"$T1TEST\""

## Special Parameter $?
assert 'echo $?'
assert 'invalid\necho $?\necho $?'
assert 'exit42\necho $?\necho $?'
assert 'exit42\n\necho $?\necho $?'
