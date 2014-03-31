#!/bin/bash

#ptmin
list1="0 200 300 500"
#list1="0"
#list2="5.5 100.0"
list2="5 100"

for file2 in $list2
do

	for file1 in $list1
	do

            #for iterator in {1..2}
            #do
 
                  #echo "qsub 2run_Boost.sh "$file1" "$file2" "$iterator
                  #qsub -q qcd.q 2run_Boost.sh $file1 $file2 $iterator
                  echo "qsub 2run_Boost.sh "$file1" "$file2
                  qsub -q qcd.q 2run_Boost.sh $file1 $file2

            #done
	done

	#sleep 240
	#sleep 190

done

echo '!! Done All !!'
