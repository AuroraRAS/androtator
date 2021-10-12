#!/bin/sh

cd Hamlib

#help us get "hamlibdatetime.h" file
./bootstrap
./configure
make

#build it.
android/hamlib-compile
