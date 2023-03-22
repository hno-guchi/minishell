#!/bin/bash
source ./test/test_functions.sh

# Tokenizer
## Single quote
assert "./print_args 'hello world' '42Tokyo'"
assert "echo 'hello world' '42Tokyo'"
assert "echo '\"hello world\"' '42Tokyo'"
## my
assert "echo '\"hello world\"' '42Tokyo'I am'kinnikunn!'a'a'a'a'"
assert "echo '\"hello world\"' '42Tokyo'\"I am\"'\"kinnikunn\"'a'a'a'a'"
assert "echo '\"hello world\"' '42Tokyo'\"I am\"'\"kinnikunn\"'a'a'a'a"
assert "echo 'hello world"
assert "echo hello world'"
assert "echo ''a"
assert "echo '' a"
assert "echo ' 'a"
assert "echo ' ' a"
assert "'"
