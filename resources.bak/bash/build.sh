#!/bin/bash

arg="$1"

echo $arg

# Caso o nome do arquivo não seja providenciado, termina o programa
if [ "$#" -eq 0 ]; then
	echo "Insira o nome do arquivo a ser compilado"
	exit 1
fi

# Caso o arquivo não exista, termina o progama
if [ ! -f "${arg}.cpp" ]; then
	echo "Arquivo inexistente"
	exit 1
fi

# Caso não exista o executável ou o código fonte é mais novo que o executável
if [ ! -f $arg ] || [ "${arg}.cpp" -nt $arg ]
then
	echo "Compilando"
	g++ -std=c++23 -o "$arg" "${arg}.cpp"
else
	echo "O arquivo não sofreu alterações"
	exit 1
fi

# Executa caso a compilação seja bem sucedida
if [ $? -eq 0 ]
then
	echo "Compilacao concluida"
fi
