 # C++ Exception Handling Guide

---
## What are Exception?

**Handling errors in functions**

    There are 4 general strategies that can be used:

        * Handle the error within the function
        * Pass the error back to the caller to deal with
        * Halt the program
        * Throw an exception

An exception in C++ is a control-flow mechanism used to report and handle runtime errors separately from normal return values.

Exception handling provides a mechanism to decouple handling of errors or other exceptional circumstances from the typical control flow of your code. This allows more freedom to handle errors when and how ever is most useful for a given situation, alleviating most (if not all) of the messiness that return codes cause.

Because returning an error from a function back to the caller is complicated (and the many different ways to do so leads to inconsistency, and inconsistency leads to mistakes), C++ offers an entirely separate way to pass errors back to the caller: exceptions.

The basic idea is that when an error occurs, an exception is “thrown”. If the current function does not “catch” the error, the caller of the function has a chance to catch the error. If the caller does not catch the error, the caller’s caller has a chance to catch the error. The error progressively moves up the call stack until it is either caught and handled (at which point execution continues normally), or until main() fails to handle the error (at which point the program is terminated with an exception error).

## Example Code

```cpp
Normal execution:
    
    main → A → B → C → return → B → return → A → return → main

With exception thrown in C++:

    main → A → B → C → throw
             ↑
       unwinding destroys C locals
       unwinding destroys B locals
       unwinding destroys A locals
       caught in main (or program terminates)

```
## Why exceptions exist

    * Separate error handling from business logic.

    * Avoid manual propagation of error codes.

    * Enforce cleanup via destructors during failure.

    * Centralize error handling at higher abstraction levels.

**Core issue**

    Return-code systems:
        Interleave success logic with error plumbing.
        Require manual propagation.
        Depend on consistent checking.
        Overload return values.
        Increase cognitive load.

    Exceptions:

        Separate error path from main logic.
        Automatically propagate upward.
        Automatically clean resources.
        Keep interfaces semantically clean.

- Chatgpt Example:
        https://chatgpt.com/s/t_69a451332a608191a8f8419a1b3b4323
## Condensed decision

    Is failure rare and is to handled locally, and should propagate automatically?

    Use this when:

        Failure is exceptional, not routine.
        Error must propagate across multiple layers.
        Local function cannot fix it.
        Return-based error propagation would pollute many interfaces.
        You need automatic stack unwinding and cleanup.

    Examples:

        Constructor fails to establish a valid object.
        Resource acquisition fails.
        Deep library code detects violation.
        Invariant breach inside a class.
        Exceptions are for structural failure across abstraction boundaries.

## Throwing Exceptions

Exceptions in C++ are implemented using three keywords that work in conjunction with each other: throw, try, and catch.

In C++, a `throw` statement is used to signal that an exception or error case has occurred (think of throwing a penalty flag). Signaling that an exception has occurred is also commonly called **raising an exception**.

To use a throw statement, simply use the `throw` keyword, followed by a value of any data type you wish to use to signal that an error has occurred. Typically, this value will be an error code, a description of the problem, or a custom exception class.

```cpp
{
    throw -1; // throw a literal integer value
    throw ENUM_INVALID_INDEX; // throw an enum value
    throw "Can not take square root of negative number"; // throw a literal C-style (const char*) string
    throw dX; // throw a double variable that was previously defined
    throw MyException("Fatal Error"); // Throw an object of class MyException
}
```

---

## Looking for Exceptions

In C++, we use the `try` keyword to define a block of statements (called a **try block**). The try block acts as an observer, looking for any exceptions that are thrown by any of the statements within the try block.

```cpp
{
    try
    {
        // Statements that may throw exceptions you want to handle go here
        throw -1; // here's a trivial throw statement
        // ta9der tkon function muhim throwi
    }
}
```

**Note:** The try block doesn't define HOW we're going to handle the exception. It merely tells the program, "Hey, if any of the statements inside this try block throws an exception, grab it!".

---

## Handling Exceptions

