#!/bin/bash
set -e

# This script can be used when you want to test locally the amount of warnings produced by your changes before doing a PR.

# Terminal colour codes
BOLD=`tput bold`
RED=`tput setaf 1`
PURPLE=`tput setaf 5`
WHITE=`tput setaf 7`
BLINK=`tput blink`
RST=`tput sgr0`


DIR="$(dirname "$(readlink -f "$0")")"
cd "$DIR/../.."

usage () {
    echo "Usage: $0 [-h] [-j jobs]"
}

show_help () {
    usage
    echo "
Check for new warnings created. 

Optional arguments:
    -h    Display this message and exit.
    -j N  use N jobs (does not support plain -j because you shouldn't use it anyway)
"
}

jobs=1

while getopts "hj:" opt
do
    case $opt in
    h)  show_help
        exit 0
        ;;
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

# Confirm run with -j jobs
echo "This will run
    make distclean
    make setup
    make disasm
    make all
using $jobs threads. This may take some time."
read -r -p "Is this okay? [Y/n]" response
response=${response,,} # tolower
if !([[ $response =~ ^(yes|y| ) ]] || [[ -z $response ]]); then
exit 0
fi




remove_ansi_codes () {
    perl -pe '
    s/\e\[[\x30-\x3f]*[\x20-\x2f]*[\x40-\x7e]//g;
    s/\e[PX^_].*?\e\\//g;
    s/\e\][^\a]*(?:\a|\e\\)//g;
    s/\e[\[\]A-Z\\^_@]//g;' $1
}


make_warnings () {
    make $1 -j$jobs 2> >(tee tools/warnings_count/warnings_temp.txt) \
    && remove_ansi_codes tools/warnings_count/warnings_temp.txt > tools/warnings_count/warnings_$2_new.txt \
    && rm tools/warnings_count/warnings_temp.txt
}

compare_warnings () {
    read CURRENT_LINES CURRENT <<< $(wc -l "tools/warnings_count/warnings_$1_current.txt")
    read NEW_LINES NEW <<< $(wc -l "tools/warnings_count/warnings_$1_new.txt")

    if [ $NEW_LINES -le $CURRENT_LINES ]
    then
        echo "${BOLD}No new warnings added in $1, well done.${RST}
"
        return 0
    else
        CURRENT_NUM=$(grep -i 'warning' $CURRENT | wc -l)
        NEW_NUM=$(grep -i 'warning' $NEW | wc -l)
        EXTRA_NUM=$(( $NEW_NUM - $CURRENT_NUM ))

        echo "${BOLD}${RED}There are $EXTRA_NUM new warnings in $1, please fix them!${RST}
${BOLD}Current warnings:${RST}"
        cat $CURRENT
        echo "${BOLD}
Total current warnings: $CURRENT_NUM

New warnings:${RST}"
        cat "$NEW"
        echo "${BOLD}
Total new warnings: $NEW_NUM ${RED}
Total extra warnings: $EXTRA_NUM ${RST}
${BOLD}
If these warnings are needed to produce a matching build, run 'tools/warnings_count/update_current_warnings.sh' and commit the updated files in 'tools/warnings_count/'.${RST}"
        return 1
    fi
}

make distclean
make_warnings setup setup
make_warnings disasm disasm
make_warnings all build

echo "
$(tput setaf 3)(lots of make output here...) 
$RST"
compare_warnings setup
compare_warnings disasm
compare_warnings build

