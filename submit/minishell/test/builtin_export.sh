#!/bin/bash
source ./test/test_functions.sh

export print_diff=0


assert 'export | sort'
# for the above test,
# try:
# echo 'export | sort ' | ./minishell > b
# echo 'export | sort ' | bash > a
# diff -y a b
assert 'env | sort'

assert 'export hoge1 \n env | grep hoge | sort'
assert 'export hoge1= \n env | grep hoge | sort'
assert 'export hoge1=1 \n env | grep hoge | sort'
assert 'export hoge1=1 hoge2=2 \n env | grep hoge | sort'
assert 'export hoge1=1 3hoge=3 hoge2=2 \n env | grep hoge | sort'
assert 'export hoge1=1 hoge2= hoge3=3 \n env | grep hoge | sort'
assert 'export hoge1=1 hoge2= hoge3=3 \n env | grep hoge | sort'
assert 'export hoge1=1 | export hoge2= | hoge3=3 \n env | grep hoge | sort'
