#!/bin/bash



### Configure shell and bootstrap
#
set -e
set -u
. `dirname $BASH_SOURCE`/_bootstrap.sh



### Get data
#
MY_COMM=$(basename $SNOOPY_TEST_FILTER)
if ! $SNOOPY_TEST_FILTER   "msg"   "exclude_comm"   "$MY_COMM,aaaa,bbbb" > /dev/null; then
    snoopy_testResult_pass
else
    snoopy_testResult_fail "My COMM: $MY_COMM"
fi
