#!/bin/bash

if [ $# -eq 1 ] && ([ $1 == "-d" ] || [ $1 == "--debug" ])
then
	FLAGS=""
	FLAGS_DEBUG="-g -g3 -ggdb -ggdb3"
	export DEBUG="yes"
	echo -e "\033[01;31mMode debug on !!!\n\033[00m"
else
	FLAGS="-O2"
	FLAGS_DEBUG=""
	export DEBUG="no"
fi

FLAGS="-w -Wall -Wextra -Werror ${FLAGS}"
LINKS="-L../ -lObjects"
INCLUDE="-I../include"

CC=0
CXX=1
LANGUAGES=("c" "cpp")
COMPILER=("gcc" "g++")

OBJECTS=("Bool" "Char" "Buffer" "String")

NB_OBJECTS=${#OBJECTS[@]}
NB_LANGUAGES=${#LANGUAGES[@]}
RELEASE="Release"


make -C .. re && make -C .. clean

echo -e "\n\033[01;33mBegining of compilations :\n"

if [ ! -e $RELEASE ]
then
	mkdir $RELEASE
fi

for ((j=0; j < $NB_LANGUAGES; ++j))
do
	if [ ! -e "${RELEASE}/${LANGUAGES[$j]}" ]
	then
		mkdir "${RELEASE}/${LANGUAGES[$j]}"
	fi
done

for ((i=0; i < $NB_OBJECTS; ++i))
do
	for ((j=0; j < $NB_LANGUAGES; ++j))
	do
		BINARY_NAME="${RELEASE}/${LANGUAGES[$j]}/${OBJECTS[$i]}.exe"
		if [ -f $BINARY_NAME ]
		then
			rm $BINARY_NAME
		elif [ -e $BINARY_NAME ]
		then
			echo -e "\033[01;31mWarning ! ${BINARY_NAME} already exists but isn't a file !\033[00m"
			continue
		fi
		SRC="Objects/${OBJECTS[$i]}/main.${LANGUAGES[$j]}"
		if [ -f "$SRC" ]
		then
			OBJ="main.o"
			echo -e "\033[01;32mCompile ${BINARY_NAME} with ${COMPILER[${j}]} !\033[01;31m"
			${COMPILER[${j}]} $FLAGS $INCLUDE $FLAGS_DEBUG -c $SRC
			${COMPILER[${j}]} $LINKS -o $BINARY_NAME $OBJ
			rm -f $OBJ
		fi
	done
done

echo -e "\033[01;00m"
