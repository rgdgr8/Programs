#!/bin/bash

print_user(){
		read -p "Enter user name: " name
		echo "$name"
}

list_files(){
		read -p "Enter size in bytes: " sz
		echo "Files/Directories with size greater than or equal to ${sz}B are:"
		((sz=sz-1)) #this is done since -size flag of find can only find greater or lesser files, not equal files, with respect to size
		
		: 'echo $sz
		l=($(find . -size +"$sz"c))
		echo ${l[@]}'

		find . -size +${sz}c -print0 | xargs -0 du -sh
}

logfile="logfile.txt"
if [ ! -f "$logfile" ]; then
		touch "$logfile"
fi

view_log(){
	echo "$logfile":
	cat "$logfile"	
}

arr=('Find user' 'List large files' 'Disk usage' 'View Log File' 'Exit')

: 'for((i=0;i<${#arr[*]};i++));do
		echo ${arr[$i]}
done'

select opt in "${arr[@]}" #self-note: this syntax for arr after in is very important
do
		case "$opt" in
						${arr[0]})
										print_user;;
						${arr[1]})
										list_files;;
						${arr[2]})
										echo 'Disk Usage:'
										du -ah;;
						${arr[3]})
										view_log;;
						${arr[4]}) 
										break;;
						*) 
										echo 'Invalid input'
		esac
		echo "$(whoami)%$opt%$(date)" >> "$logfile"
done
