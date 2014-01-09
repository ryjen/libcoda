#!/bin/bash

function prepare_src_git_dir
{
	if [ -d "$1" ]; then 
		cd $1 && git pull
	else
		git clone https://github.com/c0der78/arg3${1}.git $1
	fi

}

cd src 

prepare_src_git_dir db

prepare_src_git_dir dice

prepare_src_git_dir format

prepare_src_git_dir json

prepare_src_git_dir net

cd ..
