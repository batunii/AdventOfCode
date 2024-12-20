#!/usr/bin/zsh

if [[ -z $1 ]]; then
	echo "No arg supplied"
fi

g++ $1
./a.out
