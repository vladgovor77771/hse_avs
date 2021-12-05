#!/bin/bash

if test -f bin/app; then
    for filename in ./tests/*.in; do
        start=$(date +%s%N)
        cat $filename | ./bin/app > "${filename}.realout" 2> /dev/null
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
        rm "${filename}.realout"
    done
else
    echo "No executable found. Make first!"
fi