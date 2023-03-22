#!/bin/bash
source ./test/test_functions.sh

# Tokenizer
## Double quote
assert "echo hello \"world!\""
assert "\""
assert "echo \"\"a"
assert "echo \"\" a"
assert "echo \" \"a"
assert "echo \" \" a"

## Mixed
assert "echo hello'    world'"
assert "echo hello'    world  '\"  42tokyo  \""
# my
assert "echo \"'hello world'\" \"42Tokyo\"'\"I am\"'\"'kinnikunn!'\"\"a\"a\"a\"a"
assert "echo \"hello 'world!'\""
assert "echo 'hello \"42Tokyo!\"'"
assert "echo 'hello'\"42Tokyo'Bonjour'\""
assert "echo '\"'Hello'\",' '\"\"'This is a \"'pen'\""
