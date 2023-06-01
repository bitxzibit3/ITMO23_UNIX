#!/bin/bash

bash build_all.sh

echo 'Sequence stats:'
build/seq

echo 'Threads stats:'
build/threads

echo 'Processes stats:'
bash processes_stats.sh