#!/bin/bash

echo "Running with no options:"
./automation.exe

echo "Running with -n (newline):"
./automation.exe -n

echo "Running with -f (fflush):"
./automation.exe -f

echo "Running with -n and -f:"
./automation.exe -n -f

echo "Running with no options and redirecting output to file:"
./automation.exe &> output.txt
echo "Saved to output.txt"

echo "Running with -f and redirecting output to file:"
./automation.exe -f &> output_f.txt
echo "Saved to output_f.txt"

echo "Running with -n and redirecting output to file:"
./automation.exe -n &> output_n.txt
echo "Saved to output_n.txt"

echo "Running with -n and -f and redirecting output to file:"
./automation.exe -n -f &> output_nf.txt
echo "Saved to output_nf.txt"

echo
echo "Press any button to exit..."
read -n 1 -s -r