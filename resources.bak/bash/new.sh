#!/bin/bash
template="$HOME/maratona/maratona.bak/resources/template.cpp"

if [ "$#" -eq 0 ]; then
	echo "Providencie nomes"
	exit 1
fi

for arg in "$@"
do
	if [ ! -f "$arg".cpp ]; then
		cp "$template" "$arg".cpp
	else
		echo "Arquivo já existe"
	fi
done
