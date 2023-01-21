#!/bin/bash
set -e

# This script can be used when you want to test locally the amount of warnings produced by your changes before doing a PR.

# Terminal colour codes
# when $TERM is empty (non-interactive shell), then expand tput with '-T xterm-256color'
[[ ${TERM}=="" ]] && TPUTTERM='-T dumb' \
                  || TPUTTERM=''

declare -r BOLD=`tput ${TPUTTERM} bold`
declare -r RED=`tput ${TPUTTERM} setaf 1`
declare -r PURPLE=`tput ${TPUTTERM} setaf 5`
declare -r WHITE=`tput ${TPUTTERM} setaf 7`
declare -r BLINK=`tput ${TPUTTERM} blink`
declare -r RST=`tput ${TPUTTERM} sgr0`


DIR="$(dirname "$(readlink -f "$0")")"
cd "$DIR/../.."

COMPARE_WARNINGS="$DIR/compare_warnings.sh"

usage () {
    echo "Usage: $0 [-h] [-j jobs]"
}

show_help () {
    usage
    echo "
Check for new warnings created. 

Optional arguments:
    -h    Display this message and exit.
    -f    Run full build process
    -j N  use N jobs (does not support plain -j because you shouldn't use it anyway)
"
}

jobs=1
full=
run="make clean
    make uncompressed"



while getopts "hfj:" opt
do
    case $opt in
    h)  show_help
        exit 0
        ;;
    f)  full="true"
        run="make distclean
    make setup
    make disasm
    make all"
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
    $run
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

if [[ $full ]]; then
    make distclean
    make_warnings setup setup
    make_warnings disasm disasm
    make_warnings all build
else
    make clean
    make_warnings uncompressed build
fi


if [[ $full ]]; then
    $COMPARE_WARNINGS setup
    $COMPARE_WARNINGS disasm
fi
$COMPARE_WARNINGS build

