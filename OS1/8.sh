#!/bin/bash

read -p "Enter filename: " fn
read -p "Enter word: " wrd

echo "$fn"
if [ ! -r "$fn" ];then
	echo 'File is either non-existent or unreadable'
	exit 1
fi

echo "$wrd" | grep " "
if [ $? -eq 0 ]; then
	echo 'Word should not have space(s)'
	exit 1
fi

ln=()
l=0
c=0
while read line; do
	((l=l+1))
	t=0
	for w in $line; do
		if [ "$w" = "$wrd" ]; then
			((c+=1))
			((t+=1))
		fi
	done
	if [ "$t" -gt 0 ]; then
		ln+=("$l")
	fi
done < "$fn"

if [ "$c" -lt 1 ]; then
	echo "No such word found"
	exit 0
fi

echo "Line numbers:"
echo ${ln[@]}
echo "Word count: "
echo "$c"
