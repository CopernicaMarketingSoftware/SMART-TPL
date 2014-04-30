#!/bin/bash

OUTPUT=chainedmodifiers.tpl

echo -n "{\$name" > "$OUTPUT"

# Clang is smart enough to limit the bracket nesting level to something sane
# like 256 by default. But it allows you to increase it (I haven't done this)
# gcc doesn't limit this and will just crash once it hits about 32.000

for i in {1..16128}
#for i in {1..127}
do
  echo -n "|toupper|tolower" >> "$OUTPUT"
done

echo -n "}" >> "$OUTPUT"
