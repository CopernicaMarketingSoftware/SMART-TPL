#!/bin/bash

OUTPUT=innerforeachloops.tpl

# 13 seems fine with a lemon stack of 100
# 142 seems to be the max with a lemon stack of 1000

COUNT=142

cat /dev/null > "$OUTPUT"

for i in `seq 1 $COUNT`
do
  echo "{foreach \$map as \$key$i => \$value$i}" >> "$OUTPUT"
  echo "Key: {\$key$i}" >> "$OUTPUT"
  echo "Value: {\$value$i}" >> "$OUTPUT"
done

for i in `seq 1 $COUNT`
do
  echo "{/foreach}" >> "$OUTPUT"
done
