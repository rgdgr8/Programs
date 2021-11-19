#!/bin/bash

read -p "Enter filename: " fn
echo "Do want to replace a regex pattern or a normal string? "
select opt in Regex 'Normal String'; do
	break
done
read -p "Enter $opt to be replaced: " p1
read -p "Enter string to be replaced with: " p2

if [ ! -r "$fn" ];then
	echo 'File is either non-existent or unreadable'
	exit 1
fi

c=0
while read line; do
	for w in $line; do
		if [ "$opt" = Regex ];then
			if [[ "$w" =~ $p1 ]]; then
				((c+=1))
			fi
		else
			if [ "$w" = "$p1" ]; then
				((c+=1))
			fi
		fi
	done
done < "$fn"

if [ "$c" -lt 1 ]; then
	echo "No such $opt found"
	exit 0
else
	echo "$c matches found"
fi

sed -E -i '' "s/$p1/$p2/g" $fn
