#!/bin/bash
source ./test/test_functions.sh

# Tokenizer
## 5_1.Unquoted word
assert 'ls /'
assert 'echo hello world'
assert 'echo hello 	world'
assert 'echo hello world	'
assert 'echo hello world 	'
assert 'nosuchfile\n\n'
assert 'echo hello           world'
## [NG]
# assert 'echo hello		world'
# assert 'echo hello\tworld'
