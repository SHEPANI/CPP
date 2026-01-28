

////////////////////////////////////////////////////////
What are Exception Classes?
----------------------------------------------------------------
Exception classes are special classes used to represent errors.
----------------------------------------------------------------

In C++, you throw and catch these to handle problems gracefully. For example:

'''
cppclass MyException : public std::exception {
    // This is an exception class
};
'''

////////////////////////////////////////////////////////
Why This Exception?
----------------------------------
Exception classes are typically:
----------------------------------

Lightweight objects used temporarily during error handling.
Often thrown and caught by value or reference.
Designed to carry error information, not manage resources.

The exception classes are simple and don't need the full OCF treatment 
- they just need to inherit from std::exception and override the what() method.


////////////////////////////////////////////////////////
Throwing exceptions?
----------------------------------
In C++, a throw statement is used to signal that an exception or error case has occurred 
(think of throwing a penalty flag). Signaling that an exception has occurred 
is also commonly called raising an exception.
----------------------------------
To use a throw statement, simply use the throw keyword, 
followed by a value of any data type you wish to use to
signal that an error has occurred. Typically, this value will
be an error code, a description of the problem, or a custom exception class.

{
    throw -1; // throw a literal integer value
    throw ENUM_INVALID_INDEX; // throw an enum value
    throw "Can not take square root of negative number"; // throw a literal C-style (const char*) string
    throw dX; // throw a double variable that was previously defined
    throw MyException("Fatal Error"); // Throw an object of class MyException
}

////////////////////////////////////////////////////////
Looking for exceptions?
-----------------------------------
In C++, we use the try keyword to define a block of statements (called a try block).
The try block acts as an observer, looking for any exceptions that are thrown 
by any of the statements within the try block.
-----------------------------------

{
    try
    {
        // Statements that may throw exceptions you want to handle go here
        throw -1; // here's a trivial throw statement
        // ta9der tkon function muhim trowi
    }
}
Note that the try block doesn’t define HOW we’re going to handle the exception.
It merely tells the program, “Hey, if any of the statements inside 
this try block throws an exception, grab it!”.

////////////////////////////////////////////////////////

Handling exceptions?

Actually handling exceptions is the job of the catch block(s).
The catch keyword is used to define a block of code (called a catch block)
that handles exceptions for a single data type.
----------------------------------------------------
Keyword         Role                                            Analogy

throw           Sender - creates and sends the signal           Throwing a ball
try             Observer - watches for signals                  Standing ready to catch
catch           Handler - receives and handles the signal       Catching the ball
-----------------------------------------------------


/////////////////////////////////////////////////////////

'''
class a
{
    private:
        const int i ;
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
    // atexit(f);
    a s;
    try
    {
        a s;
        s.fl();
    }
    catch(double s)
    {
        std::cerr << "error" << '\n';
    }
    // s.fl();
}
'''

-------------- Final distilled explanation (exam-ready) -----------------
Exception handling uses runtime type identity, not compile-time conversion rules.
Numeric promotions and implicit conversions are disabled because they would 
introduce ambiguity, platform dependence, and unpredictable control flow. 
Only exact type matches or inheritance-based compatibility 
are allowed to preserve safety and determinism.
------------------------------------------------------------------------------------------------------
In normal C++ programming (like function calls), the compiler tries to be helpful by automatically converting types for you. In exception handling, it disables this "helpfulness" to prevent accidents.

Here is the breakdown of what this means and why it happens.

1. "Type Matching, Not Type Conversion"
In standard C++, if you pass an int to a function that expects a double, the compiler automatically converts it.

Normal Function: void func(double d); → Calling func(10) works (10 becomes 10.0).

Exception Handling: catch(double d) → Throwing 10 fails to catch.

The catcher looks for an exact match of the data type.

Example: The "Picky" Catcher
C++

try {
    // We throw an integer
    throw 10; 
} 
catch (double d) {
    // This will NOT catch the exception. 
    // Even though 10 can become 10.0, C++ refuses to convert it here.
    std::cout << "Caught a double"; 
}
catch (long l) {
    // This will NOT catch the exception.
    // Even though int fits inside long, C++ refuses to promote it.
    std::cout << "Caught a long";
}
catch (int i) {
    // This MATCHES exactly. This block runs.
    std::cout << "Caught an int!";
}

2. "Numeric Promotions are Disabled"
A "promotion" is when a smaller type (like char or short) is automatically upgraded to an int. Exceptions do not allow this.

If you throw 'A'; (a char), a catch block defined as catch(int x) will ignore it, even though a char is technically just a small number.

3. Why? (Safety and Determinism)
The quote mentions "safety and determinism." Here is why strictness is safer:

Scenario: Imagine you have two catch blocks:

catch (int error_code): Handles system error numbers.

catch (double temperature): Handles temperature sensor readings.

If you throw 10 (an integer error code), and C++ allowed implicit conversion:

The compiler might see the double catcher first and say, "Hey, 10 fits into a double!"

Your error code would accidentally be caught by the temperature handler.

The system would try to process your error as a temperature, leading to confusing bugs.

By disabling conversion, C++ ensures that an int is always handled by the int handler, eliminating ambiguity (determinism).
--------------------------------------------------------------------------------------------------------------------------------
The ONLY Exceptions to the Rule
While C++ is strict about numbers, it does allow three specific types of "adjustments" that are considered safe:

