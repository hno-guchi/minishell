#!/bin/bash
source ./test/test_functions.sh

source ./test/builtin_cd.sh
source ./test/builtin_echo.sh
source ./test/builtin_env.sh
source ./test/builtin_exit.sh
source ./test/builtin_export.sh
source ./test/builtin_pwd.sh
source ./test/builtin_unset.sh
source ./test/builtin_exit.sh

rm a.out cmp exit42 out print_args
