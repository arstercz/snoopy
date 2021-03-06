#!/bin/bash



### Configure shell and bootstrap
#
set -e
set -u
. `dirname $BASH_SOURCE`/_bootstrap.sh



### Get data
#
MY_COMM=$(basename $SNOOPY_TEST_FILTER)
MY_COMM_A="${MY_COMM}_a"
if ! $SNOOPY_TEST_FILTER   "msg"   "exclude_comm"   "$MY_COMM_A" > /dev/null; then
    snoopy_testResult_fail "My COMM: $MY_COMM"
else
    snoopy_testResult_pass
fi
