/* This file demonstrates that Animal is abstract and cannot be instantiated */

#include "cpp/cpp04/ex02/Animal.hpp"

int main()
{
    // The following line would cause a compilation error:
    // Animal a;  // ERROR: cannot declare variable 'a' to be of abstract type 'Animal'
    
    // The following line would also cause a compilation error:
    // Animal* ptr = new Animal();  // ERROR: invalid new-expression of abstract class type 'Animal'
    
    // This is correct - Animal can only be used as a base class pointer/reference
    // pointing to concrete derived class objects (Dog or Cat)
    
    return 0;
}
