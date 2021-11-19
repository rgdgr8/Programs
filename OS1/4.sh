#!/bin/bash

dfs(){
	for i in $1; do
		if [ -f $i ]; then
			echo $i
			((count=count+1))
		else
			cd $i
			local x=$(ls)
			dfs "$x"
			cd ..
		fi
	done
}

cfs=$(ls)
#echo "$cfs"
count=0
dfs "$cfs"
echo "$count"
