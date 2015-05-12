#!/bin/bash
file=$1

dos2unix $file
dos2unix -c mac $file

grep -vE '     ' field_statss |
    sed -e 's/   //g' |
    grep -vE '",|Hex|ID|Stage|tree|\{|\]|\[|ground|-|TEX|MC|MT|TT|MS|SP|GI|#|DH|BE|^$|\}|TI|AM|NN|Parts|SH|HS|BC|WA|TO|/|Rnd|TR|0"|1"|2"|3"|4"|5"|6"|7"|8"|9"|RE|MI|PU|GG|FG|%%|""|" |AA|=|VV' |
    sed -e 's/"//g' |
    sed -e 's/ //g' |
    sed -e 's/,//g' |
    sed -e 's/:/ /g' |
    sed -e 's/\*\*\*//g' > $file"_sedfu"
