#!/bin/bash
file=$1

dos2unix ${file}
dos2unix -c mac ${file}

grep -v '     ' ${file} |
    sed -e 's/   //g' |
    grep -vE '",|Hex|ID|Stage|tree|\{|\}|\[|\]|ground|-|[A-Z]{2}|^$|Parts|/|Rnd|[0-9]"|%|#|=|" ' |
    tr -d '"' |
    tr -d ',' |
    tr -d '*' |
    tr -d ' ' |
    tr   ':' ' ' > ${file}"_sedfu"
