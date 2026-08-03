#!/bin/bash

nome_arquivo="$1"

if [ "$#" -eq 0 ]
then
	echo "Digita o nome do arquivo fdp"
	exit 1
fi

arquivos_teste=( $(ls | grep "^$nome_arquivo" | grep '\.in') )

for arquivo in "${arquivos_teste[@]}"
do
	echo "caso teste: $arquivo"
	./a.out < "$arquivo"
	echo
done
