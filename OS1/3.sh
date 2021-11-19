read -p "Enter a filename: " fn

if [[ (! -r $fn) ]]; then
	echo 'File is either non-existent or unreadable'
fi

count=0
while read line
do
	((count=$count+1))
done < $fn

echo $count
