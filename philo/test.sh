#!/bin/bash

# Path to your program
PROGRAM="./philo 1600 100 40 40 100"

# Loop until the program crashes
while true; do
    # Run the program
    $PROGRAM

    # Check the exit status
    if [ $? -eq 0 ]; then
		echo "No crash"
        break
    fi

done