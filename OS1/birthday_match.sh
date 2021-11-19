#!/bin/bash

read -p "Birth Day 1: "  d1
read -p "Birth Day 2: "  d2

wd1=$(date -j -f '%d/%m/%Y' "$d1" +'%A')
wd2=$(date -j -f '%d/%m/%Y' "$d2" +'%A')

echo "$wd1 $wd2"

if [ "$wd1" = "$wd2" ]
then
		echo 'born on the same day of the week'
else
		echo 'Not born on the same day of the week'
fi

