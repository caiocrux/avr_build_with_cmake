#!/bin/bash

# pip install cpplint 

cpplint --root=. --recursive ./src ./lib 

if [ $? -eq 0 ];
then
    echo "executed without any C Code Guide Style Error!"
else
    echo "found some Style Error!"
fi