Actually handling exceptions is the job of the **catch block(s)**. The `catch` keyword is used to define a block of code (called a catch block) that handles exceptions for a single data type.

| Keyword | Role                                    | Analogy                  |
|---------|----------------------------------------|--------------------------|
| `throw` | Sender - creates and sends the signal  | Throwing a ball         |
| `try`   | Observer - watches for signals         | Standing ready to catch |
| `catch` | Handler - receives and handles signal  | Catching the ball       |

**What catch blocks typically do**

    If an exception is routed to a catch block, it is considered “handled” even if the catch block is empty. However, typically you’ll want your catch blocks to do something useful. There are four common things that catch blocks do when they catch an exception:

    First, catch blocks may print an error (either to the console, or a log file) and then allow the function to proceed.

    Second, catch blocks may return a value or error code back to the caller.

    Third, a catch block may throw another exception. Because the catch block is outside of the try block, the newly thrown exception in this case is not handled by the preceding try block -- it’s handled by the next enclosing try block.

    Fourth, a catch block in main() may be used to catch fatal errors and terminate the program in a clean way.

---

## Example Code

```cpp
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
```

## Recapping exception handling

Exception handling is actually quite simple, and the following two paragraphs cover most of what you need to remember about it:

When an exception is raised (using throw), the running program finds the nearest enclosing try block (propagating up the stack if necessary to find an enclosing try block -- we’ll discuss this in more detail next lesson) to see if any of the catch handlers attached to the try block can handle that type of exception. If so, execution jumps to the top of the catch block, the exception is considered handled.

If no appropriate catch handlers exist in the nearest enclosing try block, the program continues to look at subsequent enclosing try blocks for a catch handler. If no appropriate catch handlers can be found before the end of the program, the program will fail with a runtime exception error.

**Note** that the program will not perform implicit conversions or promotions when matching exceptions with catch blocks! For example, a char exception will not match with an int catch block. An int exception will not match a float catch block. However, casts from a derived class to one of its parent classes will be performed.

---

## Final Distilled Explanation (Exam-Ready)

**Exception handling uses runtime type identity, not compile-time conversion rules.**

Numeric promotions and implicit conversions are disabled because they would introduce ambiguity, platform dependence, and unpredictable control flow. Only exact type matches or inheritance-based compatibility are allowed to preserve safety and determinism.

In normal C++ programming (like function calls), the compiler tries to be helpful by automatically converting types for you. In exception handling, it disables this "helpfulness" to prevent accidents.

---

## Type Matching, Not Type Conversion

In standard C++, if you pass an `int` to a function that expects a `double`, the compiler automatically converts it.

- **Normal Function:** `void func(double d);` → Calling `func(10)` works (10 becomes 10.0).
- **Exception Handling:** `catch(double d)` → Throwing `10` fails to catch.

The catcher looks for an **exact match** of the data type.

### Example: The "Picky" Catcher

```cpp
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
```

---

## Numeric Promotions are Disabled

A "promotion" is when a smaller type (like `char` or `short`) is automatically upgraded to an `int`. Exceptions do not allow this.

If you `throw 'A';` (a char), a catch block defined as `catch(int x)` will ignore it, even though a char is technically just a small number.

---

## Why? (Safety and Determinism)

The quote mentions "safety and determinism." Here is why strictness is safer:

**Scenario:** Imagine you have two catch blocks:

- `catch (int error_code)`: Handles system error numbers.
- `catch (double temperature)`: Handles temperature sensor readings.

If you throw `10` (an integer error code), and C++ allowed implicit conversion:

- The compiler might see the double catcher first and say, "Hey, 10 fits into a double!"
- Your error code would accidentally be caught by the temperature handler.
- The system would try to process your error as a temperature, leading to confusing bugs.

By disabling conversion, C++ ensures that an `int` is always handled by the `int` handler, eliminating ambiguity (determinism).

---

## The ONLY Exceptions to the Rule

While C++ is strict about numbers, it does allow three specific types of "adjustments" that are considered safe:

