#!/usr/bin/env bash

FILE="$1"
OUT="$2"
seed="$(dd if=/dev/random bs=6 count=1 2>/dev/null | md5sum | base64 | head -c 8)"

objcopy -O binary --only-section=.text "$FILE" /tmp/code."${seed}".raw
objcopy -O binary --only-section=.data "$FILE" /tmp/data."${seed}".raw
read -r -a array <<< "$(objdump -t liblimbo.so | grep ".text" | awk '{print $1, $NF}' | sort | tr '\n' ' ')"

for ((i=0;i<${#array[@]};i+=2)); do
    echo "${array[i]}" | xxd -r -p | xxd -e | xxd -r >> "/tmp/map.${seed}.raw"
    echo "${array[i+1]}" >> "/tmp/map.${seed}.raw"
done

code_size=$(stat "/tmp/code.${seed}.raw" --printf=%s)
data_size=$(stat "/tmp/data.${seed}.raw" --printf=%s)
map_size=$(stat "/tmp/map.${seed}.raw" --printf=%s)

Scode=491520
Sdata=89600
Smap=32768
DataLoc=0x00178000

code_short=$((Scode - code_size))
data_short=$((Sdata - data_size))
map_short=$((Smap - map_size))

dd if=/dev/zero bs=$code_short count=1 >> "/tmp/code.${seed}.raw" 2>/dev/null
dd if=/dev/zero bs=$data_short count=1 >> "/tmp/data.${seed}.raw" 2>/dev/null

cat "/tmp/map.${seed}.raw" >> /tmp/data."${seed}".raw
dd if=/dev/zero bs=$map_short count=1 >> "/tmp/data.${seed}.raw" 2>/dev/null

printf "Kernel code space usage %0.2f%% ($code_size bytes), data space usage %0.2f%% (data:$data_size [%0.2f%%] + symbol:$map_size [%0.2f%%] bytes)\n" \
    "$(echo "scale=4; $code_size / $Scode * 100" | bc)" "$(echo "scale=4; ($data_size + $map_size) / ($Sdata + $Smap) * 100" | bc)" \
    "$(echo "scale=4; $data_size / $Sdata * 100" | bc)" "$(echo "scale=4; $map_size / $Smap * 100" | bc)"
printf "System map resides at address 0x%X\n" "$(echo "$(printf "%d" $DataLoc)" + $Sdata | bc)"

cat "/tmp/code.${seed}.raw" "/tmp/data.${seed}.raw" > "$OUT"
rm "/tmp/code.${seed}.raw" "/tmp/data.${seed}.raw" "/tmp/map.${seed}.raw"
