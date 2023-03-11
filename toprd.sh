#! /bin/bash

git checkout prd

git merge stg

echo "Write your message for tag"

git tag -a $1 -m $2
	