Const Qualification: throw "Error" (non-const) can be caught by catch (const char*).

Array/Function Decay: Arrays convert to pointers (just like in function calls).

Inheritance (Crucial): A Child class object can be caught by a Parent class handler.

If you throw a std::runtime_error, it can be caught by catch (std::exception).


#include <iostream>
#include <string>

int main()
{
    try
    {
        // Statements that may throw exceptions you want to handle go here
        throw -1; // here's a trivial example
    }
    catch (double) // no variable name since we don't use the exception itself in the catch block below
    {
        // Any exceptions of type double thrown within the above try block get sent here
        std::cerr << "We caught an exception of type double\n";
    }
    catch (int x)
    {
        // Any exceptions of type int thrown within the above try block get sent here
        std::cerr << "We caught an int exception with value: " << x << '\n';
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
--------------------------------------------------------------------------------------------------

what of this are allowed 
"Exact Match
Promotion
Standard Conversion
User-Defined Conversion
Ellipsis (...)"
/////////////////////////////
1. Exact Match (Allowed)
This is the gold standard. If you throw an int, you catch an int.

C++

throw 10;      // Caught by catch(int)
throw "Error"; // Caught by catch(const char*)
/////////////////////////////
2. Promotion (NOT Allowed)
In normal code, a char is automatically "promoted" to an int for math. In exceptions, this is disabled.

C++

char c = 'A';
try {
    throw c; // Throwing a char
}
catch (int x) { 
    // FAIL: This will NOT catch it. 
    // In normal functions this works, but here it is strictly forbidden.
}
/////////////////////////////
3. Standard Conversion (NOT Allowed for Numbers)
In normal code, an int converts to a double. In exceptions, this is disabled.

C++

    try {
        throw 10; // Throwing an int
    }
    catch (double d) {
        // FAIL: 10 is not converted to 10.0.
    }

The "Inheritance" Exception: There is one specific type of standard conversion that IS allowed: Derived-to-Base.

If you throw a Child object, it CAN be caught by a Parent handler.

'''
#include <iostream>

// 1. The Parent Class (Base)
class ServerError {
public:
    virtual void message() { std::cout << "Generic Server Error"; }
};

// 2. The Child Class (Derived)
// Notice it inherits from ServerError
class ConnectionTimeout : public ServerError {
public:
    void message() { std::cout << "Error: Connection Timed Out"; }
};

int main() {
    try {
        // We throw the CHILD object
        throw ConnectionTimeout(); 
    } 
    // We catch using the PARENT type
    // NOTE: We usually catch by reference (&) to avoid object slicing
    catch (ServerError& e) {
        std::cout << "Caught by Parent Handler!" << std::endl;
        e.message(); // Prints "Error: Connection Timed Out" thanks to virtual functions
    }
    
    return 0;
}
'''
Why this works: The compiler sees that ConnectionTimeout is a ServerError, so the catch block accepts it.
/////////////////////////////////////////////////////
If you throw a char* (string), it CAN be caught by void*
'''
C++ allows any non-const data pointer to be caught by a void* (a generic pointer), because void* is the "universal" pointer type in C++.

Note: This does not work for const char* (string literals like "hello"), only for mutable char* variables.

C++

#include <iostream>

int main() {
    char myString[] = "Critical Failure";
    char* myPointer = myString;

    try {
        // We throw a specific pointer (char*)
        throw myPointer;
    } 
    // We catch using a generic pointer (void*)
    catch (void* ptr) {
        std::cout << "Caught by void* handler!" << std::endl;
        std::cout << "Address: " << ptr << std::endl;
        
        // Note: You cannot print the text inside 'ptr' directly 
        // because void* doesn't know it's text. You would have to cast it back.
    }

    return 0;
}
''''
Why this works: char* automatically converts to void* in standard C++. The exception system respects this specific pointer conversion.

/////////////////////////////////////////////////////
4. User-Defined Conversion (NOT Allowed)
Even if you have a class that can be created from an integer, the exception system won't do it for you.

C++

class MyError {
public:
    MyError(int x) {} // Constructor converts int to MyError
};

try {
    throw 10; // Throwing int
}
catch (MyError e) {
    // FAIL: The compiler will not run the constructor to convert 10 to MyError.
}

/////////////////////////////
5. Ellipsis (...) (Allowed)
This is a special C++ feature (often called "catch-all"). It matches any type of exception, no matter what the signal is.

C++

try {
    throw 500;
}
catch (...) {
    // SUCCESS: This catches anything.
}
---------------------------------------------------------------------------------------------------
What catch blocks typically do

If an exception is routed to a catch block, it is considered “handled” even if the catch block is empty. However, typically you’ll want your catch blocks to do something useful. There are four common things that catch blocks do when they catch an exception:

First, catch blocks may print an error (either to the console, or a log file) and then allow the function to proceed.

Second, catch blocks may return a value or error code back to the caller.////

Third, a catch block may throw another exception. Because the catch block is outside of the try block, the newly thrown exception in this case is not handled by the preceding try block -- it’s handled by the next enclosing try block.

Fourth, a catch block in main() may be used to catch fatal errors and terminate the program in a clean way.
---------------------------------------------------------------------------------------------------
