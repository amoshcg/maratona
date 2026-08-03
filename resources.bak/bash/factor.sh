#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Forneça um número inteiro"
	exit 1
fi

echo "$1" > aux.txt

echo -n "factor($1) = "

~/maratona/resources/bash/factor < aux.txt

rm aux.txt
