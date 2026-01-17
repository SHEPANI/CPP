/* Test for Exercise 00 - Basic Orthodox Canonical Form */
#include <iostream>
#include "cpp/cpp02/ex00/Fixed.hpp"

int main( void ) {
    std::cout << "===== TEST EX00: Orthodox Canonical Form =====" << std::endl;
    
    std::cout << "\n=== Test 1: Default constructor ===" << std::endl;
    Fixed a;
    
    std::cout << "\n=== Test 2: Copy constructor ===" << std::endl;
    Fixed b( a );
    
    std::cout << "\n=== Test 3: Copy assignment ===" << std::endl;
    Fixed c;
    c = b;
    
    std::cout << "\n=== Test 4: getRawBits() ===" << std::endl;
    std::cout << "a.getRawBits() = " << a.getRawBits() << std::endl;
    std::cout << "b.getRawBits() = " << b.getRawBits() << std::endl;
    std::cout << "c.getRawBits() = " << c.getRawBits() << std::endl;
    
    std::cout << "\n=== Test 5: setRawBits() ===" << std::endl;
    c.setRawBits(1337);
    std::cout << "After c.setRawBits(1337): " << c.getRawBits() << std::endl;
    
    std::cout << "\n=== Destructor should be called 3 times ===" << std::endl;
    return 0;
}
