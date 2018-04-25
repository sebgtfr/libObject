#!/bin/bash

if [ $# -eq 2 ]
then
	export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:../"
	./${1}
fi