1. **Const Qualification:** `throw "Error"` (non-const) can be caught by `catch (const char*)`.
2. **Array/Function Decay:** Arrays convert to pointers (just like in function calls).
3. **Inheritance (Crucial):** A Child class object can be caught by a Parent class handler.
   - If you throw a `std::runtime_error`, it can be caught by `catch (std::exception)`.

---

## Catch Block Example

```cpp
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
```

---

## What Conversions Are Allowed?

| Conversion Type              | Allowed? |
|------------------------------|----------|
| Exact Match                  | ✅ Yes   |
| Promotion                    | ❌ No    |
| Standard Conversion          | ❌ No    |
| User-Defined Conversion      | ❌ No    |
| Ellipsis (...)               | ✅ Yes   |

---

## 1. Exact Match (Allowed)

This is the gold standard. If you throw an `int`, you catch an `int`.

```cpp
throw 10;      // Caught by catch(int)
throw "Error"; // Caught by catch(const char*)
```

---

## 2. Promotion (NOT Allowed)

In normal code, a `char` is automatically "promoted" to an `int` for math. In exceptions, this is disabled.

```cpp
char c = 'A';
try {
    throw c; // Throwing a char
}
catch (int x) { 
    // FAIL: This will NOT catch it. 
    // In normal functions this works, but here it is strictly forbidden.
}
```

---

## 3. Standard Conversion (NOT Allowed for Numbers)

In normal code, an `int` converts to a `double`. In exceptions, this is disabled.

```cpp
try {
    throw 10; // Throwing an int
}
catch (double d) {
    // FAIL: 10 is not converted to 10.0.
}
```

### The "Inheritance" Exception

There is one specific type of standard conversion that IS allowed: **Derived-to-Base**.

If you throw a Child object, it CAN be caught by a Parent handler.

```cpp
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
```

**Why this works:** The compiler sees that `ConnectionTimeout` is a `ServerError`, so the catch block accepts it.

---

## Pointer Conversion: char* to void*

If you throw a `char*` (string), it CAN be caught by `void*`.

C++ allows any non-const data pointer to be caught by a `void*` (a generic pointer), because `void*` is the "universal" pointer type in C++.

**Note:** This does not work for `const char*` (string literals like "hello"), only for mutable `char*` variables.

```cpp
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
```

**Why this works:** `char*` automatically converts to `void*` in standard C++. The exception system respects this specific pointer conversion.

---

## 4. User-Defined Conversion (NOT Allowed)

Even if you have a class that can be created from an integer, the exception system won't do it for you.

```cpp
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
```

---

## 5. Ellipsis (...) (Allowed)

This is a special C++ feature (often called "catch-all"). It matches any type of exception, no matter what the signal is.

```cpp
try {
    throw 500;
}
catch (...) {
    // SUCCESS: This catches anything.
}
```

---

## What Catch Blocks Typically Do

If an exception is routed to a catch block, it is considered "handled" even if the catch block is empty. However, typically you'll want your catch blocks to do something useful. There are four common things that catch blocks do when they catch an exception:

1. **Print an error** (either to the console, or a log file) and then allow the function to proceed.

2. **Return a value or error code** back to the caller.

3. **Throw another exception.** Because the catch block is outside of the try block, the newly thrown exception in this case is not handled by the preceding try block -- it's handled by the next enclosing try block.

4. A **catch block in main()** may be used to catch fatal errors and terminate the program in a clean way.

---

## Key Insight

**Try blocks catch exceptions not only from statements within the try block, but also from functions that are called within the try block.**

```cpp
#include <cmath> // for sqrt() function
#include <iostream>

// A modular square root function
double mySqrt(double x)
{
    // If the user entered a negative number, this is an error condition
    if (x < 0.0)
        throw "Can not take sqrt of negative number"; // throw exception of type const char*

    return std::sqrt(x);
}

int main()
{
    std::cout << "Enter a number: ";
    double x {};
    std::cin >> x;

    try // Look for exceptions that occur within try block and route to attached catch block(s)
    {
        double d = mySqrt(x);
        std::cout << "The sqrt of " << x << " is " << d << '\n';
    }
    catch (const char* exception) // catch exceptions of type const char*
    {
        std::cerr << "Error: " << exception << std::endl;
    }

    return 0;
}
```

