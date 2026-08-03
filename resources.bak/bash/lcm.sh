#!/bin/bash

if [ "$#" -ne 2 ]; then
	echo "Forneça dois números inteiros"
	exit 1
fi

echo "$1 $2" > aux.txt

echo -n "lcm($1, $2) = "

~/maratona/resources/bash/lcm < aux.txt

rm aux.txt
