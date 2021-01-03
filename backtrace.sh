#!/bin/bash

GDB_BINARY=~/.platformio/packages/toolchain-xtensa32/bin/xtensa-esp32-elf-gdb
ELF_FILE=.pio/build/feedc0de_usb/firmware.elf

if [[ ! -x "$GDB_BINARY" ]]
then
    echo Could not find gdb binary: "$GDB_BINARY"
    exit 1
fi

if [[ ! -f "$ELF_FILE" ]]
then
    echo Could not find elf file: "$ELF_FILE"
    exit 1
fi

ls -lah "$ELF_FILE"

PARAMS=()
for i in $@
do
	ADDR="$(echo "$i" | cut -d ":" -f 1)"
	OUTPUT="$($GDB_BINARY --batch $ELF_FILE -ex "set listsize 1" -ex "l *$ADDR" -ex "q")"

        if [[ -z "$OUTPUT" ]]
        then
            echo "${ADDR} gdb empty output"
        else
            echo "${OUTPUT}"
        fi
done
