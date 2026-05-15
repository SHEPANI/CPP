# CPP06 — C++ Type Casting

A summary of everything covered in the cpp06 module on type casting in C++.

---

## Table of Contents

1. [What is Type Casting?](#what-is-type-casting)
2. [Implicit Conversion](#implicit-conversion)
3. [Explicit Conversion](#explicit-conversion)
4. [dynamic_cast](#dynamic_cast)
5. [static_cast](#static_cast)
6. [reinterpret_cast](#reinterpret_cast)
7. [const_cast](#const_cast)
8. [Final Summary — How Everything Connects](#final-summary--how-everything-connects)

---

## What is Type Casting?

Type casting is the process of converting an expression of one type into another type. C++ provides multiple ways to perform this conversion, ranging from automatic (implicit) to explicit and controlled casts.

---

## Implicit Conversion

Implicit conversions happen **automatically** when a value is assigned to a compatible type — no cast operator is needed.

### Primitive types

```cpp
short a = 2000;
int   b;
b = a;  // short is automatically promoted to int
```

This is called a **standard conversion**. It covers:

#### Numerical type conversions

Every arrow below is a valid implicit conversion:

```
Integer promotions (safe, no data loss):
  bool       → int
  char       → int
  short      → int
  int        → long
  int        → long long
  int        → float
  int        → double
  int        → long double
  long       → long long
  long       → double
  long       → long double
  float      → double
  float      → long double
  double     → long double

Narrowing conversions (may lose data — compiler may warn):
  long long  → long
  long long  → int
  long long  → short
  long long  → char
  long       → int
  long       → short
  long       → char
  int        → short
  int        → char
  double     → float
  double     → int
  float      → int
```

> ⚠️ Narrowing conversions may cause a **loss of precision or overflow**. The compiler usually warns. An explicit cast silences the warning.

#### Conversions to/from `bool`

Any non-zero numeric value or non-null pointer converts to `true`; zero/null converts to `false`. Going the other way, `true` becomes `1` and `false` becomes `0`.

```cpp
{
    int  i = 42;
    bool b = i;      // true  (non-zero → true)

    int  j = 0;
    bool c = j;      // false (zero    → false)

    bool flag = true;
    int  n    = flag; // 1    (true  → 1)

    bool off  = false;
    int  m    = off;  // 0    (false → 0)
}
```

#### Pointer conversions

```cpp
// 1. Any pointer → void*  (generic pointer, loses type info)
int  x = 10;
int* p = &x;
void* vp = p;           // int* → void*  (implicit, always safe)

// 2. void* → typed pointer  (requires explicit cast in C++, shown for contrast)
int* p2 = (int*)vp;     // needs explicit cast — NOT implicit in C++

// 3. Derived* → Base*  (upcasting — always implicit and safe)
class Base  {};
class Child : public Base {};

Child child;
Base* bp = &child;      // Child* → Base*  (implicit upcast)

// 4. nullptr  → any pointer type
int*    np1 = nullptr;  // implicit
double* np2 = nullptr;  // implicit

// 5. T* → const T*  (adding const is always implicit)
int        val = 5;
int*       ptr = &val;
const int* cptr = ptr;  // int* → const int*  (implicit)
```

---

### Constructor conversion vs. Conversion operator

These are **two different mechanisms** — both trigger implicit conversions between class objects, but they live in different classes and work in opposite directions.

#### 1. Constructor conversion (converting constructor)

Defined **in the destination class**. The constructor takes the source type as parameter, so the compiler can build the target object from the source automatically.

```cpp
class Celsius {
public:
    double degrees;
    Celsius(double d) : degrees(d) {}  // converting constructor
};

double temp = 36.6;
Celsius body = temp;   // implicit: compiler calls Celsius(36.6)
```

The conversion goes **from the parameter type → to the class that owns the constructor**.

#### 2. Conversion operator

Defined **in the source class**. It teaches that class how to produce a value of another type when needed.

```cpp
class Celsius {
public:
    double degrees;
    Celsius(double d) : degrees(d) {}

    operator double() const {   // conversion operator: Celsius → double
        return degrees;
    }
};

Celsius body(36.6);
double temp = body;   // implicit: compiler calls body.operator double()
```

The conversion goes **from the class that owns the operator → to the return type**.

#### What if both exist?

If both a converting constructor and a conversion operator can satisfy the same conversion, the compiler reports an **ambiguity error**.

```cpp
class Fahrenheit {
public:
    double degrees;
    Fahrenheit(double d) : degrees(d) {}
    operator double() const { return degrees; }  // Fahrenheit → double
};

class Celsius {
public:
    double degrees;
    Celsius(double d) : degrees(d) {}
    Celsius(Fahrenheit f) : degrees((f.degrees - 32) * 5.0 / 9.0) {} // Fahrenheit → Celsius
};

Fahrenheit f(98.6);
Celsius c = f;   // ❌ ambiguous: use Celsius(Fahrenheit) or Fahrenheit::operator double() + Celsius(double)?
```

To resolve this, use an explicit cast to tell the compiler which path to take:

```cpp
Celsius c = Celsius(f);                  // force constructor conversion
Celsius c2 = Celsius((double)f);         // force operator double() first, then Celsius(double)
```

#### What if the classes have different attributes?

A converting constructor **only needs to receive what it uses**. If class `B` only cares about one field of class `A`, the constructor simply reads that field:

```cpp
class A {
public:
    int    id;
    double value;
    char   name[32];
};

class B {
public:
    double result;
    B(const A& a) : result(a.value) {}   // only uses a.value, ignores id and name
};

A source = {1, 3.14, "hello"};
B dest = source;   // implicit: B(source) — only a.value (3.14) is copied into result
```

The extra attributes (`id`, `name`) are simply ignored — the compiler does not care about the mismatch as long as the constructor compiles.

---

## Explicit Conversion

When the compiler won't convert automatically — or when you want to make your intent crystal-clear — you write the cast yourself. C++ inherited two classic notations for this from C:

```cpp
short a = 2000;
int   b;
b = (int) a;   // C-like cast notation
b = int(a);    // Functional notation
```

### C-like cast vs Functional notation — what is the difference?

They produce **identical machine code** for fundamental types. The difference is purely syntactic and about readability:

| | C-like `(type) expr` | Functional `type(expr)` |
|---|---|---|
| Origin | Inherited from C | C++ addition |
| Reads like | A prefix operator | A constructor / function call |
| Works on multi-word types | `(unsigned int) x` ✅ | `unsigned int(x)` ❌ won't parse |
| Works on class types | `(MyClass) x` ✅ | `MyClass(x)` ✅ (cleaner) |
| Searchable in code | Hard — `(int)` is easy to miss | Easy — looks like a function call |

The functional notation `int(a)` reads as *"construct an int from a"*, which fits naturally with how C++ thinks about types as constructors. For simple types they are the same, but many C++ programmers prefer functional notation because it is easier to grep and looks intentional.

> ⚠️ Both notations are called **traditional casts**. For class pointers they are dangerous — see below.

---

### The danger of traditional casts on class pointers

Traditional casts let you convert **any pointer to any other pointer type** with zero checks:

```cpp
class CDummy {
    float i, j;
};

class CAddition {
    int x, y;
public:
    CAddition(int a, int b) { x = a; y = b; }
    int result() { return x + y; }
};

int main() {
    CDummy    d;
    CAddition* padd;
    padd = (CAddition*) &d;   // compiles fine — no error
    cout << padd->result();   // 💥 undefined behaviour
    return 0;
}
```

`&d` is the address of a `CDummy` object. Its memory layout is two `float`s (`i`, `j`). The compiler happily reinterprets that address as if it pointed to a `CAddition` (which expects two `int`s, `x` and `y`). This compiles without a warning.

#### "Run-time error or unexpected result" — which one, and why?

This is **undefined behaviour** in C++. The standard does not mandate one specific outcome; what actually happens depends on several factors:

| Factor | Outcome |
|---|---|
| Memory happens to contain plausible bit patterns | Wrong numeric answer (unexpected result) |
| Memory is uninitialized / OS-protected | Segmentation fault / access violation (run-time error) |
| Compiler optimisation level | Code may be reordered or eliminated entirely |
| Platform / calling convention | Stack corruption, wrong registers used |

So it is **not** the compiler that decides at compile-time which will happen — the outcome is determined at **runtime** by the state of memory and the platform. The compiler simply trusts you and generates code that reads from whatever address you gave it.

---

### The four C++ casting operators — overview

To prevent exactly the problem above, C++ introduced four controlled casting operators:

```
dynamic_cast     <new_type> (expression)
static_cast      <new_type> (expression)
reinterpret_cast <new_type> (expression)
const_cast       <new_type> (expression)
```

#### The order traditional casts follow internally

When you write `(new_type) expr`, the compiler tries the following sequence and **stops at the first attempt that succeeds**:

| Step | What it tries | Fails if… |
|---|---|---|
| 1 | `const_cast` | types differ beyond just const/volatile |
| 2 | `static_cast` | types are unrelated (no inheritance / no standard conversion) |
| 3 | `static_cast` + `const_cast` | still unrelated after stripping const |
| 4 | `reinterpret_cast` | almost never fails — raw address reinterpretation |
| 5 | `reinterpret_cast` + `const_cast` | virtually never fails |

In the `(CAddition*) &d` example, steps 1–3 all fail because `CDummy` and `CAddition` are completely unrelated classes. The compiler falls through to step 4 and does a raw `reinterpret_cast` — no checks, just reinterprets the raw memory address. That is why it compiles cleanly and then breaks at runtime.

This is exactly what makes traditional casts dangerous: they silently escalate all the way to `reinterpret_cast` without telling you. The named casting operators are locks — each one permits only specific steps from the list above, and refuses to go further:

| Named cast | Permits only |
|---|---|
| `const_cast` | Step 1 only |
| `static_cast` | Steps 2–3 only |
| `reinterpret_cast` | Steps 4–5 only |
| `dynamic_cast` | A runtime type check — **not possible with traditional casts at all** |

##### `const_cast` — step 1 only (add or remove const/volatile)

```cpp
void print(char* str) { std::cout << str; }

const char* msg = "hello";
print(const_cast<char*>(msg));  // strips const so it fits the function parameter
                                // safe here because print() does not modify the string
```

```cpp
const int x = 42;
int* p = const_cast<int*>(&x);
*p = 99;  // compiles — but UNDEFINED BEHAVIOUR, x was declared const
           // const_cast does NOT make it safe to write, only to pass around
```

> `const_cast` **only** changes const/volatile qualification. It cannot change the actual type at all — `const_cast<int*>(floatPtr)` won't compile.

---

##### `static_cast` — steps 2–3 only (compile-time checked conversions)

```cpp
// Numerical conversion
double d = 3.99;
int    i = static_cast<int>(d);  // i = 3 — truncates, compiler knows this is intentional

// Up-cast (Derived* → Base*) — always safe
class Base {};
class Derived : public Base {};

Derived  obj;
Base*    bp = static_cast<Base*>(&obj);  // fine — Derived IS-A Base

// Down-cast (Base* → Derived*) — compile-time only, no runtime check
Base*    base = new Derived();
Derived* dp   = static_cast<Derived*>(base);  // compiles — but YOU must guarantee
                                               // base really points to a Derived
```

> `static_cast` refuses completely unrelated types — `static_cast<CDummy*>(cadditionPtr)` won't compile, unlike the traditional cast that silently falls through to `reinterpret_cast`.

**Step 3 — `static_cast` + `const_cast` combination:**
This happens when the conversion is valid (related types) but const also needs to be stripped at the same time. `static_cast` alone can't strip const, so the traditional cast silently applies both together:

```cpp
class Base {};
class Derived : public Base {};

const Derived  obj;
Base*          bp = (Base*) &obj;  // traditional cast: applies static_cast (Derived→Base)
                                   //                   then const_cast (strips const)
                                   // one step, no warning — dangerous and invisible
```

With named casts you must do this **explicitly in two steps**, which makes the intent visible:

```cpp
const Derived  obj;
const Base*    cbp = static_cast<const Base*>(&obj);  // step 1: upcast, keep const
Base*          bp  = const_cast<Base*>(cbp);           // step 2: strip const explicitly
```

> The traditional cast hides that two operations happened. The named cast version forces you to write both, so a code reviewer can immediately see "this person is stripping const off a base pointer" and question why.

---

##### `reinterpret_cast` — steps 4–5 only (raw bit/address reinterpretation)

```cpp
// Reinterpret a pointer as a completely unrelated pointer type
CDummy*    d    = new CDummy();
CAddition* padd = reinterpret_cast<CAddition*>(d);  // same as the dangerous traditional cast
                                                     // but now it is EXPLICIT and searchable

// Reinterpret a pointer as an integer (e.g. to inspect the raw address)
int* p    = new int(42);
long addr = reinterpret_cast<long>(p);  // stores the raw memory address as a number
std::cout << addr;
```

> `reinterpret_cast` does zero checks — it is the "I know what I'm doing, trust me" cast. The only advantage over a traditional cast is that it is visible and grep-able in the code, making dangerous casts easy to audit.

**Step 5 — `reinterpret_cast` + `const_cast` combination:**
This is the most dangerous step. It happens when the types are completely unrelated AND const needs to be stripped at the same time. The traditional cast handles both silently in one go:

```cpp
class CDummy    { float i, j; };
class CAddition { int x, y; public: int result() { return x + y; } };

const CDummy    d;
CAddition*      padd = (CAddition*) &d;  // traditional cast: reinterpret_cast (unrelated types)
                                         //                 + const_cast (strips const)
                                         // both happen silently — undefined behaviour
```

With named casts, again you must be explicit:

```cpp
const CDummy    d;
CDummy*         non_const = const_cast<CDummy*>(&d);         // step 1: strip const explicitly
CAddition*      padd      = reinterpret_cast<CAddition*>(non_const);  // step 2: raw reinterpret
```

> This is the most auditable advantage of named casts: any `reinterpret_cast` in the codebase is immediately a red flag worth reviewing. With traditional casts, this same dangerous operation is completely invisible.

---

##### `dynamic_cast` — runtime type check (requires polymorphism)

```cpp
class Base    { public: virtual ~Base() {} };  // must have at least one virtual function
class Derived : public Base {};
class Other   : public Base {};

Base* bp = new Derived();

// Safe down-cast — checked at runtime
Derived* dp = dynamic_cast<Derived*>(bp);  // succeeds: bp really points to a Derived
if (dp != NULL)
    std::cout << "cast succeeded" << std::endl;

// Failed cast — returns NULL (for pointers), does NOT crash
Other* op = dynamic_cast<Other*>(bp);      // fails: bp is not an Other
if (op == NULL)
    std::cout << "cast failed safely" << std::endl;
```

> This is the only cast that inspects the **actual runtime type** of the object. A traditional cast cannot do this — it would just reinterpret the pointer and cause undefined behaviour. `dynamic_cast` requires the base class to be polymorphic (at least one `virtual` function).

---

#### What does "traditional equivalents" mean?

The sentence *"the traditional type-casting equivalents to these expressions would be `(new_type) expression` / `new_type(expression)`"* means:

> Every C++ cast can be written with the old C-like or functional syntax and will compile — **but** the old syntax performs no safety checks and gives no hint of intent. The four named casts are replacements that each restrict what conversions are allowed and make the programmer's intent explicit in the code.

In other words:

```cpp
// These two lines do the same thing mechanically:
int* p = (int*) somePtr;              // traditional — no checks, no intent
int* p = static_cast<int*>(somePtr);  // named cast  — checked, intent is clear
```

The named casts are **not new operations** — they are the same pointer/value reinterpretation you already know, wrapped in rules that catch mistakes. Each of the four has its own specific rules and use cases, which we will cover next.

---

## `dynamic_cast`

`dynamic_cast` can only be used with **pointers and references to objects** (not plain values). Its purpose is to guarantee that the result of the conversion is a valid, complete object of the requested class — something no other cast can promise.

---

### Derived-to-base is always safe

Converting from a derived class to one of its base classes always succeeds because a `CDerived` object IS-A `CBase` object by definition:

```cpp
class CBase   {};
class CDerived: public CBase {};

CBase    b;  CBase*    pb;
CDerived d;  CDerived* pd;

pb = dynamic_cast<CBase*>(&d);    // ok: derived-to-base, always succeeds
pd = dynamic_cast<CDerived*>(&b); // COMPILATION ERROR: base-to-derived not allowed
                                  // unless CBase is polymorphic (has a virtual function)
```

The second line is rejected at **compile time** — not runtime. `dynamic_cast` refuses the base-to-derived direction entirely unless the base class is polymorphic, because without runtime type info there is no safe way to verify the cast.

---

### Polymorphic classes — runtime checking

Once the base class has at least one `virtual` function, it becomes polymorphic and `dynamic_cast` can perform a **runtime check**:

```cpp
class CBase    { virtual void dummy() {} };  // virtual → polymorphic
class CDerived : public CBase { int a; };

int main() {
    CBase* pba = new CDerived;  // CBase pointer → but points to a CDerived object
    CBase* pbb = new CBase;     // CBase pointer → points to a plain CBase object

    CDerived* pd;

    pd = dynamic_cast<CDerived*>(pba);  // SUCCESS  — pba really IS a CDerived at runtime
    if (pd == 0) std::cout << "Null pointer on first type-cast" << std::endl;

    pd = dynamic_cast<CDerived*>(pbb);  // FAILS    — pbb is only a CBase, not a CDerived
    if (pd == 0) std::cout << "Null pointer on second type-cast" << std::endl;
}
```

Output:
```
Null pointer on second type-cast
```

`pba` and `pbb` are both `CBase*` — the same static type. But at runtime their actual objects differ: `pba` points to a full `CDerived`, `pbb` to a plain `CBase`. `dynamic_cast` inspects the real object in memory and returns `NULL` instead of crashing when the cast is impossible.

---

### What is RTTI and how does it affect the compiler?

**RTTI (Run-Time Type Information)** is extra data that the compiler secretly embeds into every polymorphic object (any class with at least one `virtual` function). It is what makes `dynamic_cast` possible.

#### What the compiler actually stores

For every polymorphic class, the compiler generates a hidden structure called a **vtable** (virtual function table). Alongside the pointers to virtual functions, it attaches a `type_info` record that describes the class:

```
Memory layout of a CDerived object:
┌──────────────────────────────────────┐
│ vptr ──────────────────────────────► vtable of CDerived        │
│                                      ├─────────────────────────┤
│  int a                               │ ptr to dummy()          │
│                                      │ ptr to type_info        │
└──────────────────────────────────────┘    └─► name: "CDerived"
                                                 base: CBase
                                                 base's base: ...
```

When `dynamic_cast<CDerived*>(pbb)` runs, the compiler emits code that:
1. Follows `pbb`'s `vptr` to its vtable
2. Reads the `type_info` record attached to it
3. Walks up the inheritance chain stored there to check whether `CDerived` appears
4. If yes → returns the adjusted pointer. If no → returns `NULL`

#### The compiler option warning

Some compilers (notably older GCC and some embedded toolchains) disable RTTI by default to save binary size and speed up builds (`-fno-rtti` in GCC/Clang). If RTTI is off:
- `dynamic_cast` will either **fail to compile** or produce wrong results silently
- `typeid` (the other RTTI feature) also stops working
- You must enable it explicitly (GCC/Clang: `-frtti`, MSVC: `/GR`)

In normal desktop C++ compilation RTTI is on by default — you only hit this problem on embedded systems or when someone explicitly stripped it.

---

### Pointer → returns `NULL` on failure. Reference → throws `bad_cast`

```cpp
// POINTER version — failed cast returns NULL, you check with if
CDerived* pd = dynamic_cast<CDerived*>(pbb);
if (pd == NULL)
    std::cout << "cast failed" << std::endl;  // safe, no crash

// REFERENCE version — failed cast throws std::bad_cast (no NULL for references)
try {
    CDerived& rd = dynamic_cast<CDerived&>(*pbb);  // pbb is not a CDerived → throws
} catch (std::bad_cast& e) {
    std::cout << "Exception: " << e.what() << std::endl;
}
```

---

### Casting null pointers and casting to `void*`

`dynamic_cast` has two special behaviours that no other cast shares:

#### Null pointer between unrelated classes — always returns `NULL`

```cpp
class A { virtual void dummy() {} };
class B { virtual void dummy() {} };  // completely unrelated to A

A* pa = NULL;
B* pb = dynamic_cast<B*>(pa);  // pa is NULL → result is NULL, no crash, no UB
                                // static_cast or reinterpret_cast here = undefined behaviour
```

This is safe because `dynamic_cast` checks the pointer before touching any memory. A null input always produces a null output.

#### Any polymorphic pointer → `void*` always succeeds

```cpp
class CBase    { virtual void dummy() {} };
class CDerived : public CBase { int a; };

CDerived  obj;
CBase*    pb   = &obj;
void*     pv   = dynamic_cast<void*>(pb);  // always succeeds for any polymorphic pointer
                                            // pv now holds the address of the MOST DERIVED
                                            // object (CDerived), not just the CBase sub-object
```

This is unique: casting to `void*` gives you the address of the **complete, most-derived object**, not the base sub-object. This is useful when you need to compare whether two pointers with different types point to the same underlying object:

```cpp
CBase*    pb2 = &obj;
void*     pv2 = dynamic_cast<void*>(pb2);

if (pv == pv2)
    std::cout << "same object" << std::endl;  // true — both point to the same CDerived
```

---

## `static_cast`

`static_cast` performs conversions that are **checked at compile time only** — the compiler verifies that the two types are related (connected by inheritance), but it does zero checking at runtime about whether the actual object in memory is really what you claim it is. That responsibility falls entirely on the programmer.

---

### Pointer conversions between related classes

```cpp
class CBase    {};
class CDerived : public CBase {};

CBase*    a = new CBase;
CDerived* b = static_cast<CDerived*>(a);  // compiles — types are related
                                           // but a only holds a plain CBase object!
```

#### Why does `b` point to an "incomplete object" and cause runtime errors?

Think about what memory looks like for each class:

```
Memory layout of a CBase object:       Memory layout of a CDerived object:
┌────────────────────┐                 ┌────────────────────┐
│  CBase members     │                 │  CBase members     │  ← same region
└────────────────────┘                 ├────────────────────┤
                                       │  CDerived members  │  ← extra region
                                       └────────────────────┘
```

`a` was created with `new CBase` — so only the top region exists in memory. The extra `CDerived` region was **never allocated**. When you do `static_cast<CDerived*>(a)`, the compiler just shifts the pointer type on paper. It does not allocate the missing memory, does not check anything.

Now `b` points to a `CBase`-sized block but pretends it is `CDerived`-sized. The moment you access any member that lives in the `CDerived` region:

```cpp
b->someCDerivedMember;  // reads memory that was never allocated → garbage or segfault
```

You are reading memory that belongs to someone else — undefined behaviour. This is exactly what `dynamic_cast` protects you from by doing the runtime check.

> **Rule:** `static_cast` downcast (base→derived) is only safe when you are 100% certain the object was originally constructed as the derived type. If there is any doubt, use `dynamic_cast`.

---

### Non-pointer conversions — all cases with examples

#### 1. Standard numerical conversions

```cpp
// Floating point → integer (truncates toward zero)
double d = 3.99;
int    i = static_cast<int>(d);   // i = 3, not 4 — truncation, not rounding

// Integer → floating point
int   x = 7;
float f = static_cast<float>(x);  // f = 7.0

// Larger integer → smaller integer (narrowing — may lose data)
long  l  = 100000L;
short s  = static_cast<short>(l); // may overflow if value doesn't fit in short

// Signed ↔ unsigned
int           n  = -1;
unsigned int  u  = static_cast<unsigned int>(n);   // u = 4294967295 (wraps around)
unsigned int  u2 = 42;
int           n2 = static_cast<int>(u2);            // n2 = 42, safe here
```

#### 2. bool conversions

```cpp
// Any non-zero number → true, zero → false
int  a = 5;
bool t = static_cast<bool>(a);   // true

int  b = 0;
bool f2 = static_cast<bool>(b);  // false

// bool → int: true=1, false=0
bool flag = true;
int  val  = static_cast<int>(flag);  // val = 1
```

#### 3. char conversions

```cpp
// char → int (gives the ASCII value)
char c = 'A';
int  ascii = static_cast<int>(c);    // ascii = 65

// int → char (gives the character for that ASCII value)
int  code = 66;
char ch   = static_cast<char>(code); // ch = 'B'
```

---

### Conversions between classes — constructor and operator conversions

#### Constructor conversion (same as implicit, but explicit)

```cpp
class Celsius {
    float degrees;
public:
    Celsius(float d) : degrees(d) {}
    float get() const { return degrees; }
};

class Fahrenheit {
    float degrees;
public:
    Fahrenheit(float d) : degrees(d) {}          // constructor from float
    Fahrenheit(Celsius c) : degrees(c.get() * 9.0f / 5.0f + 32.0f) {}  // constructor from Celsius
    float get() const { return degrees; }
};

Celsius    c(100.0f);
Fahrenheit f = static_cast<Fahrenheit>(c);  // calls Fahrenheit(Celsius) constructor
                                             // same as implicit but intent is explicit
std::cout << f.get();  // 212
```

The `static_cast` here simply calls the constructor — identical to what implicit conversion would do, but written explicitly so anyone reading the code sees the conversion happening.

#### Operator conversion

```cpp
class Percentage {
    float value;
public:
    Percentage(float v) : value(v) {}
    operator float() const { return value / 100.0f; }  // conversion operator → float
};

Percentage p(75.0f);
float ratio = static_cast<float>(p);   // calls operator float()
std::cout << ratio;                    // 0.75

// Compare with implicit — both call the same operator:
float ratio2 = p;                      // implicit — works but hides the conversion
float ratio3 = static_cast<float>(p);  // explicit — makes it obvious a conversion happens
```

#### When both a constructor and an operator exist for the same conversion

```cpp
class B;
class A {
public:
    operator B() const;  // A can convert itself to B
};

class B {
public:
    B() {}
    B(A a) {}            // B can be constructed from A
};

A a;
B b = static_cast<B>(a);  // AMBIGUOUS — compiler doesn't know whether to call
                           // A::operator B() or B::B(A)
                           // this is a compile error
```

This is the same ambiguity covered in the implicit conversion section — `static_cast` does not resolve it, it just makes the intent explicit. You must remove one of the two conversion paths to fix it.

---
## `reinterpret_cast`

`reinterpret_cast` is the most powerful and most dangerous cast in C++. It tells the compiler: **"take these bits and pretend they are a completely different type"** — no checks, no conversions, no adjustments. Just a raw reinterpretation of memory.

---

### How the "binary copy" operation actually works

Every variable in memory is just a sequence of bytes. `reinterpret_cast` does not move those bytes, does not convert them, does not allocate anything. It just hands you back the **same address** with a **different type label** stamped on it by the compiler.

```
Before cast:
  int* p → [ 0x00 | 0x00 | 0x03 | 0xE8 ]   ← 4 bytes representing integer 1000
                ↑
          address: 0x7ffee4bc

After reinterpret_cast<float*>(p):
  float* fp → [ 0x00 | 0x00 | 0x03 | 0xE8 ]  ← exact same 4 bytes, same address
                 ↑
           address: 0x7ffee4bc  (unchanged)
```

The pointer value (the address) is copied as-is into the new pointer variable. Nothing in memory changes. The compiler just agrees to treat those bytes as a `float` now — even though they were never written as a `float`. That is what "binary copy of the value from one pointer to the other" means.

```cpp
int   i  = 1000;
int*  pi = &i;
float* pf = reinterpret_cast<float*>(pi);  // pf holds the exact same address as pi
                                            // the bytes of i are now "read" as a float
std::cout << *pf;  // prints garbage — the bits of 1000 (as int) make no sense as float
```

---

### All pointer conversions are allowed — no checks at all

`reinterpret_cast` does not check:
- Whether the types are related
- Whether the memory is valid
- Whether the object actually exists
- Whether sizes match

```cpp
class A { int x; };
class B { double d; };   // completely unrelated to A

A* a = new A;
B* b = reinterpret_cast<B*>(a);  // compiles — types are irrelevant
                                  // b now points to A's memory, pretending it's a B

// Even wilder — pointer to a function pointer
void myFunc() {}
void (*fp)()  = myFunc;
int* ip       = reinterpret_cast<int*>(fp);  // pointer to function → pointer to int
                                              // compiles, completely platform-dependent

// Pointer to void* and back
A*    a2  = new A;
void* vp  = reinterpret_cast<void*>(a2);   // A* → void*
A*    a3  = reinterpret_cast<A*>(vp);       // void* → A* back (safe, same address)
```

---

### Casting pointers to/from integer types — all cases

#### Why would you ever cast a pointer to an integer?

A pointer is just a memory address, and a memory address is just a number. Sometimes you need to:
- Print or log the raw address
- Store an address in a struct that only has integer fields
- Do bitwise arithmetic on an address (e.g. alignment checks)
- Interface with C libraries or hardware registers that use integers for addresses

#### The integer must be large enough to hold the address

This is the critical rule. On a 32-bit system, pointers are 4 bytes — they fit in an `int`. On a 64-bit system, pointers are 8 bytes — they do NOT fit in an `int` (only 4 bytes), you need `long` or better yet `size_t`.

```cpp
int  x = 42;
int* p = &x;

// SAFE: cast to a type large enough to hold the address
long       addr1  = reinterpret_cast<long>(p);       // works on 32-bit, risky on 64-bit
size_t     addr2  = reinterpret_cast<size_t>(p);     // size_t is always pointer-sized ✅

// Cast back to pointer — guaranteed to work if the integer was large enough
int* p2 = reinterpret_cast<int*>(addr2);  // p2 == p, points to x again ✅

// UNSAFE: integer too small
short small = reinterpret_cast<short>(p); // truncates the address — cast back would be wrong ❌
```

#### The "platform-specific format" part — simplified

The quote says *"the format in which this integer value represents a pointer is platform-specific"*. In plain terms:

> The number you get when you cast a pointer to an integer is the raw memory address. But **how addresses are numbered** depends on the OS and CPU architecture.

| Platform | Pointer size | Address range |
|---|---|---|
| 32-bit system | 4 bytes | 0 to ~4 billion |
| 64-bit system | 8 bytes | 0 to ~18 quintillion |
| Some embedded CPUs | 2 bytes | 0 to 65535 |

So the integer you get is meaningful only on the machine that produced it. Move that integer to a different architecture and it is just a meaningless number — that address does not exist there.

**The only guarantee:** if you cast a pointer to an integer type large enough (e.g. `size_t`), then cast that integer back to the original pointer type, you get the original pointer back exactly. The round-trip is guaranteed — nothing more.

```cpp
int  val = 99;
int* original = &val;

size_t as_integer = reinterpret_cast<size_t>(original);  // pointer → integer
int*   restored   = reinterpret_cast<int*>(as_integer);  // integer → pointer back

// restored == original: guaranteed ✅
// *restored == 99:      guaranteed ✅
```

---

### Low-level, system-specific, non-portable — what do these mean?

#### "Low-level"

High-level code works with objects, types, and logic. Low-level code works with raw memory addresses and bit patterns — the same things the CPU deals in. `reinterpret_cast` bypasses everything C++'s type system normally protects you from.

```cpp
// High-level (static_cast): "convert this double to int mathematically"
double d = 3.14;
int    i = static_cast<int>(d);    // i = 3 — a real mathematical conversion

// Low-level (reinterpret_cast): "give me the raw bits of this double, read as int"
int raw = *reinterpret_cast<int*>(&d);  // not 3 — the IEEE 754 bit pattern of 3.14
                                         // completely different number, platform-specific
```

#### "System-specific"

The result depends on how your OS and CPU organize memory:

```cpp
// Checking pointer alignment (must be 4-byte aligned for int on most CPUs)
int  x   = 10;
int* p   = &x;
bool aligned = (reinterpret_cast<size_t>(p) % 4 == 0);  // answer depends on where
                                                          // the OS placed x in memory
```

A different OS or compiler settings may place `x` at a different address, giving a different result.

#### "Non-portable"

Code using `reinterpret_cast` may work on one machine and break on another:

```cpp
// On a 32-bit machine: pointer fits in int — works
int* p    = &someVar;
int  addr = reinterpret_cast<int>(p);   // works on 32-bit

// On a 64-bit machine: pointer is 8 bytes, int is 4 bytes — addr is TRUNCATED
// casting addr back to int* gives the wrong address entirely ❌
```

Correctness depends on the machine — that is the definition of non-portable.

#### All realistic use cases of `reinterpret_cast`

```cpp
// 1. Inspect the raw bytes of any object
float f = 1.0f;
unsigned char* bytes = reinterpret_cast<unsigned char*>(&f);
for (int i = 0; i < (int)sizeof(float); i++)
    printf("%02X ", bytes[i]);  // 00 00 80 3F  (IEEE 754 bytes of 1.0f)

// 2. Hardware / memory-mapped register access (embedded systems)
// A hardware register lives at a fixed address decided by the circuit board
volatile int* led_register = reinterpret_cast<volatile int*>(0x40021000);
*led_register = 1;  // turn on LED — writes 1 to that hardware address

// 3. Storing a pointer as an integer (e.g. for serialisation or IPC)
int  data   = 42;
int* ptr    = &data;
size_t stored = reinterpret_cast<size_t>(ptr);        // pointer → integer
int*  recovered = reinterpret_cast<int*>(stored);     // integer → pointer back
                                                       // only valid on the SAME machine

// 4. Type-punning — reading the raw bit pattern of a float as an unsigned int
float        pi   = 3.14159f;
unsigned int bits = *reinterpret_cast<unsigned int*>(&pi);
printf("float bits: %08X\n", bits);  // 40490FD0 (IEEE 754 representation)
```

---

### Why dereferencing an incompatible pointer is unsafe

```cpp
class A { int x; };       // size: 4 bytes
class B { double d; };    // size: 8 bytes

A* a = new A;
B* b = reinterpret_cast<B*>(a);  // b points to A's 4-byte block
```

Memory layout comparison:

```
A object (allocated):          B's expected layout:
┌──────────────┐               ┌──────────────┐
│  int x       │  4 bytes      │              │
└──────────────┘               │  double d    │  8 bytes expected
                               │              │
                               └──────────────┘
```

When you access `b->d`, the compiler reads 8 bytes starting at `b`'s address. Only 4 bytes belong to the `A` object — the next 4 bytes belong to whatever is adjacent in memory (heap metadata, another variable, or unmapped memory).

- If the extra 4 bytes are readable → garbage `double` value (unexpected result)
- If they are in a protected memory page → segmentation fault (runtime crash)
- If the optimiser sees the strict aliasing violation → may eliminate or reorder the access entirely (undefined behaviour)

This is why the text says "does not make much sense" — there is no legitimate reason to read a `B` from an `A`-sized block. `reinterpret_cast` lets you write it, but the outcome is fully undefined.

---

## `const_cast`

`const_cast` is the **only** C++ cast that can add or remove `const` (and `volatile`) qualifiers from a type. It does not touch the actual bits in memory, does not change the type, does not do any conversion — it purely changes whether the compiler treats the variable as read-only or not.

> **Critical rule:** `const_cast` removes the compiler's restriction, it does NOT make the write safe. If the original object was declared `const`, writing through a `const_cast`-ed pointer is **undefined behaviour** even if it compiles.

---

### The core use case — passing a const variable to a non-const parameter

```cpp
void print(char* str) {          // expects non-const char*
    std::cout << str << std::endl;
}

int main() {
    const char* c = "sample text";
    print(const_cast<char*>(c));  // strips const so it fits the parameter
    return 0;
}
```

`print` does not modify `str` — it only reads it. But its signature says `char*` (non-const), so the compiler refuses to pass a `const char*` directly. `const_cast` removes the restriction for the duration of the call. This is safe **only because** `print` never writes to the pointer.

---

### All usage cases with examples

#### 1. Remove `const` from a pointer to pass to a legacy/C function

The most common real-world use — old C APIs that were written before `const` was common, so they take `char*` even when they don't modify the string:

```cpp
// Legacy C function — written without const, but does not modify the string
void legacy_log(char* message) {
    printf("%s\n", message);
}

void modern_function(const std::string& text) {
    // text.c_str() returns const char* — but legacy_log needs char*
    legacy_log(const_cast<char*>(text.c_str()));  // safe: legacy_log only reads it
}
```

#### 2. Remove `const` from a reference

```cpp
void double_value(int& x) {   // needs non-const reference to modify
    x *= 2;
}

int main() {
    const int val = 5;
    double_value(const_cast<int&>(val));  // compiles — but UNDEFINED BEHAVIOUR
                                          // val was declared const — writing to it
                                          // is UB even through const_cast
}
```

This compiles but is undefined behaviour — the compiler may have placed `val` in read-only memory or replaced all uses of `val` with the literal `5` at compile time. This example shows what NOT to do.

#### 3. Safe use with a non-const original object

The only truly safe case of removing const is when the original object was **not** declared const — it just arrived through a const pointer/reference:

```cpp
void increment(const int* p) {
    // p is const — but what if we know the caller passed a non-const int?
    int* writable = const_cast<int*>(p);
    (*writable)++;   // safe ONLY if the original object was not declared const
}

int main() {
    int x = 10;                // NOT const — lives in writable memory
    increment(&x);             // safe: original is non-const ✅
    std::cout << x;            // 11

    const int y = 10;          // IS const — lives in read-only memory
    increment(&y);             // compiles — but writing inside is UB ❌
}
```

#### 4. Add `const` to a pointer (the safe direction)

`const_cast` can also go the other way — adding `const`. This is always safe because you are restricting access, not expanding it:

```cpp
int  x  = 42;
int* p  = &x;

const int* cp = const_cast<const int*>(p);  // add const — always safe
// *cp = 99;  // would be a compile error now — cp is read-only
```

In practice you rarely need `const_cast` to add const (the compiler does it implicitly), but it is technically valid.

#### 5. Remove `volatile`

`const_cast` also works on `volatile`, which tells the compiler "do not cache this variable, always read it fresh from memory" (used in hardware registers and multithreading):

```cpp
volatile int hardware_flag = 0;

// A function that does not need the volatile guarantee
void process(int* p) {
    *p = 1;
}

process(const_cast<int*>(&hardware_flag));  // strips volatile so it fits the parameter
```

This is safe only if you are sure the function does not need to observe hardware changes to the variable.

#### 6. `const` method calling a non-const method — mutable workaround

In C++98, before `mutable` was widely used, `const_cast` was sometimes used inside a `const` method to call a non-const version of itself:

```cpp
class Buffer {
    char data[256];
    int  size;
public:
    // Non-const version
    char* get_data() {
        return data;
    }

    // Const version — avoid duplicating logic by casting away const
    const char* get_data() const {
        // cast away const on 'this' to call the non-const version
        return const_cast<Buffer*>(this)->get_data();
    }
};
```

This is safe because the non-const `get_data` does not actually modify the object — it just returns a pointer. The `const_cast<Buffer*>(this)` trick was a standard C++98 pattern to avoid duplicating function bodies.

---

### Summary — when is `const_cast` safe vs unsafe?

| Situation | Safe? |
|---|---|
| Original object was NOT declared `const`, arrives via `const` pointer/ref | ✅ Safe to write |
| Passing `const` pointer to a C/legacy function that only reads | ✅ Safe — no write happens |
| Original object WAS declared `const`, writing through cast | ❌ Undefined behaviour |
| Adding `const` to a pointer | ✅ Always safe |
| Stripping `volatile` when no hardware/threading concerns | ✅ Generally safe |

---

## Final Summary — How Everything Connects

### The Big Picture — One Problem, Many Solutions

Every cast in C++ exists to answer one question: **"these two types don't match — how do I bridge them?"** The entire README is a progression from "the compiler does it for you" all the way to "you do everything yourself":

```
LEAST CONTROL                                          MOST CONTROL
     │                                                      │
  Implicit ──► static_cast ──► dynamic_cast ──► reinterpret_cast
                                    │                        │
                               const_cast ◄─────────────────┘
                           (orthogonal to all)
```

---

### How the casts complete each other — the gaps they fill

**Implicit conversion** is the baseline. It handles all the safe, obvious cases automatically — numbers promoting upward (`short→int`), classes with matching constructors. The moment it refuses, you are forced into explicit territory.

**The traditional cast (`(type)expr`)** is the bridge from C — it covers everything implicit won't do, but does so blindly by trying all four named casts in order until something fits. It is the "I don't care how, just make it work" option. The four named casts exist precisely to replace it with intention.

**`static_cast`** picks up exactly where implicit conversion stops. If implicit would do it automatically, `static_cast` does it explicitly. If implicit would refuse but the types are at least *related* (inheritance chain, numerical family), `static_cast` covers that too. Its weakness: it trusts you on downcasts.

**`dynamic_cast`** plugs the exact hole `static_cast` leaves open — the unsafe downcast. Where `static_cast` says "I'll trust you", `dynamic_cast` says "I'll check at runtime". The trade-off is cost (RTTI lookup) and a requirement (the base must be polymorphic). They are direct complements: use `static_cast` when certain, `dynamic_cast` when you need a guarantee.

**`reinterpret_cast`** goes where neither `static_cast` nor `dynamic_cast` will go — completely unrelated types, raw memory, hardware addresses. It does not convert anything, it just relabels bytes. It is the escape hatch for system-level work the type system was never designed to express.

**`const_cast`** is orthogonal to all of the above — it does not change what type something is, only whether it is read-only. Every other cast can be combined with a `const` concern, and `const_cast` is the dedicated tool for that dimension alone.

---

### The safety ladder

```
dynamic_cast     — safest     — checks at RUNTIME,    returns NULL on failure
static_cast      — safe       — checks at COMPILE TIME, trusts you on downcasts
const_cast       — neutral    — no type change, safe if original was not const
reinterpret_cast — dangerous  — zero checks, raw bits, UB if misused
traditional cast — worst      — silently escalates to reinterpret_cast without warning
```

---

### The cost ladder

```
implicit / static_cast / const_cast / reinterpret_cast  — zero runtime cost
dynamic_cast                                            — runtime cost: RTTI lookup + inheritance walk
```

This is why `dynamic_cast` is not the default — you pay for it every call. `static_cast` is the free version that only works when you can prove safety yourself.

---

### When each one is the right answer

| Situation | Use |
|---|---|
| Compiler already knows the types are compatible | Implicit — do nothing |
| Numerical conversion you want to make explicit | `static_cast` |
| Upcast (derived → base pointer) | `static_cast` or implicit |
| Downcast and you are 100% certain of the type | `static_cast` |
| Downcast and you are NOT certain — need a safety net | `dynamic_cast` |
| Legacy C function needs non-const but won't modify | `const_cast` |
| Completely unrelated pointer types | `reinterpret_cast` |
| Hardware register / raw memory address | `reinterpret_cast` |
| Quick cast without caring about safety (prototype only) | traditional cast |

---

### The thread that runs through everything

Every topic in this README is about one core tension: **what the compiler knows at compile time vs what only exists at runtime**.

Implicit and `static_cast` live entirely at compile time — resolved before the program runs. `dynamic_cast` is the one moment where C++ admits the compiler does not always know enough and defers to runtime. `reinterpret_cast` abandons the type system entirely and drops to the hardware level. `const_cast` is a narrow tool for the one case where the type is right but the access permission is wrong.

Understanding that progression — compile-time knowledge eroding as you go down the ladder — is the mental model that makes every casting decision in cpp06 straightforward.
