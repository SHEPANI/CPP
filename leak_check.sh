#!/bin/bash

echo "=== Checking Memory Leaks with Valgrind ==="
echo ""

# Install valgrind if not present
command -v valgrind >/dev/null 2>&1 || { 
    echo "Installing valgrind..."
    apt-get update -qq && apt-get install -y valgrind -qq
}

for ex in ex00 ex01 ex02; do
    echo "=========================================="
    echo "Testing cpp/cpp04/$ex"
    echo "=========================================="
    
    # Compile
    make -C cpp/cpp04/$ex fclean >/dev/null 2>&1
    make -C cpp/cpp04/$ex >/dev/null 2>&1
    
    if [ $? -ne 0 ]; then
        echo "❌ Compilation failed for $ex"
        continue
    fi
    
    echo "✅ Compiled successfully"
    echo ""
    echo "Running valgrind memory check..."
    echo ""
    
    # Run valgrind
    valgrind --leak-check=full \
             --show-leak-kinds=all \
             --track-origins=yes \
             --verbose \
             --log-file=/tmp/valgrind-$ex.log \
             cpp/cpp04/$ex/Animals >/dev/null 2>&1
    
    # Check results
    echo "--- Valgrind Summary ---"
    grep "LEAK SUMMARY" /tmp/valgrind-$ex.log -A 5
    grep "ERROR SUMMARY" /tmp/valgrind-$ex.log
    
    # Determine if there are leaks
    definitely_lost=$(grep "definitely lost:" /tmp/valgrind-$ex.log | awk '{print $4}')
    indirectly_lost=$(grep "indirectly lost:" /tmp/valgrind-$ex.log | awk '{print $4}')
    
    if [ "$definitely_lost" = "0" ] && [ "$indirectly_lost" = "0" ]; then
        echo "✅ No memory leaks in $ex"
    else
        echo "❌ Memory leaks detected in $ex!"
        echo "Full log at /tmp/valgrind-$ex.log"
    fi
    
    echo ""
done

echo "=========================================="
echo "Memory leak check completed"
echo "=========================================="
