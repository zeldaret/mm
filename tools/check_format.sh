#!/bin/bash

usage () {
    echo "Usage: $0 [-j jobs]"
}

jobs=1

while getopts "j:" opt
do
    case $opt in
    j)  j_option_arg="$OPTARG"
        if [[ ! "${j_option_arg}" =~ ^[0-9]*$ ]]
        then
            echo "Error: Option '-j' expects numeric argument, you gave: ${j_option_arg}"
            exit 1
        fi
        jobs="$j_option_arg"
        ;;
    ?)  usage
        exit 2
        ;;
    esac
done
shift $(($OPTIND - 1))


STATUSOLD=`git status --porcelain`
./format.py -j$jobs
if [ $? -ne 0 ]
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
