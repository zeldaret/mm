#!/usr/bin/env bash
set -eu -o pipefail

if [ "${VERBOSE-}" ]
then
echo "$VERSION"
echo "$DISASM_DIR"
echo "$DISASM_BASEROM"
echo "$PYTHON"
set -x
fi

DISASM_DATA_DIR="tools/disasm/$VERSION"
DISASM_FLAGS="--custom-suffix _unknown --sequential-label-names --no-use-fpccsr --no-cop0-named-registers --no-asm-emit-size-directive --asm-end-label endlabel --Mreg-names=o32"
DISASM_FLAGS="$DISASM_FLAGS --config-dir $DISASM_DATA_DIR --symbol-addrs $DISASM_DATA_DIR/functions.txt --symbol-addrs $DISASM_DATA_DIR/variables.txt"

echo Disassembling...
cmd="$PYTHON tools/disasm/disasm.py $DISASM_FLAGS $DISASM_BASEROM -o $DISASM_DIR --split-functions $DISASM_DIR/functions"
echo "$cmd"
$cmd || (
    echo
    echo Error on disassembling.
    false
)
echo Disassembling done.
