#!/bin/bash

line='!! Done All !!'
list=`ls BoostedTop.o*`

for file in $list
do

      output=`tail --line=1 $file`
      if [ "${output}" == "${line}" ]; then
            rm -fv ${file}
      fi
done

echo 'Done All'
