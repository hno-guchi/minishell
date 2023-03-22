#!/bin/bash
source ./test/test_functions.sh

source ./test/hnoguchi/03_path_exec.sh
source ./test/hnoguchi/04_path_file_name.sh
source ./test/hnoguchi/05_1_unquoted.sh
source ./test/hnoguchi/05_2_single_quote.sh
source ./test/hnoguchi/05_3_double_quote.sh
source ./test/hnoguchi/06_parse.sh
source ./test/hnoguchi/09_redirect.sh
source ./test/hnoguchi/10_pipe.sh
source ./test/hnoguchi/11_expand.sh
source ./test/hnoguchi/12_signal.sh

rm a.out cmp exit42 infinite_loop lol ls out print_args test1
