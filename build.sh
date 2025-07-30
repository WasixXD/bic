#!/bin/bash

gcc -I/usr/local/include/quickjs/ \
    -Wall \
    -L/usr/local/lib/quickjs/ \
    -o main src/*.h src/*.c \
    -lquickjs -lm

./main