### Why Pass Errors Back to the Caller?

At this point, some of you are probably wondering why it's a good idea to pass errors back to the caller. Why not just make `MySqrt()` handle its own error? The problem is that different applications may want to handle errors in different ways:

- A console application may want to print a text message.
- A Windows application may want to pop up an error dialog.
- In one application, this may be a fatal error, and in another application it may not be.

By passing the error out of the function, each application can handle an error from `mySqrt()` in a way that is the most context appropriate for it! Ultimately, this keeps `mySqrt()` as modular as possible, and the error handling can be placed in the less-modular parts of the code.

**Additional Note:** If you catch and handle an exception in the same function where it's thrown, it's normal that you don't continue execution there because you've completed the work and you have an error you don't want. It's like you're no longer giving consideration to the crash. The important thing is that **exception is exceptional**.

---

## Exception Handling and Stack Unwinding

The program first looks to see if the exception can be handled immediately inside the current function (meaning the exception was thrown within a try block inside the current function, and there is a corresponding catch block associated).

If not, the program next checks whether the function's caller (the next function up the call stack) can handle the exception. In order for the function's caller to handle the exception, the call to the current function must be inside a try block, and a matching catch block must be associated.

If no match is found, then the caller's caller (two functions up the call stack) is checked. Similarly, in order for the caller's caller to handle the exception, the call to the caller must be inside a try block, and a matching catch block must be associated.

The process of checking each function up the call stack continues until either a handler is found, or all of the functions on the call stack have been checked and no handler can be found.

### Important Notes:

- **If a matching exception handler is found**, then execution jumps from the point where the exception is thrown to the top of the matching catch block. This requires unwinding the stack (removing the current function from the call stack) as many times as necessary to make the function handling the exception the top function on the call stack.

- **If no matching exception handler is found**, the stack may or may not be unwound. We will talk more about this case in the next section (Uncaught exceptions and catch-all handlers).

- **When the current function is removed from the call stack**, all local variables are destroyed as usual, but no value is returned.

### Key Insight

**Unwinding the stack destroys local variables in the functions that are unwound** (which is good, because it ensures their destructors execute).

---

## Stack Unwinding Example

```cpp
#include <iostream>

void D() // called by C()
{
    std::cout << "Start D\n";
    std::cout << "D throwing int exception\n";

    throw -1;

    std::cout << "End D\n"; // skipped over
}

void C() // called by B()
{
    std::cout << "Start C\n";
    D();
    std::cout << "End C\n";
}

void B() // called by A()
{
    std::cout << "Start B\n";

    try
    {
        C();
    }
    catch (double) // not caught: exception type mismatch
    {
        std::cerr << "B caught double exception\n";
    }

    try
    {
    }
    catch (int) // not caught: exception not thrown within try
    {
        std::cerr << "B caught int exception\n";
    }

    std::cout << "End B\n";
}

void A() // called by main()
{
    std::cout << "Start A\n";

    try
    {
        B();
    }
    catch (int) // exception caught here and handled
    {
        std::cerr << "A caught int exception\n";
    }
    catch (double) // not called because exception was handled by prior catch block
    {
        std::cerr << "A caught double exception\n";
    }

    // execution continues here after the exception is handled
    std::cout << "End A\n";
}

int main()
{
    std::cout << "Start main\n";

    try
    {
        A();
    }
    catch (int) // not called because exception was handled by A
    {
        std::cerr << "main caught int exception\n";
    }
    std::cout << "End main\n";

    return 0;
}
```

As you can see, stack unwinding provides us with some very useful behavior -- if a function does not want to handle an exception, it doesn't have to. The exception will propagate up the stack until it finds someone who will! This allows us to decide where in the call stack is the most appropriate place to handle any errors that may occur.

