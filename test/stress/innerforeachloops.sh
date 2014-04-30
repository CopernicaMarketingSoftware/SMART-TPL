#!/bin/bash

OUTPUT=innerforeachloops.tpl

# 13 seems to be the max, after that the internal lemon stack will start to overflow

COUNT=13

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