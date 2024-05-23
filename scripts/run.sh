#!/bin/bash

pkgs='git build-essential pkg-config cmake cmake-data libsdl2-dev libsdl2-gfx-dev assimp-utils libassimp-dev libassimp5 libfreetype6-dev libsdl2-mixer-dev'
install=false
for pkg in $pkgs; do
  status="$(dpkg-query -W --showformat='${db:Status-Status}' "$pkg" 2>&1)"
  if [ ! $? = 0 ] || [ ! "$status" = installed ]; then
    install=true
    break
  fi
done
if "$install"; then
  sudo apt install $pkgs
fi


if [ ! -d "build" ]; then
  mkdir build
fi

cd build
cmake ..
make -j 16
./PP2I
