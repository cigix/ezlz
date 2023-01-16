#!/bin/bash

THIS_SCRIPT=${BASH_SOURCE[0]}
THIS_DIR=$(dirname "$THIS_SCRIPT")

cd "$THIS_DIR"

if [ -z "$EZLZ" -o -z "$UNEZLZ" ]
then
    echo "This script requires environment variables EZLZ and UNEZLZ be set"
    exit 1
fi

error=0
for script in ./[[:digit:]][[:digit:]]-*.sh
do
    echo -n "$script: "
    output=$("$script" 2>&1)
    if [ $? -eq 0 ]
    then
        echo -e "\e[32mOK\e[0m"
    else
        echo -e "\e[31mKO\e[0m"
        echo "$output"
        error=1
    fi
done
exit $error
