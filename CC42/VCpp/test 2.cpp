// What Happens Without virtual
// If a function is not declared as virtual, the compiler uses static dispatch
// or early binding to resolve the function call. This means that the compiler 
// determines the function to be called at compile-time based on the type of the 
// pointer or reference being used.

// In your example, if speak() were not declared as virtual in Animal, 
// the compiler would resolve the call a->speak() to Animal::speak() at compile-time,
//  because a is a pointer to Animal. The fact that a is actually pointing to a Dog object
//   at runtime would not be taken into account.

// So, without virtual, the steps I described earlier would not occur:

// No vtable lookup would be performed.
// The compiler would have already determined that Animal::speak() should be called.

// ----------------------

// How the Correct Implementation is Chosen
// At runtime, when a->speak() is called, the program follows these steps:

// It looks at the object being pointed to by a, which is a Dog object.
// It checks the vtable of the Dog class.
// It finds that Dog provides an override for speak(), so it calls Dog::speak().

// If Dog hadn't provided an override, it would have called Animal::speak(), 
// which is the implementation provided by the base class.

// #include <iostream>

// class Animal {
//     char* name;
// public:
//     Animal() { name = new char[10]; }
//     ~Animal() { 
//         delete[] name;
//         std::cout << "Destroyed\n"; 
//     }
//     void getName()
//     {
//         std::cout << this->name << "\n" ;
//     }
// };

// int main()
// {
//     Animal A;
//     A.~Animal();     // Deletes 'name'
//     A.getName();     // ❌ Access deleted memory!
//     // When A goes out of scope: delete[] name AGAIN → CRASH!
// }
#include <string>

// class Animal {
//     char* name;
// public:
//     Animal(){
//         this->name = new char;
//     }
//     Animal& operator=(const Animal& Other) {   
//         delete[] this->name;
//         this->name = new char[strlen(Other.name) + 1];
//         strcpy(this->name, Other.name);
//         return (*this);
//     }
// };
#include <iostream>
class P
{
    public:
        P()
        {
            std::cout << "P constroctor.\n";
        }
        virtual ~P()
        {
            std::cout << "P Destructor.\n";
        }
};
class C : public P
{
    public:
        C()
        {
            std::cout << "C constroctor.\n";
        }
        ~C()
        {
            std::cout << "C Destructor.\n";
        }
};

int main ()
{
    P *a = new C();
    // Animal a;
    // Animal b;
    delete a;
}
