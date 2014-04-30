#!/bin/bash

OUTPUT=elseif.tpl

# 31 seems to be the limit, anything higher seems to overflow the lemon stack

COUNT=31

echo "{if true}" > "$OUTPUT"
echo "echo" >> "$OUTPUT"

for i in `seq 1 $COUNT`
do
  echo "{elseif true}" >> "$OUTPUT"
  echo "echo" >> "$OUTPUT"
done

echo "{else}" >> "$OUTPUT"
echo "echo" >> "$OUTPUT"

echo "{/if}" >> "$OUTPUT"