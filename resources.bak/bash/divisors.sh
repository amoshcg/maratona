#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Forneça um número inteiro"
	exit 1
fi

echo "$1" > aux.txt

echo -n "divisors($1) = "

~/maratona/resources/bash/divisors < aux.txt

rm aux.txt
