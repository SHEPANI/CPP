# C++ Templates — Complete Guide
### Based on ISO/IEC 14882:1998(E) — *Programming Languages — C++* (C++98)

> **"A template defines a family of classes or functions."**
> — §14, ISO/IEC 14882:1998

---

## Table of Contents

1. [What Is a Template?](#1-what-is-a-template)
2. [Template Parameters](#2-template-parameters)
   - [Type Parameters](#21-type-parameters)
   - [Non-Type Parameters](#22-non-type-parameters)
   - [Template Template Parameters](#23-template-template-parameters)
   - [Default Template Arguments](#24-default-template-arguments)
3. [Class Templates](#3-class-templates)
   - [Defining a Class Template](#31-defining-a-class-template)
   - [Member Functions Outside the Class](#32-member-functions-outside-the-class)
   - [Member Classes](#33-member-classes)
   - [Static Data Members](#34-static-data-members)
4. [Function Templates](#4-function-templates)
   - [Basic Function Template](#41-basic-function-template)
   - [Function Template Overloading](#42-function-template-overloading)
   - [Partial Ordering of Function Templates](#43-partial-ordering-of-function-templates)
5. [Member Templates](#5-member-templates)
6. [Template Arguments](#6-template-arguments)
   - [Type Arguments](#61-type-arguments)
   - [Non-Type Arguments](#62-non-type-arguments)
   - [Template Template Arguments](#63-template-template-arguments)
7. [Template Specialization](#7-template-specialization)
   - [Explicit (Full) Specialization](#71-explicit-full-specialization)
   - [Partial Specialization of Class Templates](#72-partial-specialization-of-class-templates)
8. [Template Instantiation](#8-template-instantiation)
   - [Implicit Instantiation](#81-implicit-instantiation)
   - [Explicit Instantiation](#82-explicit-instantiation)
9. [Name Resolution in Templates](#9-name-resolution-in-templates)
   - [Dependent Names and `typename`](#91-dependent-names-and-typename)
   - [Non-Dependent Names](#92-non-dependent-names)
10. [Friends in Templates](#10-friends-in-templates)
11. [Type Equivalence](#11-type-equivalence)
12. [Common Pitfalls & Rules Summary](#12-common-pitfalls--rules-summary)

---

## 1. What Is a Template?

A **template** is a blueprint for generating a family of related classes or functions. Instead of writing the same code many times for different types, you write it once with a *type placeholder*, and the compiler generates the real code when you use it.

**Without templates — repetitive code:**
```cpp
int    max_int   (int a,    int b)    { return a > b ? a : b; }
double max_double(double a, double b) { return a > b ? a : b; }
// ...one function per type, forever
```

**With a template — write it once:**
```cpp
template<class T>
T max(T a, T b) { return a > b ? a : b; }

int    r1 = max(3, 5);       // T = int    (compiler generates max<int>)
double r2 = max(1.2, 3.4);   // T = double (compiler generates max<double>)
```

### Syntax

```
exportopt template < template-parameter-list > declaration
```

A `template-declaration` can:
- Declare or define a **function** or **class**
- Define a **member function**, member class, or static data member of a class template
- Define a **member template** of a class or class template

---

## 2. Template Parameters

There are exactly **three kinds** of template parameters.

### 2.1 Type Parameters

The most common kind. Written with `class` or `typename` — there is **no semantic difference** between the two keywords here.

```cpp
template<class T>    class Box { T value; };   // T is a type
template<typename T> class Box { T value; };   // identical meaning
```

**Multiple type parameters:**
```cpp
template<class Key, class Value>
class Map {
    Key   k;
    Value v;
};

Map<int, string> phonebook;   // Key=int, Value=string
```

**Type parameter used as a base class:**
```cpp
template<class T>
class Wrapper : public T {    // T must be a defined class at instantiation
    // ...
};
```

---

### 2.2 Non-Type Parameters

A **non-type parameter** is a *value* — not a type. It must be one of:
- Integral or enumeration type
- Pointer to object or pointer to function
- Reference to object or reference to function
- Pointer to member

> **Not allowed:** floating-point, class, or void types as non-type parameters.

```cpp
// Integral non-type parameter
template<int N>
class FixedArray {
    int data[N];
};

FixedArray<10> a;    // N = 10; array of 10 ints
FixedArray<256> b;   // N = 256; array of 256 ints
```

```cpp
// Pointer non-type parameter
template<int* p>
struct R { /* ... */ };

int* ptr;
R<ptr> r;    // OK: pointer with external linkage
```

```cpp
// Reference non-type parameter
template<const int& CRI>
struct B { /* ... */ };

int c = 1;
B<c> b;      // OK: bound directly to c

B<1> err;    // ERROR: temporary would be required
```

**Non-type parameters are compile-time constants** — you cannot modify them:
```cpp
template<int i>
void f() {
    i++;     // ERROR: cannot change a non-type template parameter
}
```

---

### 2.3 Template Template Parameters

A parameter that is itself a **class template**. This lets you pass a template as an argument to another template.

```cpp
template<class T> class myarray { /* ... */ };

template<class K, class V, template<class T> class Container = myarray>
class Map {
    Container<K> keys;
    Container<V> values;
};

Map<int, string>           m1;   // uses default: myarray
Map<int, string, vector>   m2;   // Container = vector
```

> **Rule:** Only **primary** class templates are accepted as template template arguments — not partial specializations.

---

### 2.4 Default Template Arguments

Any kind of template parameter may have a **default value**, just like default function arguments.

```cpp
template<class T = int, int N = 10>
class Buffer {
    T data[N];
};

Buffer<>          b1;   // T=int,   N=10  (both defaults)
Buffer<double>    b2;   // T=double, N=10 (one default)
Buffer<char, 256> b3;   // no defaults used
```

**Rules for defaults:**
- Once a parameter has a default, all *following* parameters must also have defaults.
- Default arguments can only be given in class template declarations, not in function template declarations.
- A parameter may not be given a default in two different declarations in the same scope.

```cpp
template<class T1, class T2 = int> class A;   // OK
template<class T1 = int, class T2> class A;   // OK (merged with the above)
// Together they are equivalent to:
template<class T1 = int, class T2 = int> class A;

template<class T1 = int, class T2> class B;   // ERROR: T2 has no default
```

---

## 3. Class Templates

### 3.1 Defining a Class Template

A **class template** defines an unbounded family of related types. Think of it as a parameterized blueprint.

```cpp
template<class T>
class Array {
    T*  v;
    int sz;
public:
    explicit Array(int size);
    T& operator[](int i);
    T& elem(int i) { return v[i]; }
    // ...
};

Array<int>     v1(20);    // an Array of ints
Array<double>  v2(30);    // an Array of doubles
Array<string>  v3(5);     // an Array of strings

v1[3] = 7;
v2[0] = 3.14;
```

The prefix `template<class T>` declares `T` as the type parameter. `Array` is now a *parameterized type* — you must supply the type when using it.

---

### 3.2 Member Functions Outside the Class

Member functions can be defined **outside** the class template definition. Repeat the `template<...>` prefix:

```cpp
template<class T>
T& Array<T>::operator[](int i) {
    if (i < 0 || sz <= i)
        error("Array: range error");
    return v[i];
}
```

When there are multiple type parameters, the parameter names in the out-of-class definition may differ, but the *order* must match:

```cpp
template<class T1, class T2>
struct A {
    void f1();
    void f2();
};

template<class T2, class T1>
void A<T2, T1>::f1() { }       // OK: order matches primary template

template<class T2, class T1>
void A<T1, T2>::f2() { }       // ERROR: order swapped
```

---

### 3.3 Member Classes

A nested class of a class template can be defined outside the enclosing template definition:

```cpp
template<class T>
struct Outer {
    class Inner;    // forward declaration
};

// OK: requires Outer to be defined, but not Outer::Inner
Outer<int>::Inner* p1;

// Define Inner outside:
template<class T>
class Outer<T>::Inner { /* ... */ };

// Now Inner is fully defined:
Outer<int>::Inner obj;
```

---

### 3.4 Static Data Members

Static data members of class templates are defined at namespace scope with their own `template<...>` prefix:

```cpp
template<class T>
class X {
    static T s;    // declaration
};

template<class T>
T X<T>::s = 0;    // definition

// Each instantiation gets its own copy:
X<int>   a;       // X<int>::s   is int,   initialized to 0
X<char*> b;       // X<char*>::s is char*, initialized to 0
```
// TODO : template instantiation.
---

## 4. Function Templates

### 4.1 Basic Function Template

A **function template** defines a family of related functions. The compiler deduces the template arguments from the function arguments — you usually don't need to specify them explicitly.

```cpp
template<class T>
T max(T a, T b) {
    return a > b ? a : b;
}

int    r1 = max(3, 7);         // T deduced as int
double r2 = max(1.5, 2.7);     // T deduced as double
```

**Explicit argument specification** (when deduction is ambiguous or impossible):
```cpp
template<class T>
void print() { /* prints type name */ }

print<int>();      // T = int, explicit — cannot be deduced from arguments
```

---

### 4.2 Function Template Overloading

Function templates can be overloaded with each other and with non-template functions:

```cpp
// Two different function templates with the same name:
template<class T> void f(T);    // #1: general
template<class T> void f(T*);   // #2: pointer specialization

int x = 5;
f(x);    // calls #1 with T=int
f(&x);   // calls #2 with T=int  (f<int>(int*))
```

```cpp
// In different translation units:
// file1.cpp                     file2.cpp
template<class T> void f(T*);   template<class T> void f(T);
void g(int* p) {                 void h(int* p) {
    f(p);  // calls f<int>(int*) f(p);  // calls f<int*>(int*)
}                                }
```

The **signature** of a function template includes: its function signature, return type, and template parameter list. Parameter *names* don't matter — only their structure does.

---

### 4.3 Partial Ordering of Function Templates

When multiple templates match a call, the compiler picks the **most specialized** one.

```cpp
template<class T> void f(T);          // A: most general
template<class T> void f(T*);         // B: more specialized (pointer)
template<class T> void f(const T*);   // C: most specialized (const pointer)

const int* p;
f(p);   // calls C: f(const T*) is more specialized than B or A
```

```cpp
template<class T> void h(const T&);   // A
template<class T> void h(Array<T>&);  // B: more specialized

Array<int>       z1;
h(z1);    // calls B: h(Array<T>&) is more specialized

const Array<int> z2;
h(z2);    // calls A: h(Array<T>&) is not callable for const
```

> **Rule:** Template A is *more specialized* than B if A can handle every type B handles, but B cannot handle every type A handles.

---

## 5. Member Templates

A template can be declared **inside** a class or class template — this is called a **member template**.

```cpp
template<class T>
class string {
public:
    // Member function template: compare with any type T2
    template<class T2>
    int compare(const T2& s);

    // Member constructor template
    template<class T2>
    string(const string<T2>& s) { /* ... */ }
};

// Define outside — need both template-parameter-lists:
template<class T>
template<class T2>
int string<T>::compare(const T2& s) {
    // ...
}
```

**Usage — non-template and template with same name:**
```cpp
template<class T>
struct A {
    void f(int);               // non-template
    template<class T2> void f(T2); // template
};

A<char> ac;
ac.f(1);      // calls non-template f(int)
ac.f('c');    // calls template f<char>
ac.f<>(1);    // explicitly calls the template version
```

**Restrictions on member templates:**
- A member function template **cannot be virtual**.
- A destructor **cannot** be a member template.
- A local class cannot have member templates.

```cpp
template<class T>
struct AA {
    template<class C> virtual void g(C);   // ERROR: virtual member template
    virtual void f();                       // OK: normal virtual function
};
```

---

## 6. Template Arguments

### 6.1 Type Arguments

A type argument must be a **type-id**. The following are **not** allowed as type arguments:
- Local types (defined inside a function)
- Types with no linkage
- Unnamed types

```cpp
template<class T> class X { /* ... */ };

void f() {
    struct Local { };       // local type

    X<Local>  err1;         // ERROR: local type
    X<Local*> err2;         // ERROR: pointer to local type
}

X<int>    ok1;     // OK
X<string> ok2;     // OK
```

---

### 6.2 Non-Type Arguments

Non-type arguments must be **compile-time constants** and must match the parameter's type. The standard allows these forms:

```cpp
// 1. Integral constant expression
template<int N> class A { };
A<42>    a;        // OK: integer literal
A<2+3>   b;        // OK: constant expression

// 2. Address of external object (with &, optional for arrays/functions)
template<int* p> class B { };
int arr[10];
B<arr>   c;        // OK: array name = pointer
B<&arr[0]> err;    // ERROR: address of array element

// 3. Static member address
struct S { static int x; };
template<int*> class C { };
C<&S::x> d;        // OK: address of static member

// 4. String literals are NOT valid (internal linkage)
template<char* p> class D { };
D<"hello"> err2;        // ERROR: string literal has internal linkage

char greeting[] = "hello";
D<greeting> e;          // OK: named external array
```

---

### 6.3 Template Template Arguments

A template template argument must be the **name of a primary class template**:

```cpp
template<class T> class A {       // primary template
    int x;
};
template<class T> class A<T*> {   // partial specialization
    long x;
};

// Template template parameter:
template<template<class U> class V>
class C {
    V<int>  y;    // uses primary template → y.x is int
    V<int*> z;    // uses partial specialization → z.x is long
};

C<A> c;           // V = A (primary template)
```

> Only the **primary** template name is accepted; partial specializations are not. But when the template is instantiated inside `C`, the matching specialization (including partial specializations) is automatically selected.

---

## 7. Template Specialization

Sometimes the generic template does the wrong thing for a specific type. **Specialization** lets you provide a custom implementation for particular arguments.

### 7.1 Explicit (Full) Specialization

Use `template<>` to specialize for a specific type:

```cpp
// Primary template
template<class T>
class stream {
    // general stream implementation
};

// Explicit specialization for char
template<>
class stream<char> {
    // optimized narrow-character implementation
};

stream<int>  s1;    // uses primary template
stream<char> s2;    // uses the explicit specialization
```

**Function template specialization:**
```cpp
template<class T>
class Array { /* ... */ };

template<class T>
void sort(Array<T>& v) { /* general sort */ }

// Special sort for char* arrays:
template<>
void sort<char*>(Array<char*>& v) { /* fast string sort */ }
```

**Specializing a member:**
```cpp
template<class T>
struct A {
    void f(T) { /* general */ }
};

// Specialize just the member for int:
template<>
void A<int>::f(int) { /* fast int version */ }
```

> **Rule:** An explicit specialization must be declared **before** the first use of that specialization that would trigger implicit instantiation.

---

### 7.2 Partial Specialization of Class Templates

Partial specialization provides a custom definition for a **subset** of argument combinations. Only class templates (not function templates) support partial specialization.

```cpp
// Primary template — 3 parameters
template<class T1, class T2, int I>
class A { };                            // #1 general

// Partial specializations:
template<class T, int I>
class A<T, T*, I> { };                  // #2 when T2 is T*

template<class T1, class T2, int I>
class A<T1*, T2, I> { };                // #3 when T1 is a pointer

template<class T>
class A<int, T*, 5> { };                // #4 when T1=int, T2=T*, I=5

// Using them:
A<int, int, 1>    a1;    // uses #1 (no partial match)
A<int, int*, 1>   a2;    // uses #2 (T=int, I=1)
A<int, char*, 5>  a3;    // uses #4 (T=char)
A<int, char*, 1>  a4;    // uses #3 and #5... could be ambiguous
```

**Matching rules:**
1. Find all partial specializations that match the given arguments.
2. If exactly one matches — use it.
3. If multiple match — use the *most specialized* (partial ordering rules).
4. If none match — use the primary template.
5. If two or more match and neither is more specialized — **program is ill-formed** (ambiguous).

**Restrictions on partial specialization argument lists:**
```cpp
template<int I, int J> struct B {};
template<int I> struct B<I, I> {};    // OK: both params same value

template<int I, int J> struct C {};
template<int I> struct C<I+5, I*2> {};  // ERROR: expression in argument
```

---

## 8. Template Instantiation

**Instantiation** is the act of generating a real class or function from a template by substituting actual arguments for template parameters.

### 8.1 Implicit Instantiation

The compiler instantiates a template **automatically** when it needs the complete definition. You don't have to do anything special.

```cpp
template<class T>
class Z {
public:
    void f();
    void g();
};

void h() {
    Z<int>   a;      // Z<int> is implicitly instantiated (complete type needed)
    Z<char>* p;      // Z<char> is NOT instantiated (pointer only, no complete type needed)

    a.f();           // Z<int>::f() is instantiated (function call needs definition)
    p->g();          // Z<char> IS instantiated (member call needs complete type)
                     // Z<char>::g() is instantiated too
}
// Z<int>::g(), Z<char>::f(), and Z<double> are never instantiated
```

**Implicit instantiation and static members:**
- Implicit instantiation of a class template does **not** instantiate static data members — only when the static member itself is actually used.

---

### 8.2 Explicit Instantiation

You can force the compiler to instantiate a template in a specific translation unit. This is useful to avoid having the same instantiation in many object files.

```cpp
template<class T> class Array { void mf(); };
template<class T> void sort(Array<T>& v) { /* ... */ }

// Force instantiation:
template class Array<char>;         // instantiate Array<char> and all its members
template void Array<int>::mf();     // instantiate only this member function
template void sort(Array<char>&);   // instantiate sort for Array<char> (T deduced)

// Explicit instantiation in a namespace:
namespace N {
    template<class T> class Y { void mf() { } };
}
template class N::Y<char*>;         // OK: in namespace N
```

> **Rule:** Do not explicitly instantiate the same template more than once, and do not both explicitly instantiate and explicitly specialize the same template for the same arguments.

---

## 9. Name Resolution in Templates

Inside a template, names are resolved at two different points:
- **Non-dependent names**: resolved at the *point of the template definition*.
- **Dependent names** (names that depend on a template parameter): resolved at the *point of instantiation*.

### 9.1 Dependent Names and `typename`

When a name inside a template depends on a template parameter and refers to a **type**, you must use the `typename` keyword:

```cpp
template<class T>
class Y {
    void f() {
        typename T::A* pa;    // T::A is a type — typename required
        T::A* err;            // ERROR: T::A treated as a value; this is multiplication!
    }
};
```

Without `typename`, `T::A` is assumed to be a **value** (non-type), not a type.

**Using a member template with `template` keyword:**
```cpp
class X {
public:
    template<size_t N> X* alloc();
};

template<class T>
void f(T* p) {
    T* p1 = p->alloc<200>();            // ERROR: < is treated as less-than
    T* p2 = p->template alloc<200>();   // OK: template keyword clarifies
}
```

**Common pattern — typedef through `typename`:**
```cpp
template<class T>
class Container {
public:
    typedef typename T::value_type value_type;
    // T::value_type depends on T, so typename is needed
};
```

---

### 9.2 Non-Dependent Names

Names that do **not** depend on template parameters are bound **immediately** at the point of definition — not at instantiation:

```cpp
void g(double);

template<class T>
class Z {
    void f() {
        g(1);     // binds to g(double) immediately — at template definition
                  // g(int) declared later is NOT considered
    }
};

void g(int);   // defined after the template — not visible to the template's g(1) call
```

---

## 10. Friends in Templates

Friends can be:
- A specific specialization of a template
- An entire template family
- An ordinary non-template function or class

```cpp
template<class T> class task;
template<class T> task<T>* preempt(task<T>*);

template<class T>
class task {
    friend void next_time();                    // non-template friend; every task<T> has it
    friend void process(task<T>*);              // friend matched by type; not a template specialization
    friend task<T>* preempt<T>(task<T>*);       // specific specialization of preempt
    template<class C> friend int func(C);       // all specializations of func are friends

    friend class task<int>;                     // specific instantiation as friend
    template<class P> friend class frd;         // all specializations of frd are friends
};
```

**Friend template definitions inside a class:**
```cpp
class A {
    template<class T> friend class B;               // OK: all B<T> are friends
    template<class T> friend void f(T) { /* ... */ }  // OK: defined inline
};
```

**Restrictions:**
- A friend template **cannot be declared in a local class**.
- Friend declarations **cannot declare partial specializations**.
- A friend class template **cannot be defined** inside the class that grants friendship (only declared).

```cpp
template<class T> class A { };
class X {
    template<class T> friend class A<T*>;   // ERROR: partial specialization as friend
};
```

---

## 11. Type Equivalence

Two template specializations refer to the **same type** (or function) when all their arguments are equivalent:

```cpp
template<class E, int size>
class buffer { /* ... */ };

buffer<char, 2*512> x;    // same type as...
buffer<char, 1024>  y;    // ...this: 2*512 == 1024
```

```cpp
template<class T, void(*err_fct)()>
class list { /* ... */ };

list<int, &error_handler1> x1;
list<int, &error_handler2> x2;
list<int, &error_handler2> x3;   // same type as x2
list<char, &error_handler2> x4;  // different: T is char

// x2 and x3 are the same type
// x1 differs from x2 (different pointer value)
// x4 differs from x2 (different type T)
```

---

## 12. Common Pitfalls & Rules Summary

### ✅ Things that work

```cpp
// Default type parameter
template<class T = char> class String;
String<> s;          // OK: String<char>

// Empty template argument list with default:
String* err;         // ERROR: must write String<>

// Using a previously-declared template parameter in a later one:
template<class T, T* p, class U = T> class X { };
```

### ❌ Common errors

```cpp
// 1. Specifying template-id in primary template declaration
template<class T> class A<T> { };         // ERROR: use just class A { };

// 2. Floating-point non-type parameter
template<double d> class X;               // ERROR
template<double* pd> class Y;             // OK: pointer is fine

// 3. String literal as non-type argument
template<char* p> class Z { };
Z<"hello"> z;                             // ERROR: string literal = internal linkage

// 4. Local type as type argument
void f() {
    struct Local { };
    vector<Local> v;                      // ERROR: local type
}

// 5. Missing typename for dependent type name
template<class T>
void g() {
    T::iterator it;              // ERROR: T::iterator assumed to be a value
    typename T::iterator it2;    // OK
}

// 6. Virtual member template
template<class T> struct S {
    template<class U> virtual void f(U);  // ERROR: cannot be virtual
};

// 7. Giving default template argument to function template
template<class T = int> void h(T);    // ERROR: not allowed for function templates
```

### Quick Reference

| Feature | Class Template | Function Template |
|---|---|---|
| Default arguments | ✅ Allowed | ❌ Not allowed |
| Partial specialization | ✅ Allowed | ❌ Not allowed |
| Explicit (full) specialization | ✅ Allowed | ✅ Allowed |
| `export` keyword | ✅ Allowed | ✅ Allowed |
| Overloading | ❌ Must be unique name (except 14.5.4) | ✅ Can overload |
| Virtual member template | — | ❌ Not allowed |

---

## Grammar Summary (Annex A.12)

```
template-declaration:
    exportopt template < template-parameter-list > declaration

template-parameter-list:
    template-parameter
    template-parameter-list , template-parameter

template-parameter:
    type-parameter
    parameter-declaration          ← non-type parameter

type-parameter:
    class identifieropt
    class identifieropt = type-id
    typename identifieropt
    typename identifieropt = type-id
    template < template-parameter-list > class identifieropt
    template < template-parameter-list > class identifieropt = id-expression

template-id:
    template-name < template-argument-listopt >

template-name:
    identifier

template-argument-list:
    template-argument
    template-argument-list , template-argument

template-argument:
    assignment-expression          ← non-type argument
    type-id                        ← type argument
    id-expression                  ← template template argument

explicit-instantiation:
    template declaration

explicit-specialization:
    template < > declaration
```

---

*Source: ISO/IEC 14882:1998(E) — Programming Languages — C++, Chapter 14 (§14.1–§14.8), First edition 1998-09-01. 776 pages.*
