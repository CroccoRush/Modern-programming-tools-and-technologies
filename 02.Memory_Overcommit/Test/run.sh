#!/bin/bash

echo "Running with size 500GB; mode Write; pause 999µs:"
./test.exe -s 536870912000 -m w -p 999
sleep 1.0
echo

echo "Running with size 500GB; mode Write; pause 1000µs:"
./test.exe -s 536870912000 -m w -p 1000
sleep 1.0
echo

echo "Running with size 500GB; mode Read; pause 999µs:"
./test.exe -s 536870912000 -m r -p 999
sleep 1.0
echo

echo "Running with size 500GB; mode Read; pause 1000µs:"
./test.exe -s 536870912000 -m r -p 1000
sleep 1.0
echo

echo

echo "Running with size 50GB; mode Write; pause 999µs:"
./test.exe -s 53687091200 -m w -p 999
sleep 10.0
echo

echo "Running with size 50GB; mode Write; pause 1000µs:"
./test.exe -s 53687091200 -m w -p 1000
sleep 10.0
echo

echo "Running with size 50GB; mode Read; pause 999µs:"
./test.exe -s 53687091200 -m r -p 999
sleep 10.0
echo

echo "Running with size 50GB; mode Read; pause 1000µs:"
./test.exe -s 53687091200 -m r -p 1000
sleep 1.0
echo

echo
echo "Press any button to exit..."
read -n 1 -s -r