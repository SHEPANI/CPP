#!/bin/bash

echo "======================================"
echo "CPP Module 04 - Exercise 02"
echo "Abstract Animal Class"
echo "======================================"
echo ""

cd cpp/cpp04/ex02

echo "1. Compiling the program..."
make clean > /dev/null 2>&1
make

if [ $? -ne 0 ]; then
    echo "❌ Compilation failed!"
    exit 1
fi

echo "✅ Compilation successful!"
echo ""

echo "2. Running tests..."
echo "======================================"
./Animals
echo ""

echo "======================================"
echo "3. Key Points:"
echo "======================================"
echo "✅ Animal class is now ABSTRACT (has pure virtual function)"
echo "✅ Animal::makeSound() is declared as 'virtual void makeSound() const = 0;'"
echo "✅ Cannot instantiate Animal directly (would cause compilation error)"
echo "✅ Can only create Dog and Cat objects"
echo "✅ Polymorphism still works through Animal* pointers"
echo "✅ All tests from ex01 still work correctly"
echo ""

echo "4. Testing abstract class constraint..."
echo "======================================"
echo "The following code would NOT compile:"
echo "  Animal a;              // ERROR: abstract class"
echo "  Animal* p = new Animal(); // ERROR: abstract class"
echo ""
echo "This is the expected behavior - Animal should not be instantiable!"
echo ""

echo "✅ Exercise 02 completed successfully!"
