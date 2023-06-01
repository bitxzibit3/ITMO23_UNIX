#!/bin/bash

g++ -o build/processes src/processes.cpp

build/processes 10000
build/processes 100000
build/processes 1000000