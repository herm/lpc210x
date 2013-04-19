#!/bin/sh
#set -x
sourcedir=$(dirname $(readlink -f $0))
destdir=$1
modulename=lpc210x
if [ -z "$destdir" ]; then
    echo "destination=?"
    exit 1
fi
mkdir -p "$destdir"
cd "$destdir"
git init .
git submodule add "$sourcedir" "$modulename"


cp -i $modulename/config.template config.h
cp -i $modulename/main.template main.cpp
cp -i $modulename/Makefile.template Makefile
cp -i $modulename/.gitignore .gitignore
mkdir debug
git add config.h main.cpp Makefile .gitignore
git commit -m "Created new project"
