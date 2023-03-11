#! /bin/bash

git checkout stg

git merge dev

echo "Write your message for tag"

git tag -a $1 -m $2
