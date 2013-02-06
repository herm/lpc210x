#!/bin/bash
name=$1
if [ "x$name" = "x" ]; then
    echo "Name?"
    exit 1
fi
git mv lpc210x_base.files "$name.files"
git mv lpc210x_base.config "$name.config"
git mv lpc210x_base.creator "$name.creator"
git mv lpc210x_base.includes "$name.includes"