---
## Itanium C++ ABI

It is a binary-level contract that defines how C++ features work at the machine/runtime level on most Unix-like systems (GCC, Clang on Linux and macOS).

It specifies:

    * Name mangling rules
    * Object layout
    * Virtual table layout
    * RTTI structure

    Exception handling mechanism

## What is `__cxa_allocate_exception`?

It is a runtime library function defined by the **Itanium C++ ABI** (used by GCC & Clang on Linux/macOS).

### Its Job:

Allocate memory for an exception object that must survive stack unwinding.

### In Simple Words:

It allocates space where the thrown object will live outside the stack.

```
┌──────────────────────────────┐
│ ABI exception header         │  ← used by runtime
│------------------------------│
│ type_info*                   │
│ destructor pointer           │
│ handler count                │
└──────────────────────────────┘
│ user exception object        │
│ std::runtime_error           │
│ vptr + message               │
└──────────────────────────────┘
```

### This Memory Is:

- Not stack
- Not regular `new`
- Controlled by the C++ runtime

### Why Not Just Use `new`?

Because exceptions need extra metadata:

    - RTTI (`type_info`)
    - Destructor callback
    - Handler tracking
    - Thread-local chaining

`new` only allocates raw memory — it doesn't integrate with:

    - Stack unwinding
    - Landing pads
    - Catch matching

---

## What `__cxa_throw` Really Does (Important)

Conceptually, `__cxa_throw` does this:

```cpp
void __cxa_throw(void* obj, type_info* tinfo, destructor dtor) {
    _Unwind_RaiseException(exception_object);
    std::terminate(); // only if no handler found
}
```

### So the Real Unwinder Is:

**`_Unwind_RaiseException`** - This is part of the Itanium C++ ABI (used by Clang/GCC).

---

## Final Mental Timeline (Source → Runtime)

```
throw -1
↓
__cxa_allocate_exception (heap)
↓
store int value
↓
attach typeinfo(int)
↓
__cxa_throw
↓
destroy D frame
↓
destroy C frame
↓
check B handlers → no match
↓
check A handlers → MATCH
↓
execute catch(int)
↓
resume normal execution
```

### Putting It All Together:

```
throw -1
↓
VISIBLE ASM:
    call __cxa_allocate_exception
    call __cxa_throw
↓
INVISIBLE RUNTIME:
    _Unwind_RaiseException
↓
METADATA:
    .eh_frame + personality functions
↓
MEMORY:
    destroy stack frames
    keep heap exception alive
↓
CONTROL FLOW:
    jump to landing pad
↓
NORMAL EXECUTION RESUMES
```

---

## Summary

C++ exception handling provides a robust mechanism for error handling with:

- Type-safe exception matching
- Automatic stack unwinding
- Proper resource cleanup through destructors
- Flexible error propagation up the call stack

Remember: exceptions are for exceptional circumstances, not regular control flow!

## Uncaught exceptions

```cpp
class A : public B
{
    public:
        A(void)
        : B()
        {
        }
        catch(float a)
        {
            std::cout << "oops\n";
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
```
```cpp
class A : public B
{
    public:
        A(void)
        : B()
        {
        }
        catch(float a)
        {
            std::cout << "oops\n";
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

    f();
    std::cout << "sucess " << a << "\n";
}
```

## Exceptions and member functions: (IMPORTANT)


---

## What are Exception Classes?

**Exception classes are special classes used to represent errors.**

In C++, you throw and catch these to handle problems gracefully. For example:

```cpp
class MyException : public std::exception {
    // This is an exception class
};
```

---

## Why This Exception?

**Exception classes are typically:**

- Lightweight objects used temporarily during error handling.
- Often thrown and caught by value or reference.
- Designed to carry error information, not manage resources.

The exception classes are simple and don't need the full OCF treatment - they just need to inherit from `std::exception` and override the `what()` method.

---