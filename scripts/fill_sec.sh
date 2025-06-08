#!/usr/bin/env bash

FILE="$1"
SECTORS="$2"
FILESIZE="$(stat "$FILE" --printf=%s)"
DESIRED_SIZE=$((SECTORS * 512))
SHORT=$((DESIRED_SIZE - FILESIZE))

if [[ $SHORT -gt 0 ]]; then
    dd if=/dev/zero bs=$SHORT count=1 >> "$FILE" 2>/dev/null
elif [[ $SHORT -lt 0 ]]; then
    echo "ERROR: $SECTORS * 512 - $FILESIZE == $SHORT < 0"
    exit 1
else
    echo "No resize needed"
fi
