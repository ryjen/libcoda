#!/bin/bash

function prepare_src_git_dir
{

	cd src 
	if [ -d "$1" ]; then 
		cd $1 && git pull && cd ..
	else
		git clone https://github.com/c0der78/arg3${1}.git $1
	fi
	cd ..
}

prepare_src_git_dir db

prepare_src_git_dir dice

prepare_src_git_dir format

prepare_src_git_dir json

prepare_src_git_dir net

