#!/bin/bash

if [ "$#" -ne 2 ]; then
	echo "Forneça dois números"
	exit 1
fi

echo "$1 $2" > aux.txt

echo -n "gcd($1, $2) = "

~/maratona/resources/bash/gcd < aux.txt

rm aux.txt
