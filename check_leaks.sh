#!/bin/bash

echo "======================================"
echo "Memory Leak Check for CPP Module 04"
echo "======================================"
echo ""

# Check if valgrind is installed
if ! command -v valgrind &> /dev/null; then
    echo "⚠️  Valgrind not found. Installing..."
    sudo apt-get update > /dev/null 2>&1
    sudo apt-get install -y valgrind > /dev/null 2>&1
fi

# Exercise 00
echo "=== Exercise 00: Polymorphism ==="
cd /workspaces/CPP/cpp/cpp04/ex00
make fclean > /dev/null 2>&1
make > /dev/null 2>&1

if [ $? -eq 0 ]; then
    echo "✅ Compilation successful"
    echo "Running valgrind..."
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./Animals 2>&1 | grep -E "(definitely lost|indirectly lost|still reachable|ERROR SUMMARY)"
    if [ ${PIPESTATUS[0]} -eq 0 ]; then
        echo "✅ No memory leaks detected in ex00"
    else
        echo "❌ Memory leaks or errors found in ex00"
    fi
else
    echo "❌ Compilation failed"
fi

echo ""

# Exercise 01
echo "=== Exercise 01: Brain ==="
cd /workspaces/CPP/cpp/cpp04/ex01
make fclean > /dev/null 2>&1
make > /dev/null 2>&1

if [ $? -eq 0 ]; then
    echo "✅ Compilation successful"
    echo "Running valgrind..."
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./Animals 2>&1 | grep -E "(definitely lost|indirectly lost|still reachable|ERROR SUMMARY)"
    if [ ${PIPESTATUS[0]} -eq 0 ]; then
        echo "✅ No memory leaks detected in ex01"
    else
        echo "❌ Memory leaks or errors found in ex01"
    fi
else
    echo "❌ Compilation failed"
fi

echo ""

# Exercise 02
echo "=== Exercise 02: Abstract Class ==="
cd /workspaces/CPP/cpp/cpp04/ex02
make fclean > /dev/null 2>&1
make > /dev/null 2>&1

if [ $? -eq 0 ]; then
    echo "✅ Compilation successful"
    echo "Running valgrind..."
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./Animals 2>&1 | grep -E "(definitely lost|indirectly lost|still reachable|ERROR SUMMARY)"
    if [ ${PIPESTATUS[0]} -eq 0 ]; then
        echo "✅ No memory leaks detected in ex02"
    else
        echo "❌ Memory leaks or errors found in ex02"
    fi
else
    echo "❌ Compilation failed"
fi

echo ""
echo "======================================"
echo "Memory leak check complete"
echo "======================================"
