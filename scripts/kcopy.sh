#!/usr/bin/env bash

FILE="$1"
OUT="$2"
seed="$(dd if=/dev/random bs=6 count=1 2>/dev/null | md5sum | base64 | head -c 8)"
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"

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

Magic="Anivice"
Ssize=$(((1217-18)*512))
Scode=491520
Sdata=90112
Smap=$((Ssize - (Scode + Sdata) - $(echo -n "$Magic" | wc -c)))
DataLoc=$(grep -E '\s+\.\s=\s0x[0-9|A-Z]+;' < "$SCRIPT_DIR/link.ld" | tail -n 1 | sed -E 's/.*(0x.*);/\1/g')

if [[ $((1024*1024+Scode)) -ne $(printf "%d" "$DataLoc") ]];
then
    echo -e "\033[31mERROR: Image data section starts at address $((1024*1024+Scode)) while linker script suggests "
    exit 1
fi

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
printf "\033[32;1mCode resides at address \033[31;1m0x%X\033[32m (%d KB)\033[0m\n" $((1024*1024)) $((Scode/1024))
printf "\033[33;1mData resides at address \033[31;1m0x%X\033[33m (%d KB)\033[0m\n" $((1024*1024+Scode)) $((Sdata/1024))
printf "\033[35;1mSmap resides at address \033[31;1m0x%X\033[35m (%d KB)\033[0m\n" "$(echo "$(printf "%d" "$DataLoc")" + $Sdata | bc)" $((Smap/1024))
printf "\033[36;1mMAGC resides at address 0x%X\033[0m\n" "$(printf "(%d - 7) - 512*18 + 1024*1024\n" $Ssize | bc)"

cat "/tmp/code.${seed}.raw" "/tmp/data.${seed}.raw" > "$OUT"
echo -n "$Magic" >> "$OUT"
rm "/tmp/code.${seed}.raw" "/tmp/data.${seed}.raw" "/tmp/map.${seed}.raw"
