#!/bin/bash

echo "Testing CPP04 Exercise 01..."
echo "=============================="
echo ""

cd cpp/cpp04/ex01

echo "Compiling..."
make clean > /dev/null 2>&1
make

if [ $? -eq 0 ]; then
    echo ""
    echo "Compilation successful!"
    echo ""
    echo "Running tests..."
    echo "=============================="
    ./Animals
    echo ""
    echo "=============================="
    echo "Checking for memory leaks with valgrind..."
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./Animals 2>&1 | grep -E "(definitely lost|indirectly lost|ERROR SUMMARY)"
else
    echo "Compilation failed!"
    exit 1
fi
