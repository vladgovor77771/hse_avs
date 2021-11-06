#!/bin/bash

for filename in ./tests/*.in; do
    start=$(date +%s%N)
    python3 src/app.py $filename "${filename}.realout"
    end=$(date +%s%N)
    diff=$(($end-$start))
    if cmp "${FILE%%.*}.out" "${filename}.realout" 2> /dev/null; then
        echo "Test $filename fails!!!"
        echo "Expected:"
        cat "${FILE%%.*}.out"
        echo "Got:"
        cat "${filename}.realout"
    else
        echo "Test $filename succeeded. Time elapsed: $diff nanos"
    fi
    if test -f "${filename}.realout"; then
        rm "${filename}.realout"
    fi
done
