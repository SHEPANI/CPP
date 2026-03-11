
#include <iostream>

// class a
// {
//     public:
//         virtual void f()
//         {
//             std::cout << "hello\n";
//         }

// };
// class b : public a
// {
//     private: 
//         void f()
//             {
//         std::cout << "hello1\n";
//     }
// };

// int main()
// {
//     a *s = new b();
//     s->f();
// }
//-------------------------

// class a
// {
//     private:
//         const int i ;
//         float *f;
//     public:
//         a();
//         ~a();
//         void fl();
// };

// void a::fl()
// {
//     throw 1;
// }

// a::a() : i(0)
// {
//     f = new float;
// }

// a::~a()
// {
//     delete f;
// }

// void f()
// {
//     system("leaks a.out");
// }

// int main()
// {
//     // atexit(f);
//     a s;
//     try
//     {
//         a s;
//         s.fl();
//     }
//     catch(double s)
//     {
//         std::cerr << "error" << '\n';
//     }
//     // s.fl();
// }


// #include <iostream>
// #include <string>

// int main()
// {
//     try
//     {
//        const  char *s = "s";
//        char *s1 = const_cast<char*>(s);;
//         // Statements that may throw exceptions you want to handle go here
//         throw (s1); // here's a trivial example
//     }
//     catch (double) // no variable name since we don't use the exception itself in the catch block below
//     {
//         // Any exceptions of type double thrown within the above try block get sent here
//         std::cerr << "We caught an exception of type double\n";
//     }
//     catch ( char*)
//     {
//         // throw -1;
//         // Any exceptions of type int thrown within the above try block get sent here
//         std::cerr << "We caught an int exception with value: " << '\n';
//     }
//     catch (const std::string&) // catch classes by const reference
//     {
//         // Any exceptions of type std::string thrown within the above try block get sent here
//         std::cerr << "We caught an exception of type std::string\n";
//     }

//     // Execution continues here after the exception has been handled by any of the above catch blocks
//     std::cout << "Continuing on our merry way\n";

//     return 0;
// }


// #include <iostream>

// void D() // called by C()
// {
//     std::cout << "Start D\n";
//     std::cout << "D throwing int exception\n";

//     throw - 1;

//     std::cout << "End D\n"; // skipped over
// }

// void C() // called by B()
// {
//     std::cout << "Start C\n";
//     D();
//     std::cout << "End C\n";
// }

// void B() // called by A()
// {
//     std::cout << "Start B\n";

//     try
//     {
//         C();
//     }
//     catch (double) // not caught: exception type mismatch
//     {
//         std::cerr << "B caught double exception\n";
//     }

//     try
//     {
//     }
//     catch (int) // not caught: exception not thrown within try
//     {
//         std::cerr << "B caught int exception\n";
//     }

//     std::cout << "End B\n";
// }

// void A() // called by main()
// {
//     std::cout << "Start A\n";

//     try
//     {
//         B();
//     }
//     catch (int) // exception caught here and handled
//     {
//         std::cerr << "A caught int exception\n";
//     }
//     catch (double) // not called because exception was handled by prior catch block
//     {
//         std::cerr << "A caught double exception\n";
//     }

//     // execution continues here after the exception is handled
//     std::cout << "End A\n";
// }

// int main()
// {
//     std::cout << "Start main\n";

//     try
//     {
//         throw 1;
//     }
//     catch (int) // not called because exception was handled by A
//     {
//         std::cerr << "main caught int exception\n";
//     }
//     std::cout << "End main\n";

//     return 0;
// }


// #include <iostream>
// #include <exception>

// class MyCustomError : public std::exception {
// public:
//     virtual const char* what() const throw() {
//         return "!!! My Custom Critical Error !!!";
//     }
// };

// int main() {
//     try {
//         throw MyCustomError(); // Throwing the Child
//     }
//     // WRONG WAY: Catching by Value (No &)
//     catch (std::exception e) { 
//         // C++ "Slices" the object. It converts MyCustomError into a plain std::exception.
//         // It forgets your virtual function override.
//         std::cout << "By Value: " << e.what() << std::endl; 
//     }

//     try {
//         throw std::runtime_error(""); // Throwing the Child /// way we use throwing with exception
//     }
//     // RIGHT WAY: Catching by Reference (With &)
//     catch (std::exception& e) {
//         // No copying happens. 'e' is just a pointer/reference to the original object.
//         // Polymorphism works, so it calls YOUR function.
//         // throw -1;
//         std::cout << "By Ref  : " << e.what() << std::endl;
//     }

//     return 0;
// }



// #include <iostream>

// class A { 
//     public:
//     A();
//     ~A()
//     { 
//         std::cout<<"A destroyed\n";
//     }
// };
// A::A()
// {
// }
// class B 
// { 
//     public:
//     B();
//     ~B()
//     {
//          std::cout<<"B destroyed\n";
//     }
// };
// B::B()
// {
// }
// void g() {
//     B b;
//     throw 1;
// }

// void f() {
//     A a;
//     g();
// }

// int main() {
//     try{
//         f();
//     }
//     catch(...)
//     {
//     }
// }

#include <iostream>
class B
{
    public:
        int a;
        B(void)
        {
            a = 15;
            // throw(a);
        }

};

class A : public B
{
    public:
        A(void)
        : B()
        {
        }
        // catch(float a)
        // {
        //     std::cout << "oops\n";
        // }
        ~A(void)
        {
            std::cout << "A destructor called.\n";
        }
};

struct Err
{
    int a;
    double b;
};
void f(void)
{
    A a;
    Err e;
    e.a = 5;
    e.b = 5.9;
    throw(e);
}

int main()
{
    try
    {
        f();
    }
    catch(Err a)
    {
        std::cout << "sucess " << 15 << "\n";
    }
    catch(Err b)
    {

    }
}