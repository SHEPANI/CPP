/* Test for Exercise 01 - Useful Fixed Point Class */
#include <iostream>
#include "cpp/cpp02/ex01/Fixed.hpp"

int main( void ) {
    std::cout << "===== TEST EX01: Constructors and Conversion =====" << std::endl;
    
    std::cout << "\n=== Test 1: Default constructor ===" << std::endl;
    Fixed a;
    
    std::cout << "\n=== Test 2: Int constructor ===" << std::endl;
    Fixed const b( 10 );
    
    std::cout << "\n=== Test 3: Float constructor ===" << std::endl;
    Fixed const c( 42.42f );
    
    std::cout << "\n=== Test 4: Copy constructor ===" << std::endl;
    Fixed const d( b );
    
    std::cout << "\n=== Test 5: Copy assignment with new instance ===" << std::endl;
    a = Fixed( 1234.4321f );
    
    std::cout << "\n=== Test 6: Output operator << ===" << std::endl;
    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;
    
    std::cout << "\n=== Test 7: toInt() conversion ===" << std::endl;
    std::cout << "a is " << a.toInt() << " as integer" << std::endl;
    std::cout << "b is " << b.toInt() << " as integer" << std::endl;
    std::cout << "c is " << c.toInt() << " as integer" << std::endl;
    std::cout << "d is " << d.toInt() << " as integer" << std::endl;
    
    std::cout << "\n=== Test 8: toFloat() conversion ===" << std::endl;
    std::cout << "a is " << a.toFloat() << " as float" << std::endl;
    std::cout << "b is " << b.toFloat() << " as float" << std::endl;
    std::cout << "c is " << c.toFloat() << " as float" << std::endl;
    std::cout << "d is " << d.toFloat() << " as float" << std::endl;
    
    std::cout << "\n=== Destructors should be called ===" << std::endl;
    return 0;
}
