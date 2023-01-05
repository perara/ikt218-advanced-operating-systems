#!/bin/bash
MUSL=../build/musl-cross
mkdir -p ../build

if [ ! -d "$MUSL" ] ; then
    git clone https://github.com/richfelker/musl-cross-make.git $MUSL
fi

cat <<EOT >> $MUSL/config.mak
TARGET = i386-linux-musl
OUTPUT = $MUSL/compiler
GCC_VER = 11.2.0
EOT


cd $MUSL && make