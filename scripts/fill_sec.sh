#!/usr/bin/env bash

FILE="$1"
OFILE="$2"
SECTORS="$3"
FILESIZE="$(stat "$FILE" --printf=%s)"
DESIRED_SIZE=$((SECTORS * 512))
SHORT=$((DESIRED_SIZE - FILESIZE))

if [[ $SHORT -gt 0 ]]; then
    cp "$FILE" "$OFILE"
    dd if=/dev/zero bs=$SHORT count=1 >> "$OFILE" 2>/dev/null
elif [[ $SHORT -lt 0 ]]; then
    echo "ERROR: $SECTORS * 512 - $FILESIZE == $SHORT < 0"
    exit 1
else
    echo "No resize needed"
fi
