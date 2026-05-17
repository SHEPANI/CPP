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

// ----------------------------------------------------------------------------------------------------------------------------------

#include <iostream>
int main()
{
    /*
    implicit convertion: 
    happen automatically when a value is assigned to a compatible type — no cast operator is needed.
    */
    {
        // --- Integer promotions (safe - no data loss) --- //

        short a = 303;
        int b;
        b = a; 
        std::cout <<"b : "<< b << "\n";
        bool i = true;
        a = i; 
        std::cout <<"a : " << a << " sizeof(bool) : " <<  sizeof(i) << "\n";
        i = false;
        a = i;
        std::cout << a << '\n';
        long l;
        float f;
        b = 1263278237;
        l = b;
        f = b;
        std::cout <<"l : " << l << "\nf : " << f<< " \n";
        double d = f;
        long double ld = f;
        std::cout << "f to d : " << d << "\nf to ld : " << ld <<"\n";

        // ------- Narrowing conversions (may lose data — compiler may warn) ----//

        long long ll = 1000000000001111233;
        a = ll;
        char c;
        c = ll;

        std::cout << "a : " << a << "\n";
        std::cout << "c : " << c << "\n";

        // ------------ Pointer conversions ----------------// (important)
    
        // 1. Any pointer → void*  (generic pointer, loses type info)
        int  x = 10;
        int* p = &x;
        void* vp = p;           // int* → void*  (implicit, always safe)

        // 2. void* → typed pointer  (requires explicit cast in C++, shown for contrast)
        int* p2 = (int*)vp;     // needs explicit cast — NOT implicit in C++

        // 3. Derived* → Base*  (upcasting — always implicit and safe)
        class Base  {public:
            virtual ~Base(){};};
        class Child : public Base {
                int age;
            public:
                Child(): age(10){};
                void print()
                {std::cout << "c : "<< "\n";}
                // {std::cout << "c : "<< this->age<< "\n";} // 
        };

        Child child;
        Base base;
        // child.print();
        Base* bp = &child;      // Child* → Base*  (implicit upcast)
        Base* bp2 =  &base;      // Child* → Base*  (implicit upcast)
        // bp->print(); becouse slicing and the now only the part of child the parent can use the print() func
        // but we can use dynamic cast and get the child part from the parent with add virtual 
        Child* cp = dynamic_cast<Child*>(bp);
        Child* cp1 = dynamic_cast<Child*>(bp2);// return NULL
        cp->print();
        cp1->print(); // // This "works" on NULL because nothing touches 'this' in the child class no derefrence
                        // if u wanna check decomment the child class comment  
        // 4. nullptr  → any pointer type
        int*    np1 = nullptr;  // implicit
        double* np2 = nullptr;  // implicit

        // 5. T* → const T*  (adding const is always implicit)
        int        val = 5;
        int*       ptr = &val;
        const int* cptr = ptr;  // int* → const int*  (implicit)

        // --------------- Constructor conversion vs. Conversion operator -------- //

        class Celsius {
            public:
                double degrees;
                Celsius(double d) : degrees(d){}  // converting constructor
            };
            
            double temp = 36.6;
            Celsius body = temp;   // implicit: compiler calls Celsius(36.6)
            std::cout << body.degrees << "\n";

            class A{
                public:
                    long c;
                    A(int j) : c(j){}
            };
            int j = 19;
            A n = j;
        // ------  Conversion operator ----------- //
        // Defined in the source class. It teaches that class how to produce a value of another type when needed.
        class Celsius1 {
            public:
                double degrees;
                Celsius1(double d) : degrees(d){}  // converting constructor

                operator int() const{  // conversion operator: Celsius → double
                    return degrees;
                }
            };
            
            Celsius1 body1(15);
            double db = body1; // implicit: compiler calls body.operator double()
            std::cout << db << "\n";
    }
    /*
        Explicit Conversion
            When the compiler won't convert automatically — or when you want to make your intent crystal-clear 
            — you write the cast yourself. 
    */
    {
        // C++ inherited two classic notations for this from C:

        short a = 200;
        int b;
        b = int(a); // function notation c++ version it like u say constructe an int from a
        b = (int)a; // C-like cast notation
        std::cout << "b : " << b<< "\n";
        // the deferent is just the readabillity and syntactic
        
        /* 
            Both notations are called traditional casts. For class pointers they are dangerous
            because the let u convert any pointer to any other pointer type without checks
         */

        class A{int i;};
        class B{
            float b;
            public:
                B(int i): b(i){};
                float res() 
                {return (b);}
       };
       A d;
       B *pb;
       pb = (B*) &d; // compile fine no err checks
       std::cout << pb->res() << "\n"; // undefine behaviour
       /*
            &d is the address of a CDummy object. Its memory layout is two floats (i, j).
            The compiler happily "reinterprets" that address as if it pointed to 
            a CAddition (which expects two ints, x and y).
       */

       // --- const_ cast -------- //
       
       const int x = 42;
       int *ip = const_cast<int*>(&x);
       *ip=100;

       std::cout << x << "\n";
       std::cout << *ip << "\n";
       // ------ static cast -------- //

       // Numerical conversion
        double dd = 3.99;
        int    i = static_cast<int>(dd);  // i = 3 — truncates, compiler knows this is intentional

        // Up-cast (Derived* → Base*) — always safe
        class Base {
            public:
                
        };
        class Derived : public Base {
        };

        Derived  obj;
        Base*    bp = static_cast<Base*>(&obj);  // fine — Derived IS-A Base

        // Down-cast (Base* → Derived*) — compile-time only, no runtime check
        Base*    base = new Derived();
        Derived* dp   = static_cast<Derived*>(base);  // compiles — but YOU must guarantee
                                                    // base really points to a Derived
    }
}