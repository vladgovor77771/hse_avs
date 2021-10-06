#!/bin/bash

if test -f bin/app.out; then
    for filename in ./tests/*.in; do
        cat $filename | ./bin/app.out > "${filename}.realout" 2> /dev/null
        if cmp "${FILE%%.*}.out" "${filename}.realout" 2> /dev/null; then
            echo "Test $filename fails!!!"
            echo "Expected:"
            cat "${FILE%%.*}.out"
            echo "Got:"
            cat "${filename}.realout"
        else
            echo "Test $filename successed"
        fi
        rm "${filename}.realout"
    done
else
    echo "No executable found. Make first!"
fi