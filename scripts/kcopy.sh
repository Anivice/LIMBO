#!/usr/bin/env bash

FILE="$1"
OUT="$2"
seed="$(dd if=/dev/random bs=6 count=1 2>/dev/null | md5sum | base64 | head -c 8)"

objcopy -O binary --only-section=.text "$FILE" /tmp/code."${seed}".raw
objcopy -O binary --only-section=.data "$FILE" /tmp/data."${seed}".raw

code_size=$(stat "/tmp/code.${seed}.raw" --printf=%s)
data_size=$(stat "/tmp/data.${seed}.raw" --printf=%s)

code_short=$((491136 - code_size))
data_short=$((122752 - data_size))

printf "Kernel code space usage %0.2f%% ($code_size bytes), data space usage %0.2f%% ($data_size bytes)\n" \
    "$(echo "scale=4; $code_size / 491136 * 100" | bc)" "$(echo "scale=4; $data_size / 122752 * 100" | bc)"

dd if=/dev/zero bs=$code_short count=1 >> "/tmp/code.${seed}.raw" 2>/dev/null
dd if=/dev/zero bs=$data_short count=1 >> "/tmp/data.${seed}.raw" 2>/dev/null

cat "/tmp/code.${seed}.raw" "/tmp/data.${seed}.raw" > "$OUT"
rm "/tmp/code.${seed}.raw" "/tmp/data.${seed}.raw"
