#!/bin/bash

#runs test nothing 
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl
make ifdeftest

gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D WRAP
make ifdeftest

gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D WRAPTWO
make ifdeftest

gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D WRAPMAX
make ifdeftest

gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D WRAPOVER
make ifdeftest
