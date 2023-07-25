#!/bin/bash
source ./test/test_functions.sh

# Signal handling
echo "int main() { while (1) ; }" | gcc -xc -o infinite_loop -

## Signal to shell processes
print_desc "SIGTERM to SHELL"
(sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGTERM minishell) &
# Redirect stderr to suppress signal terminated message
assert './infinite_loop' 2>/dev/null

print_desc "SIGQUIT to SHELL"
# SIGQUIT should not kill the shell
(sleep 0.01; pkill -SIGQUIT bash;
 sleep 0.01; pkill -SIGTERM bash;
# SIGQUIT should not kill the minishell
 sleep 0.01; pkill -SIGQUIT minishell;
 sleep 0.01; pkill -SIGTERM minishell) &
# Redirect stderr to suppress signal terminated message
assert './infinite_loop' 2>/dev/null

print_desc "SIGINT to SHELL"
# SIGINT should not kill the shell
(sleep 0.01; pkill -SIGINT bash;
 sleep 0.01; pkill -SIGTERM bash;
# SIGINT should not kill the minishell
 sleep 0.01; pkill -SIGINT minishell;
 sleep 0.01; pkill -SIGTERM minishell) &
# Redirect stderr to suppress signal terminated message
assert './infinite_loop' 2>/dev/null

## Signal to child processes
print_desc "SIGTERM to child process"
(sleep 0.01; pkill -SIGTERM infinite_loop;
 sleep 0.01; pkill -SIGTERM infinite_loop) &
assert './infinite_loop'

print_desc "SIGINT to child process"
(sleep 0.01; pkill -SIGINT infinite_loop;
 sleep 0.01; pkill -SIGINT infinite_loop) &
# Redirect stderr to suppress signal terminated message
assert './infinite_loop'

print_desc "SIGQUIT to child process"
(sleep 0.01; pkill -SIGQUIT infinite_loop;
 sleep 0.01; pkill -SIGQUIT infinite_loop) &
assert './infinite_loop'

print_desc "SIGUSER1 to child process"
(sleep 0.01; pkill -SIGUSR1 infinite_loop;
 sleep 0.01; pkill -SIGUSR1 infinite_loop) &
assert './infinite_loop'

# Manual Debug
# $ ./minishell
# $ 
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ hogehoge
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF
# >
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF
# > hoge
# > fuga
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
