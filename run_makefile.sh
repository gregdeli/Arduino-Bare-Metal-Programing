#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <rule> <target>"
    echo "Available rules: default, upload, arduino, assembly, clean"
    exit 1
fi

# Assign arguments to variables
RULE=$1
TARGET=$2

# Export the TARGET variable and run the selected makefile rule
export TARGET
make -f Makefile $RULE

# Check if the make command was successful
if [ $? -eq 0 ]; then
    echo "Makefile rule '$RULE' executed successfully for target '$TARGET'."
else
    echo "Makefile rule '$RULE' failed for target '$TARGET'."
fi