#!/usr/bin/env bash

cd build
rm -rf ../build/*
cmake .. && make
cd ..
./build/app/main macros/gps_test.mac
./build/app/main macros/xray.mac

