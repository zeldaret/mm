#!/usr/bin/env bash
set -eu -o pipefail

if [ "${VERBOSE-}" ]
then
echo "$VERSION"
echo "$DISASM_DIR"
echo "$ASSEMBLE_DIR"
echo "$AS_CMD"
echo "$LD"
set -x
fi

echo Assembling text,data,rodata,bss sections together for each file...
for filebase in `find $DISASM_DIR -name '*.s' -printf '%P\n' | sed -E -n 's/\.(text|data|rodata|bss)\.s$//p' | sort | uniq`
do
    printf '\e[2K%s\r' "${filebase}"
    files=
    for section in text data rodata bss
    do
        file="$DISASM_DIR/$filebase.$section.s"
        if [ -e $file ]
        then
            files="$files $file"
        fi
    done
    mkdir -p $(dirname $ASSEMBLE_DIR/$filebase.o)
    iconv_cmd="iconv -f UTF-8 -t EUC-JP $files"
    asfile_cmd="$AS_CMD -o $ASSEMBLE_DIR/$filebase.o --"
    ( $iconv_cmd | $asfile_cmd ) || (
        echo
        echo Error on assembling:
        echo "$filebase"
        echo Command line:
        echo "$iconv_cmd | $asfile_cmd"
        false
    )
done
echo
echo Assembling done!
