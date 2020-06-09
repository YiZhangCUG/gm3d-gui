#!/bin/bash

if [[ ${1} == "configure" && ! -d "build/" ]]; then
	mkdir build && cd build && rm -rf * && cmake ..
elif [[ ${1} == "configure" ]]; then
	cd build && rm -rf * && cmake ..
elif [[ ${1} == "build" ]]; then
	cd build && make
elif [[ ${1} == "install" ]]; then
	cd build && make install
fi