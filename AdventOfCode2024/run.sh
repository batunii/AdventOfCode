#!/usr/bin/zsh

if [[ -z $1 ]]; then
	echo "No arg supplied"
fi

gcc $1
./a.out
