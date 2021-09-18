#!/bin/bash


# Terminal colour codes
BOLD=`tput bold`
RED=`tput setaf 1`
PURPLE=`tput setaf 5`
WHITE=`tput setaf 7`
BLINK=`tput blink`
RST=`tput sgr0`

read CURRENT_LINES CURRENT <<< $(wc -l "tools/warnings_count/warnings_$1_current.txt")
read NEW_LINES NEW <<< $(wc -l "tools/warnings_count/warnings_$1_new.txt")

if [ $NEW_LINES -le $CURRENT_LINES ]
then
    echo "${BOLD}No new warnings added in $1, well done.${RST}
"
    exit 0
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
    exit 1
fi
