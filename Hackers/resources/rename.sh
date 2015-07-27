#!/bin/bash

echo "Preparing..."
i=0
for file in $(ls "$1")
do
	mv "$1/$file" "$1/_$file.txt"
	i=$(expr "$i" + 1)
done

echo "Renaming..."
i=0
for file in $(ls "$1")
do
        mv "$1/$file" "$1/$i.txt"
        i=$(expr "$i" + 1)
done
