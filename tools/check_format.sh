#!/bin/bash

STATUSOLD=`git status --porcelain`
./format.sh
if [ $? ]
then
   echo "Formatter failed. Exiting."
   exit -1
fi
STATUSNEW=`git status --porcelain`

if [ "${STATUSOLD}" != "${STATUSNEW}" ];
then
    echo ""
    echo "Misformatted files found. Run ./format.sh and verify codegen is not impacted."
    echo ""
    diff --unified=0  --label "Old git status" <(echo "${STATUSOLD}") --label "New git status" <(echo "${STATUSNEW}")
    echo ""
    echo "Exiting."
    exit 1
fi

exit 0
