# Write a bash script to run the compile the main.cpp file and run it multiple times eg. 10 times.
# The script should take the number of times the program should run as an argument.
# I want to save the time taken by the program to execute in a file called report.txt.
# The report.txt file should have the following format:
# Time taken to execute the program 1: 0.1s
# Time taken to execute the program 2: 0.2s and so on.






#!/bin/bash


if [ $# -ne 1 ]
then
    echo "Usage: $0 <number of times to run the program>"
    exit 1
fi

if [ ! -f main.cpp ]
then
    echo "main.cpp file not found!"
    exit 2
fi

g++ -std=c++17 main.cpp -o main

if [ $? -ne 0 ]
then
    echo "Compilation failed!"
    exit 3
fi

for i in $(seq 1 $1)

do
    time_taken=$(./main)
    echo "Time taken to execute the program $i: $time_taken" >> report.txt
done

echo "Report generated in report.txt"

exit 0

# Run the script as follows:

