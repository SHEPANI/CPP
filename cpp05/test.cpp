
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
//         void fl();ta9der tkon function muhim throwi
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

// #include <iostream>
// class B
// {
//     public:
//         int a;
//         B(void)
//         {
//             a = 15;
//             // throw(a);
//         }

// };

// class A : public B
// {
//     public:
//         A(void)
//         : B()
//         {
//         }
//         // catch(float a)
//         // {
//         //     std::cout << "oops\n";
//         // }
//         ~A(void)
//         {
//             std::cout << "A destructor called.\n";
//         }
// };

// struct Err
// {
//     int a;
//     double b;
// };
// void f(void)
// {
//     A a;
//     Err e;
//     e.a = 5;
//     e.b = 5.9;
//     throw(e);
// }

// int main()
// {
//     try
//     {
//         f();
//     }
//     catch(Err a)
//     {
//         std::cout << "sucess " << 15 << "\n";
//     }
//     catch(Err b)
//     {

//     }
// }

// #include <iostream>
// #include <fstream>

// int main()
// {
//     std::ofstream outFile("<target>_shrubbery");
//     if (outFile.is_open())
//         std::cout << "succes\n";
//     else   
//         std::cout << "not succes\n";
    
//     outFile <<
//         "       _-_\n"
//         "    /~~   ~~\\\n"
//         " /~~         ~~\\\n"
//         "{               }\n"
//         " \\  _-     -_  /\n"
//         "   ~  \\\\ //  ~\n"
//         "_- -   | | _- _\n"
//         "  _ -  | |   -_\n"
//         "      / / \\ \n";
// }


//---------------------------------------------------------
/*
class test
{
    public:
        test();
        ~test();
        // void func(test& a){}
};

test::~test()
{}
test::test()
{
}

class test1
{
    public:
        test1();
        ~test1();
        // void func(test1& a){}
};

test1::~test1()
{}
test1::test1()
{
}


test1& func1(test1& b)
{
    std::cout << "func b\n";
    return b;
}

test& func(test1& a)
{
    std::cout << "test currect\n";

    throw func1(a);
    std::cout << "after Throw\n";
}



int main()
{
    test1 a;
    
    try
    {
        func(a);
    }
    catch(test& a)
    {
        std::cerr << "has been catch" << '\n';
        return 1;
    }
     
}
hadi 4adi dump o terminita 7it wakha throwina 
function catch katchof return ta3ha machi match ma tkatchach
*/

//---------------------------------------------------------------

/*

class a
{
    private:
        const int i;
        float *f;
    public:
        a();
        ~a();
        void fl();
};

void a::fl()
{
    throw 1;
}

a::a() : i(0)
{
    f = new float;
}
a::~a()
{
    delete f;
}

    
void f()
{
    system("leaks a.out");
}

int main()
{
    atexit(f);
    a s;
    try
    {
        a s;
        s.fl();
    }
    catch(int s)
    {
        std::cerr << "error" << '\n';
    }
    s.fl();
}

 */

 // -----------------------------------------------------------------

/*

Type Matching, Not Type Conversion

int main()
{
    try {
        // We throw an integer
        throw 10; 
    } 
    catch (double d) {
        // This will NOT catch the exception. 
        // Even though 10 can become 10.0, C++ refuses to convert it here.
        std::cout << "Caught a double\n"; 
    }
    catch (long l) {
        // This will NOT catch the exception.
        // Even though int fits inside long, C++ refuses to promote it.
        std::cout << "Caught a long\n";
    }
    catch (int i) {
        // This MATCHES exactly. This block runs.
        std::cout << "Caught an int!\n";
    }
}
*/

// ----------------------------------
/*
int main()
{
    try {
        // We throw an integer
        const char* s = "hello";
        throw s; 
    } 
    catch (double d) {
        // This will NOT catch the exception. 
        // Even though 10 can become 10.0, C++ refuses to convert it here.
        std::cout << "Caught a double\n"; 
    }
    catch (const void* l) {
        // This will NOT catch the exception.
        // Even though int fits inside long, C++ refuses to promote it.
        std::cout << "Caught a void*\n";
    }
    catch (const  char* i) {
        // This MATCHES exactly. This block runs.
        std::cout << "Caught an char*!\n";
    }
}
    char * ta9dar t catchih b void* b7al kima ta9dar tcatshi child b parent obj
    Pointer conversion (char* to void*) o drived-to-base classes 
*/
// -----------------------------------------------
/*

//ellipsis

int main()
{
    try {
        throw 500;
    }
    catch (...) {
        // SUCCESS: This catches anything.
    }
}
*/
/*
class B
{
    public:
};

class A : public B
{
    public:
        A(void)
        : B()
        {
        }
        ~A(void)
        {
            std::cout << "A destructor called.\n";
        }
};

void f(void)
{
    A a;
    throw(5);
}

int main()
{
    try
    {
        f();
    }
    catch(float a)
    {
        std::cout << "sucess " << a << "\n";
    }
}

// unwinding i9dar itra i9dar ma yatrach mani ma kayat catshach exp b7al hna 
// ma destroyach object a li kayn f func f()

//     You got it exactly right! That is a perfect summary of how the two systems work.

//     Here is your summary mapped to the exact concepts compiler engineers use:

// 1. The Two-Pass System (The "Scout" Method)
//     Your Summary: "Checks first if there is a catch... then chooses to go back and destroy or abort."

//     How it works: Pass 1 is the scout. It runs up the call stack, looking at all the try/catch blocks without touching a single variable. If it finds a match, it sends Pass 2 to unwind the stack safely. If the scout hits the top of the program and finds nothing, it tells the program to terminate immediately, leaving the memory frozen exactly as it was.

// 2. The One-Pass System (The "Bulldozer" Method)
//     Your Summary: "Checks catch blocks one by one when he destroys content of them one by one."

//     How it works: It destroys as it searches. The moment an error is thrown, it starts walking backward, calling destructors and wiping out memory. At each step, it asks, "Is there a catch block here?" If it reaches the end and the answer is still no, the program crashes, but the memory has already been completely wiped clean during the search.

//     You have completely mastered the logic behind C++ stack unwinding. You are officially thinking
*/