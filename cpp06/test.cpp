// ----- Implicit conversion ---

/*

Implicit conversions do not require any operator.
They are automatically performed when a value is copied
to a compatible type.

*/

/*

int main()
{
    short a = 100; 
    int b;
    b = a; // the value of a has been promoted from short to int
           // and we have not had to specify any type-casting operator.
           // This is known as a "standard conversion".
}

*/

/*
Implicit conversions also include constructor or operator conversions,
which affect classes that include specific constructors or operator 
functions to perform conversions. For example:Unrelated
*/

/*
    // implicit constructor conversion

#include <iostream>
class a
{
    public:
        a(){
            std::cout << "a constructer\n";
        }
};
class b
{
    public:
        b (a A){
            std::cout << "b constructer\n";
        }
};

int main()
{
    a A;
    b B(A);
}

*/


// --------------- Explicit conversion --------------

// C++ is a strong-typed language. Many conversions, specially those that imply a different interpretation of the value,
// require an explicit conversion. We have already seen two notations for explicit type conversion:
// functional and c-like casting:

// {
//     short a=2000;
//     int b;
//     b  = (int) a;    // c-like cast notation
//     b = int (a);    // functional notation 
// }

// #include <iostream>
// class a
// {
//     public:
//         int i = 10 , j=19;
// };

// class b
// {
//     public: 
//         float b = 11 , c = 15;
// };
// int main()
// {
//     a * p ;
//     b i;

//     p = (a*)&i;
//     a &rff = (a&)i;
//     std::cout << rff.j << "\n"<< p->i<< "\n"<<i.b;
// }



// // class type-casting
// #include <iostream>
// using namespace std;

// class CDummy {
//     float i,j;
// };

// class CAddition {
// 	int x=0,y=12;
//   public:
// 	CAddition (int a, int b) { x=13; y=13; }
// 	int result() { return x+y;}
// };

// int main () {
//   CDummy d;
//   CAddition * padd;
//   padd = (CAddition*) &d;
//   cout << padd->result();
//   return 0;
// }


// // ------------ static cast ---------- //


//         // static_cast<T>(v) //
// int main()
// {
//     /*
//         If T is a reference type,
//         the result is an lvalue (you get a reference back).

//         When the documentation says the result is an lvalue,
//         it means the casted object still points to a real 
//         "home" in memory, rather than being a temporary
//         number floating in space.

//         Think of an lvalue as a "locator value."
//         It represents an object that occupies
//         a persistent location in memory.

//         Example: int x = 5; — Here, x is an lvalue.
//         You can take its address (&x).

//     */
//     {
//         int i = 19;
//         int j = static_cast<int&>(i);
//         /*A brand new int object is constructed 
//         It is a temporary copy (an rvalue).*/
    
//         printf("%i\n", j);
//         j = 1;
//         printf("%i\n", i);
//     }
//     {
//         int i = 19;
//         int& j = static_cast<int&>(i);
//         /*
//         No new object is created.
//         "j" is just a new name (an lvalue) 
//         for the memory already occupied by "i".
//         If you modify d, "j" sees those changes.
//         */
//         printf("%i\n", j);
//         j = 1;
//         printf("%i\n", i);
//     }
//     {
//         int i = 19;
//         static_cast<int&>(i) = i-1;
//         printf("%i\n", i);
//     }

//     {
//         double i = 10.7;
//         std::cout << i<<"\n";
//         double j = static_cast<int>(i);
//         std::cout << j<<"\n";

//     }

//     /*
//         summary :
//         static_cast<int>(v): Gives you a value (copy).

//         static_cast<int&>(v): Gives you a reference 
//         (the original memory location, aka an lvalue).
//     */
//    // ----------------------------------------------

//    // ---- You cannot define new types inside the cast.---//

//    /*
//         This means the target type (the one inside the < >) must already be a known,
//         fully defined type before the line of code is reached.
//         You cannot use the cast as a place to declare a new struct or class on the fly.
//    */

//    {
//     // Trying to define a new struct inside the cast
//     void* ptr;
//     // static_cast<struct NewType { int x; }*>(ptr); // wrong

//     // right way 
//         struct NewType { int x; }; // Define it first
    
//         NewType* myType = static_cast<NewType*>(ptr); // Now use it
//    }

//    // ------------ It cannot cast away constness ----------// 
   
//    /*
//         This is the most important safety feature of `static_cast`.
//         If a variable is marked `const`, it is "locked" from being changed.
//         `static_cast` respects that lock.
//    */
//   {
//     const int i = 42;
//     // int& b = static_cast<int&>(i); // Error! static_cast cannot remove 'const
//     int& b = const_cast<int&>(i);
//     std::cout << b << "\n"<< i;
//     /*
//         ### Why this matters for your ScalarConverter
//         In your project, you are dealing with `std::string& str`.
//         If that string were passed as a `const std::string& str`,
//         and you tried to pass it to a function that requires a non-const string,
//         `static_cast` wouldn't help you.

//         **The "Job" Breakdown:**
//         *   **`static_cast`**: Changes the **Type** (e.g., `double` to `int`).
//         *   **`const_cast`**: Changes the **Access Rights** (e.g., `const` to `non-const`).

//         Think of it this way: `static_cast` changes the *shape* of the data,
//         while `const_cast` only changes the *permission* to touch it.
//     */
//   }
// }

