
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


#include <iostream>
#include <string>

int main()
{
    try
    {
       const  char *s = "s";
       char *s1 = const_cast<char*>(s);;
        // Statements that may throw exceptions you want to handle go here
        throw (s1); // here's a trivial example
    }
    catch (double) // no variable name since we don't use the exception itself in the catch block below
    {
        // Any exceptions of type double thrown within the above try block get sent here
        std::cerr << "We caught an exception of type double\n";
    }
    catch ( char*)
    {
        // throw -1;
        // Any exceptions of type int thrown within the above try block get sent here
        std::cerr << "We caught an int exception with value: " << '\n';
    }
    catch (const std::string&) // catch classes by const reference
    {
        // Any exceptions of type std::string thrown within the above try block get sent here
        std::cerr << "We caught an exception of type std::string\n";
    }

    // Execution continues here after the exception has been handled by any of the above catch blocks
    std::cout << "Continuing on our merry way\n";

    return 0;
}
