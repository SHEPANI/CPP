# The Four C++ Casts — A Complete Plain-English Guide

> Based on **ISO/IEC 14882:1998 — the C++98 Standard**

---

## Table of Contents

- [Why Does C++ Have Four Separate Cast Operators?](#-why-does-c-have-four-separate-cast-operators)
- [1. `static_cast` — §5.2.9](#1-static_cast--529)
- [2. `dynamic_cast` — §5.2.7](#2-dynamic_cast--527)
- [3. `const_cast` — §5.2.11](#3-const_cast--5211)
- [4. `reinterpret_cast` — §5.2.10](#4-reinterpret_cast--5210)
- [5. `uintptr_t` — Not in C++98](#5-uintptr_t--not-in-c98)
- [Summary Table](#-summary-table)
- [The Old-Style (C-Style) Cast — §5.4](#-the-old-style-c-style-cast--54)
  - [What It Is](#what-it-is-1)
  - [Three Ways to Write an Explicit Conversion](#three-ways-to-write-an-explicit-conversion)
  - [The Result Type: lvalue or rvalue?](#the-result-type-lvalue-or-rvalue)
  - [The Core Rule: What Can It Actually Do?](#the-core-rule-what-can-it-actually-do)
  - [The Ambiguity Rule and When It's Ill-Formed](#the-ambiguity-rule-and-when-its-ill-formed)
  - [The Special Rule for Incomplete Class Types](#the-special-rule-for-incomplete-class-types)
  - [The Access Bypass — C-Style Cast's Unique Superpower](#the-access-bypass--c-style-casts-unique-superpower)
  - [The Strict Aliasing Trap (§3.10 §15)](#the-strict-aliasing-trap-3101-15)
  - [User-Defined Conversions and the Cast](#user-defined-conversions-and-the-cast)
  - [Full Priority Walk-Through](#full-priority-walk-through-what-the-compiler-actually-does)
  - [The "Same Semantics" Guarantee](#the-same-semantics-guarantee)
  - [C-Style vs Named Casts Summary](#summary-c-style-vs-named-casts)

---

## 🗺️ Why Does C++ Have Four Separate Cast Operators?

Before C++ had its own cast operators, programmers used the old C-style cast:

```cpp
int x = (int)someValue;
```

The C++98 standard still allows this (Section 5.4), but notes that the C-style cast quietly does whichever of the named casts would apply — in order:

1. `const_cast`
2. `static_cast`
3. `static_cast` + `const_cast`
4. `reinterpret_cast`
5. `reinterpret_cast` + `const_cast`

If it can be interpreted in more than one way as a `static_cast` + `const_cast`, it's outright ill-formed. **The C-style cast is ambiguous and silent about what it actually does.**

The named casts fix this. Each one has one specific job, and the compiler enforces that you're only asking for what that cast is allowed to do. They exist so that dangerous conversions are **visible and intentional**, not hidden.

---

## 1. `static_cast` — §5.2.9

### What It Is

The workhorse of safe, compile-time conversions. It says: *"I know these two types are related in a way the compiler can verify statically — just do the conversion."*

```cpp
static_cast<T>(v)
```

- If `T` is a reference type, the result is an **lvalue** (you get a reference back).
- Otherwise it's an **rvalue**.
- You cannot define new types inside the cast.
- It **cannot cast away constness** — that's `const_cast`'s job.

### What It Can Do (Exhaustive List from the Standard)

**1. Any implicitly allowed conversion, in reverse.**

If the compiler would automatically convert type `A → B` (say, `int` to `double`), you can use `static_cast` to go `B → A` explicitly. Exception: you cannot reverse lvalue-to-rvalue, array-to-pointer, function-to-pointer, or boolean conversions.

```cpp
double d = 3.7;
int i = static_cast<int>(d); // double → int, truncates to 3
```

**2. Anything that could be initialized directly.**

If `T t(v);` would compile, then `static_cast<T>(v)` is legal. The effect is exactly the same as that declaration — the same constructors and conversion functions fire.

**3. Casting to void.**

Any expression can be explicitly cast to `void`, which just discards the value. (The standard notes the destructor for any temporary is still called at the normal time.)

```cpp
static_cast<void>(someExpression); // discard result explicitly
```

**4. Downcasting in a class hierarchy (without polymorphism).**

If `B` is a base class of `D`, and you have a `B*` that you know actually points to a `D` object, you can cast down:

```cpp
struct B {};
struct D : public B {};
D d;
B& br = d;
D& dr = static_cast<D&>(br); // produces lvalue to the original d object
```

> ⚠️ **The catch:** The standard says if the `B` lvalue isn't actually a sub-object of a `D`, the result is **undefined**. `static_cast` trusts you. It does no runtime check. If you're wrong, anything can happen. (If you need a safe checked downcast, use `dynamic_cast`.)

> **Restriction:** `B` must not be a virtual base class of `D` for this to be allowed.

**5. Pointer to `void*` and back.**

A pointer to any object can be converted to `void*`. And a `void*` can be converted back to a pointer to the original type. Round-tripping is guaranteed to give you the original pointer back.

```cpp
int x = 42;
void* vp = static_cast<void*>(&x);
int* ip = static_cast<int*>(vp); // ip == &x, guaranteed
```

**6. Integer ↔ enum.**

An integer can be explicitly converted to an enum type. If the value is within the enum's valid range, it is unchanged. Otherwise the result is unspecified.

**7. Pointer-to-member conversions (in the class hierarchy).**

A pointer to a member of a derived class `D` can be converted to a pointer to the same member via the base class `B`, and vice versa, subject to the same hierarchy validity rules.

---

## 2. `dynamic_cast` — §5.2.7

### What It Is

The safe, runtime-checked cast. It works only on **polymorphic types** (classes with at least one virtual function). At runtime, it actually looks up the object's true type and decides if the cast is valid. If it isn't, it fails gracefully instead of causing undefined behavior.

```cpp
dynamic_cast<T>(v)
```

- `T` must be a pointer or reference to a complete class type, or "pointer to cv void" (i.e. `void*`).
- Cannot cast away constness.
- Requires **RTTI** (Run-Time Type Information) to be available.

### What "Polymorphic" Means

The standard (§10.3) defines it explicitly: *"A class that declares or inherits a virtual function is called a polymorphic class."* If your class has no virtual functions, `dynamic_cast` cannot be used on it.

### The Three Outcomes

**Case 1: Upcasting (Derived → Base).** Always safe. `dynamic_cast` behaves identically to the implicit conversion — no runtime check needed. The standard says if `B` is an accessible, unambiguous base of `D`, and you cast from `D*` to `B*`, you just get a pointer to the `B` sub-object.

```cpp
struct B { virtual void f() {} };
struct D : B {};
D d;
B* bp = dynamic_cast<B*>(&d); // always works, same as B* bp = &d
```

**Case 2: Downcasting or cross-casting (runtime check).** At runtime, the implementation examines the most-derived object pointed to by `v` and checks if a valid path to type `T` exists. The logic (from §5.2.7 §8) is:

- If `v` points to a public base class sub-object of a `T` object, and there is exactly one such `T` object in the most-derived object, the result is a pointer to that `T` object. ✅
- Otherwise if the most-derived object has an unambiguous public base of type `T`, the result is a pointer to that `T` sub-object. ✅
- Otherwise: the cast **fails**. ❌

**Case 3: Casting to `void*`.** `dynamic_cast<void*>(v)` is special — it gives you a pointer to the **most derived object**. This lets you find where an object actually starts in memory, regardless of which base class pointer you're holding.

### What Happens on Failure

| Cast type | Failure result |
|-----------|---------------|
| Pointer cast | Returns `nullptr` — **always check the result!** |
| Reference cast | Throws `std::bad_cast` (§18.5.2), derived from `std::exception` |

```cpp
class A { virtual void f() {} };
class B { virtual void g() {} };
class D : public virtual A, private B {};

void g() {
    D d;
    B* bp = (B*)&d;       // C-style needed to break access protection
    A* ap = &d;           // fine: public derivation

    D& dr = dynamic_cast<D&>(*bp);  // FAILS — throws bad_cast
    ap = dynamic_cast<A*>(bp);      // FAILS — yields nullptr
    bp = dynamic_cast<B*>(ap);      // FAILS — private base
    ap = dynamic_cast<A*>(&d);      // SUCCEEDS
    bp = dynamic_cast<B*>(&d);      // FAILS
}
```

### Ambiguous Hierarchies

With diamond or multiple inheritance, `dynamic_cast` can also fail if the path to `T` is ambiguous — i.e. there are two `T` sub-objects and neither is uniquely reachable.

```cpp
class E : public D, public B {};
class F : public E, public D {};

void h() {
    F f;
    A* ap = &f;
    D* dp = dynamic_cast<D*>(ap);  // SUCCEEDS: finds unique A
    E* ep1 = dynamic_cast<E*>(ap); // SUCCEEDS
    // (E*)ap would be ill-formed — cast from virtual base
}
```

---

## 3. `const_cast` — §5.2.11

### What It Is

The **only** cast that can add or remove `const` (or `volatile`) qualifiers from a type. It changes nothing else about the type — no conversion, no reinterpretation. Its entire purpose is manipulating **cv-qualifiers** (`const` and `volatile`).

```cpp
const_cast<T>(v)
```

- If `T` is a reference type, the result is an **lvalue**; otherwise an **rvalue**.
- **Cannot** change any other aspect of the type (not a conversion tool — only for cv-qualifiers).

### What "Casting Away Constness" Means (§5.2.11 §8–11)

The standard gives a precise definition. For two pointer types `X1` and `X2`, casting from `X1` to `X2` casts away constness if there is no implicit conversion from the innermost cv-qualified version of `X1`'s pointed-to chain to the corresponding part of `X2`'s chain. In practice: you're removing a `const` or `volatile` that the implicit conversion system would not allow you to remove.

The same rule applies to reference casts and pointer-to-member casts.

### What It Can Do

**1. Add or remove `const`/`volatile` from a pointer.**

```cpp
const int* cp = &someInt;
int* p = const_cast<int*>(cp); // removes const
```

The result refers to the original object — no copy is made.

**2. Add or remove `const`/`volatile` from a reference.**

```cpp
const int x = 42;
int& r = const_cast<int&>(x); // removes const from reference
```

Again, refers to the original object.

**3. Multi-level pointers.** The same rules apply recursively for `const int**` etc. The "member" aspect of a pointer-to-member is ignored when deciding where cv-qualifiers are being added or removed.

**4. Null pointers.** A null pointer value is converted to the null pointer value of the destination type.

### ⚠️ The Critical Danger

The standard (§5.2.11 §7) includes a stark warning:

> *"A write operation through the pointer, lvalue, or pointer to data member resulting from a `const_cast` that casts away a const-qualifier may produce undefined behavior."*

Specifically: if the original object was declared `const`, **writing** through a `const_cast`'d pointer to it is **undefined behavior**. The implementation may have placed it in read-only memory. You can read through the cast pointer safely, but you must not write.

```cpp
const int x = 42;
int* p = const_cast<int*>(&x);
*p = 99; // ⚠️ UNDEFINED BEHAVIOR — x was declared const
```

The legitimate use case for `const_cast` is when you receive a `const` pointer to something you **know** was not originally declared `const`:

```cpp
void legacyAPI(int* p); // old API, doesn't take const but doesn't write

void safe(const int* cp) {
    legacyAPI(const_cast<int*>(cp)); // OK if legacyAPI really doesn't write
}
```

### What `const_cast` Cannot Do

The standard explicitly notes (§5.2.11 §12):

> Conversions between pointers to functions are not covered — such conversions lead to values whose use causes undefined behavior. Similarly, converting a pointer to a `const` member function to a pointer to a non-`const` member function is not allowed.

---

## 4. `reinterpret_cast` — §5.2.10

### What It Is

The most dangerous cast. It tells the compiler: *"Just treat these bytes as this type."* No conversion happens. The underlying bit pattern is reinterpreted. Almost everything about it is **implementation-defined** (the compiler chooses how it works) or **undefined behavior** if misused.

```cpp
reinterpret_cast<T>(v)
```

- If `T` is a reference type, result is an **lvalue**; otherwise an **rvalue**.
- **Cannot** cast away constness.
- The mapping is **implementation-defined** — the result might or might not produce a different representation from the original.

### What It Can Do

**1. Pointer → integer.**

A pointer can be converted to any integral type large enough to hold it. The standard says the mapping is implementation-defined, but notes it *"is intended to be unsurprising to those who know the addressing structure of the underlying machine."* In other words: you'll get the raw memory address as a number.

```cpp
int x;
unsigned long addr = reinterpret_cast<unsigned long>(&x); // raw address (C++98: pick an integral type large enough)
```

> **Round-trip guarantee:** If you convert a pointer to an integer of sufficient size and back to the same pointer type, you get the original pointer back. This is the only guarantee.

**2. Integer/enum → pointer.**

You can go the other way — turn an integer into a pointer. The standard notes one edge case: converting an integral constant expression of value zero **always** gives a null pointer. Converting any other expression that happens to have value zero **may not** give a null pointer.

**3. Function pointer → different function pointer type.**

You can cast between function pointer types. Calling through the wrong type is undefined behavior. The only guarantee is round-tripping: cast `T1* → T2* → T1*` and you get the original value back.

**4. Object pointer → different object pointer type.**

You can cast between any two object pointer types. Round-tripping is safe if the alignment requirements of `T2` are no stricter than `T1`. Otherwise the result is unspecified. (And of course, using a pointer of the wrong type to read/write memory is undefined behavior in most cases — with certain exceptions related to `char*` and union access.)

**5. Null pointer → null pointer.**

A null pointer value always converts to the null pointer value of the destination type.

**6. Pointer-to-member → pointer-to-member.**

Between function pointer-to-members: round-tripping is safe. Between data pointer-to-members: round-tripping is safe if the alignment of `T2` is no stricter than `T1`. Otherwise unspecified.

**7. lvalue → reference to different type (type punning).**

This is what the standard calls a type pun (footnote 67):

```cpp
reinterpret_cast<T&>(x)
// is exactly identical to:
*reinterpret_cast<T*>(&x)
```

You get a reference to the same memory interpreted as a different type. No copy, no constructor, no temporary. The footnote explicitly names this technique **"type punning."**

---

## 5. `uintptr_t` — Not in C++98

`uintptr_t` **does not appear in the C++98 standard.** The text of the standard never mentions it.

Here is why, and what the standard says instead:

The C++98 standard (§5.2.10 §4) describes the pointer-to-integer conversion as:

> *"A pointer can be explicitly converted to any integral type large enough to hold it."*

It does not name a specific type for this. The burden is on you to pick one. In practice in C++98, programmers used `unsigned long` or `unsigned int` and hoped it was big enough.

`uintptr_t` was introduced in **C99** (as part of `<stdint.h>`) and carried into **C++11** (as `<cstdint>`). It is defined as: an unsigned integer type that is large enough to hold a pointer value on the current platform. On a 32-bit system it is 32 bits; on a 64-bit system it is 64 bits.

Its relationship to `reinterpret_cast` in modern C++ (C++11 and later):

```cpp
#include <cstdint>  // C++11 and later only — not available in C++98

int x = 42;
uintptr_t addr = reinterpret_cast<uintptr_t>(&x); // guaranteed large enough
int* back = reinterpret_cast<int*>(addr);          // round-trip: back == &x
```

In **C++98**, you had to do this manually with a type you hoped was wide enough:

```cpp
int x = 42;
unsigned long addr = reinterpret_cast<unsigned long>(&x); // C++98 — no uintptr_t
int* back = reinterpret_cast<int*>(addr);                 // round-trip: back == &x
```

The C++98 standard does not provide `uintptr_t` but the concept it embodies — an integer type guaranteed large enough to hold a pointer — is exactly what §5.2.10 §4 and §5 are describing when they say *"integral type large enough to hold it."*

---

## 🗃️ Summary Table

| | `static_cast` | `dynamic_cast` | `const_cast` | `reinterpret_cast` |
|---|---|---|---|---|
| **Purpose** | Safe compile-time conversion | Safe runtime-checked cast | Add/remove cv-qualifiers only | Raw reinterpretation of bits |
| **Checked at** | Compile time | Runtime | Compile time | Compile time (but mostly UB territory) |
| **Requires polymorphism?** | No | Yes (for downcasting) | No | No |
| **Can cast away `const`?** | No | No | Yes, that's its job | No |
| **On failure** | Undefined behavior (wrong downcast) | `nullptr` or throws `bad_cast` | N/A | Undefined behavior if misused |
| **Result is predictable?** | Yes | Yes | Yes | Implementation-defined |
| **Type pun?** | No | No | No | Yes |

---

## ⚡ The Old-Style (C-Style) Cast — §5.4

### What It Is

The C-style cast is the original cast syntax inherited from C. It looks like this:

```cpp
(T) expression
```

You wrap a type name in parentheses and put it in front of an expression. The standard (§5.4) defines the grammar precisely:

```
cast-expression:
    unary-expression
    ( type-id ) cast-expression
```

Notice that the grammar is **recursive** — you can write `(T)(U)someValue`, casting twice in sequence. The right side is another cast-expression, not just a value.

---

### Three Ways to Write an Explicit Conversion

The C++98 standard (§5.4 §2) says there are actually **three syntaxes** that all count as explicit type conversion. They're all part of the same language feature:

**1. Cast notation (C-style):**
```cpp
(int)someDouble
```

**2. Functional notation (§5.2.3):**
```cpp
int(someDouble)
```

**3. Named cast operators:**
```cpp
static_cast<int>(someDouble)
dynamic_cast<Base*>(ptr)
const_cast<int*>(constPtr)
reinterpret_cast<uintptr_t>(ptr)
```

For the functional notation specifically, the standard says (§5.2.3 §1): *"If the expression list is a single expression, the type conversion expression is equivalent (in definedness, and if defined in meaning) to the corresponding cast expression."* In other words, `int(x)` and `(int)x` mean exactly the same thing. If multiple values are passed (`T(x1, x2, ...)`), it constructs a class object — equivalent to declaring `T t(x1, x2, ...)` and using `t` as an rvalue.

---

### The Result Type: lvalue or rvalue?

§5.4 §1 states:

> *"The result of the expression `(T) cast-expression` is of type `T`. The result is an lvalue if `T` is a reference type, otherwise the result is an rvalue."*

And then an important note:

> *"If `T` is a non-class type that is cv-qualified, the cv-qualifiers are ignored when determining the type of the resulting rvalue."*

What this means in practice:

```cpp
int x = 5;
(int&)x         // lvalue — T is a reference type
(int)x          // rvalue — T is not a reference type
(const int)x    // rvalue — the 'const' is IGNORED on a non-class rvalue
```

That third one is subtle. If you cast to `const int` and the result is not a reference, the `const` just disappears from the result type. It has no effect. This only matters for class types — `const MyClass` on a non-reference result does preserve the `const`.

The standard also clarifies in §3.10 §6 that:

> *"An expression which holds a temporary object resulting from a cast to a nonreference type is an rvalue."*

So a C-style cast to a non-reference type **always** produces a temporary rvalue — never the original object.

---

### The Core Rule: What Can It Actually Do?

§5.4 §5 is the heart of the section. The standard lists exactly what conversions the C-style cast can perform, **in priority order**:

1. `const_cast`
2. `static_cast`
3. `static_cast` followed by `const_cast`
4. `reinterpret_cast`
5. `reinterpret_cast` followed by `const_cast`

The rule is: *"If a conversion can be interpreted in more than one of the ways listed above, the interpretation that appears first in the list is used, even if a cast resulting from that interpretation is ill-formed."*

> ⚠️ **This is the critical danger.** The compiler doesn't pick the interpretation that works — it picks the **first one on the list** and uses it, even if it's broken.

**§5.4 §4 — The Hard Boundary**

> *"Any type conversion not mentioned below and not explicitly defined by the user (12.3) is ill-formed."*

If a conversion can't be expressed as one of the five interpretations above, and the user hasn't defined a conversion function (`operator T()`) or a converting constructor, the cast simply **does not compile**. The C-style cast is not a magic "make it work" incantation — it still has limits.

---

### The Ambiguity Rule and When It's Ill-Formed

§5.4 §5 has a separate rule specifically for the `static_cast` + `const_cast` interpretation:

> *"If a conversion can be interpreted in more than one way as a static_cast followed by a const_cast, the conversion is ill-formed."*

The standard provides an example of this (§5.4 §5):

```cpp
struct A {};
struct I1 : A {};
struct I2 : A {};
struct D : I1, I2 {};

A* foo(D* p) {
    return (A*)(p); // ill-formed — static_cast interpretation is ambiguous
}
```

Here, `D` inherits from `A` through two paths (`I1` and `I2`). A `static_cast` from `D*` to `A*` would be ambiguous because there are two `A` sub-objects. The compiler cannot choose one. But since `static_cast` comes **before** `reinterpret_cast` in the priority list, the compiler tries `static_cast` first — finds it ill-formed — and the whole thing fails. It does **not** fall back to `reinterpret_cast`.

This is a key distinction: the named casts would at least be clear about what they're trying to do. The C-style cast silently escalates through the list and fails in a confusing way.

---

### The Special Rule for Incomplete Class Types

§5.4 §6 introduces a unique behavior that **doesn't exist in any named cast**:

> *"The operand of a cast using the cast notation can be an rvalue of type 'pointer to incomplete class type'. The destination type of a cast using the cast notation can be 'pointer to incomplete class type'. In such cases, even if there is an inheritance relationship between the source and destination classes, whether the static_cast or reinterpret_cast interpretation is used is **unspecified**."*

This means: if you cast between pointers to types that are forward-declared but not fully defined yet, the compiler doesn't know if there's an inheritance relationship. It picks either `static_cast` or `reinterpret_cast` — but the standard says which one it picks is **unspecified**. You literally cannot know what you're getting. This is a unique trap of the C-style cast with no parallel in the named operators.

---

### The Access Bypass — C-Style Cast's Unique Superpower

§5.4 §7 is one of the most important and least-known rules in this section. The named casts all **respect** access control (`public`/`private`/`protected`). The C-style cast **does not**:

> *"In addition to those conversions, the following static_cast and reinterpret_cast operations (optionally followed by a const_cast operation) may be performed using the cast notation of explicit type conversion, even if the base class type is not accessible:"*

The three specific cases granted this access bypass are:

- **Case 1:** A pointer or lvalue of derived class type → pointer or reference to an unambiguous base class type. This works even if the base is `private`.
- **Case 2:** A pointer-to-member of derived class → pointer-to-member of an unambiguous non-virtual base class type. Again, even if `private`.
- **Case 3:** A pointer, lvalue, or pointer-to-member of non-virtual base class type → pointer, reference, or pointer-to-member of a derived class type. Even if `private`.

In other words:

```cpp
class Base {};
class Derived : private Base {};  // private inheritance!

Derived d;
Base* bp = (Base*)(&d);                    // WORKS — C-style bypasses private
// Base* bp = static_cast<Base*>(&d);      // ERROR — static_cast respects access
```

This is intentional — it matches the behavior of the original C language, which had no concept of access control. The C++ standard preserves this for backwards compatibility but it is a significant footgun.

---

### The Strict Aliasing Trap (§3.10 §15)

When the C-style cast resolves to a `reinterpret_cast`, you are **type-punning** — telling the compiler to access the same memory as a different type. The standard imposes a **strict aliasing rule** in §3.10 §15 that determines when this is legal:

> *"If a program attempts to access the stored value of an object through an lvalue of other than one of the following types the behavior is undefined:"*

The **allowed** types are:

- The dynamic type of the object
- A cv-qualified version of that type (e.g. `const T` when `T` is the real type)
- The signed or unsigned counterpart of the dynamic type
- The signed or unsigned counterpart of a cv-qualified version of the dynamic type
- An aggregate or union that contains the dynamic type among its members
- A (possibly cv-qualified) base class type of the dynamic type
- `char` or `unsigned char` (these two can alias **anything**)

Everything else is **undefined behavior**. This is directly relevant to the C-style cast because it can silently become a `reinterpret_cast`, letting you write code that looks like it works but violates this rule:

```cpp
float f = 3.14f;
int i = *(int*)(&f);  // C-style cast → reinterpret → UNDEFINED BEHAVIOR
                      // int is not in the allowed alias list for float
```

The footnote in the standard (footnote 48) states bluntly: *"The intent of this list is to specify those circumstances in which an object may or may not be aliased."*

---

### User-Defined Conversions and the Cast

§5.4 §4 specifies that any type conversion "explicitly defined by the user" (§12.3) is permitted by the cast notation. This means the C-style cast also invokes:

- **Conversion constructors** — a constructor of the destination type that takes one argument of the source type
- **Conversion functions** — `operator T()` defined in the source class

```cpp
class MyInt {
public:
    MyInt(int v) : val(v) {}        // converting constructor
    operator double() { return val; } // conversion function
    int val;
};

MyInt m = (MyInt)42;    // invokes MyInt(int) — converting constructor
double d = (double)m;   // invokes operator double()
```

These are the only cases where a C-style cast can do something that none of the five named-cast interpretations could do on their own — when user-defined conversions are involved, the compiler treats `(T)x` as initialization `T t(x)`, firing constructors or conversion functions as needed.

---

### Full Priority Walk-Through: What the Compiler Actually Does

Here is the exact sequence the compiler follows every time it sees `(T)expr`, laid out step by step from the standard:

```
Step 1: Can this be done as a const_cast alone?
         (only changes cv-qualifiers, nothing else)
        → YES: use const_cast. STOP.

Step 2: Can this be done as a static_cast alone?
         (hierarchy navigation, arithmetic conversions,
          void*, enum/int, anything implicitly reversible)
        → YES: use static_cast. STOP.
          (even if it's ill-formed — the compiler tries it first)

Step 3: Can this be done as static_cast + const_cast?
         (downcast while also stripping const)
        → YES (unambiguously): use static_cast + const_cast. STOP.
        → YES (but ambiguous): ILL-FORMED. Compilation error.

Step 4: Can this be done as a reinterpret_cast alone?
         (pointer↔integer, pointer↔pointer, type pun)
        → YES: use reinterpret_cast. STOP.

Step 5: Can this be done as reinterpret_cast + const_cast?
         (raw reinterpretation while stripping const)
        → YES: use reinterpret_cast + const_cast. STOP.

Step 6: Is there a user-defined conversion (constructor/operator)?
        → YES: invoke it. STOP.

Step 7: None of the above apply.
        → ILL-FORMED. Compilation error.
```

---

### The "Same Semantics" Guarantee

§5.4 §5 is explicit: *"The same semantic restrictions and behaviors apply."* This means the C-style cast does **not** get special permissions when it resolves to a named cast. If the equivalent `static_cast` would have undefined behavior, the C-style cast that resolves to `static_cast` has the same undefined behavior. The C-style cast doesn't secretly make anything safer — it just hides which cast it chose.

---

### Summary: C-Style vs Named Casts

| Property | C-style `(T)x` | Named casts |
|---|---|---|
| Makes intent visible | ❌ — opaque | ✅ — explicit |
| Respects private inheritance | ❌ — bypasses it (§5.4 §7) | ✅ — access controlled |
| Can strip `const` | ✅ (silently) | Only `const_cast`, explicitly |
| Works on incomplete types | ✅ (unspecified behavior, §5.4 §6) | Varies — mostly requires complete types |
| Can type-pun | ✅ (silently resolves to `reinterpret_cast`) | Only `reinterpret_cast`, explicitly |
| Ambiguous paths | Picks first valid interpretation | Each cast has one well-defined job |
| Safe downcasting | ❌ (no runtime check) | `dynamic_cast` checks at runtime |
| Searchable in code | ❌ — hard to grep | ✅ — easy to find and audit |

The C-style cast is not wrong or forbidden in C++98, but the standard's design of the named casts is a deliberate statement: every named cast does one thing, is readable, and fails loudly when you ask it to do something outside its lane. The C-style cast does all five things invisibly, and when it resolves to the most dangerous option — `reinterpret_cast` — it gives you no warning that it did.

---

*Based on ISO/IEC 14882:1998 (C++98 Standard)*
