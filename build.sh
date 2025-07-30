#!/bin/bash



gcc -I/usr/local/include/quickjs/  -L/usr/local/lib/quickjs/ -o main src/*.h src/*.c -lm -lquickjs

./main