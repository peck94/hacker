#!/bin/bash

for file in $(ls emails)
do
	cat "emails/$file" | grep "Subject: " | sed -e 's/^Subject: //'
done
