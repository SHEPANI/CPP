/* Test for Exercise 02 - Comparison and Arithmetic Operators */
#include <iostream>
#include "cpp/cpp02/ex02/Fixed.hpp"

int main( void ) {
    std::cout << "===== TEST EX02: Operators (Comparison, Arithmetic, Increment/Decrement) =====" << std::endl;
    
    std::cout << "\n=== Test 1: Creating instances ===" << std::endl;
    Fixed a;
    Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
    
    std::cout << "\n=== Test 2: Output operator << ===" << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    
    std::cout << "\n=== Test 3: Pre-increment (++a) ===" << std::endl;
    std::cout << "++a = " << ++a << std::endl;
    
    std::cout << "\n=== Test 4: Value after pre-increment ===" << std::endl;
    std::cout << "a = " << a << std::endl;
    
    std::cout << "\n=== Test 5: Post-increment (a++) ===" << std::endl;
    std::cout << "a++ = " << a++ << std::endl;
    
    std::cout << "\n=== Test 6: Value after post-increment ===" << std::endl;
    std::cout << "a = " << a << std::endl;
    
    std::cout << "\n=== Test 7: max() static function ===" << std::endl;
    std::cout << "Fixed::max( a, b ) = " << Fixed::max( a, b ) << std::endl;
    
    std::cout << "\n=== Test 8: Comparison operators ===" << std::endl;
    Fixed x(5);
    Fixed y(10);
    std::cout << "x = " << x << ", y = " << y << std::endl;
    std::cout << "x > y: " << (x > y) << std::endl;
    std::cout << "x < y: " << (x < y) << std::endl;
    std::cout << "x >= y: " << (x >= y) << std::endl;
    std::cout << "x <= y: " << (x <= y) << std::endl;
    std::cout << "x == y: " << (x == y) << std::endl;
    std::cout << "x != y: " << (x != y) << std::endl;
    
    std::cout << "\n=== Test 9: Arithmetic operators ===" << std::endl;
    Fixed p(10);
    Fixed q(3);
    std::cout << "p = " << p << ", q = " << q << std::endl;
    std::cout << "p + q = " << (p + q) << std::endl;
    std::cout << "p - q = " << (p - q) << std::endl;
    std::cout << "p * q = " << (p * q) << std::endl;
    std::cout << "p / q = " << (p / q) << std::endl;
    
    std::cout << "\n=== Test 10: Pre-decrement (--a) ===" << std::endl;
    Fixed dec(5);
    std::cout << "dec = " << dec << std::endl;
    std::cout << "--dec = " << --dec << std::endl;
    
    std::cout << "\n=== Test 11: Post-decrement (dec--) ===" << std::endl;
    std::cout << "dec-- = " << dec-- << std::endl;
    std::cout << "dec = " << dec << std::endl;
    
    std::cout << "\n=== Test 12: min() with non-const references ===" << std::endl;
    Fixed m1(20);
    Fixed m2(15);
    std::cout << "m1 = " << m1 << ", m2 = " << m2 << std::endl;
    std::cout << "Fixed::min( m1, m2 ) = " << Fixed::min( m1, m2 ) << std::endl;
    
    std::cout << "\n=== Test 13: max() with non-const references ===" << std::endl;
    std::cout << "Fixed::max( m1, m2 ) = " << Fixed::max( m1, m2 ) << std::endl;
    
    return 0;
}
