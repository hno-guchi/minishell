#!/bin/bash
source ./test/test_functions.sh

## usami test case
assert 'export | grep No_such | sort'
assert 'export No_such\n export | grep No_such | sort'
assert 'export No_such=Fuga\n export | grep No_such | sort'
assert 'export No_such=Fuga Hoge=No_such\n export | grep No_such | sort'
assert 'export [invalid]'
assert 'export [invalid_No_such]\n export | grep No_such | sort'
assert 'export [invalid]=No_such\n export | grep No_such | sort'
assert 'export [invalid] No_such Hoge=No_such\n export | grep No_such | sort'
assert 'export No_such [invalid] Hoge=No_such\n export | grep No_such | sort'
assert 'export No_such Hoge=No_such [invalid]\n export | grep No_such | sort'
assert 'export No_such="No_such2=Hoge"\nexport $No_such\n export | grep No_such | sort'
## hnoguchi test case
assert 'export Test1\n export | grep Test | sort'
assert 'export Test2=\n export | grep Test | sort'
assert 'export Test2\n export | grep Test | sort'
assert 'export "Test3"\n export | grep Test | sort'
assert 'export "Test4="\n export | grep Test | sort'
assert 'export "Test4"\n export | grep Test | sort'
assert 'export Test5=value\n export | grep Test | sort'
assert 'export Test5=\n export | grep Test | sort'
assert 'export Test5\n export | grep Test | sort'
assert 'export Test5=value\n export | grep Test | sort'
assert 'export Test5\n export | grep Test | sort'

rm a.out cmp exit42 out print_args
