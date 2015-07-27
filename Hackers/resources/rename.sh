#!/bin/bash

i=0
for file in $(ls "$1")
do
	echo "Renaming $file to $i.txt"
	mv "$1/$file" "$1/$i.txt"
	i=$(expr "$i" + 1)
done
