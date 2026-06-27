# C++98 Templates, Containers, Iterators & Algorithms
### Reference Guide for `cpp07` — ISO/IEC 14882:1998

---

## Table of Contents

0. [What is the STL?](#0-what-is-the-stl)
   - [The Short Answer](#01-the-short-answer)
   - [Where STL Came From](#02-where-stl-came-from)
   - [Why the Standard Itself Never Says "STL"](#03-why-the-standard-itself-never-says-stl)
   - [The Four Pillars and How They Connect](#04-the-four-pillars-and-how-they-connect)
   - [A Mental Model](#05-a-mental-model)
1. [Templates (Chapter 14)](#1-templates)
   - [What is a Template?](#11-what-is-a-template)
   - [Class Templates](#12-class-templates)
   - [Function Templates](#13-function-templates)
   - [Template Parameters](#14-template-parameters)
   - [Template Specialization](#15-template-specialization)
   - [Template Instantiation](#16-template-instantiation)
   - [Non-type Template Parameters](#17-non-type-template-parameters)
   - [Template Template Parameters](#18-template-template-parameters)
2. [Containers (Chapter 23)](#2-containers)
   - [Container Requirements](#21-container-requirements)
   - [vector](#22-vector)
   - [list](#23-list)
   - [deque](#24-deque)
   - [map](#25-map)
   - [set](#26-set)
   - [stack / queue / priority\_queue](#27-stack--queue--priority_queue)
3. [Iterators (Chapter 24)](#3-iterators)
   - [Iterator Categories](#31-iterator-categories)
   - [Iterator Traits](#32-iterator-traits)
   - [Reverse Iterators](#33-reverse-iterators)
   - [Insert Iterators](#34-insert-iterators)
4. [Algorithms (Chapter 25)](#4-algorithms)
   - [Non-Modifying Operations](#41-non-modifying-sequence-operations)
   - [Modifying Operations](#42-modifying-sequence-operations)
   - [Sorting & Binary Search](#43-sorting--binary-search)
5. [Quick Cheat Sheet](#5-quick-cheat-sheet)

---

## 0. What is the STL?

### 0.1 The Short Answer

**STL = Standard Template Library.** It's the name of the *original library* — designed by Alexander Stepanov (with Meng Lee and David Musser) — that introduced **containers, iterators, algorithms, and function objects** as a unified, template-based system to C++.

When your 1337 peers, subject PDFs, or older tutorials say "the STL," they almost always mean: **`vector`, `list`, `map`, `set`, iterators, and `<algorithm>` functions like `sort`/`find`/`transform`.** That's it. It's not a separate library you `#include` — it's a *design* that got absorbed into the C++ Standard Library itself.

```
"STL"                          ≈   the containers + iterators + algorithms
                                    + function objects parts of...

std (the C++ Standard Library) =   STL-derived parts  +  streams (iostream)
                                    +  strings  +  locales  +  numerics  + ...
```

> STL ⊂ std — the STL is a (large, foundational) **part** of the Standard Library, not the whole thing.

---

### 0.2 Where STL Came From

This is historical context — **not** something you'll find written in the ISO standard, but essential for understanding *why* the standard is organized the way it is.

| Year | Event |
|---|---|
| 1979–1992 | Stepanov develops the theory of **generic programming** (algorithms decoupled from data structures), first explored in Ada and Scheme |
| 1992 | Stepanov + Meng Lee formalize this as a C++ library at HP Labs |
| Nov 1993 | Stepanov presents the library to the ANSI/ISO C++ committee, who respond favorably |
| 1994 | A formal proposal is developed; associative containers (map/set) are added and validated by David Musser; approved by the committee in July 1994 |
| 1994 | HP makes their implementation freely available, becoming the basis for many vendor implementations |
| 1998 | Formally incorporated into ISO/IEC 14882:1998 — the exact PDF you uploaded |

So when you opened that PDF and saw §23 Containers, §24 Iterators, §25 Algorithms — **you were reading the STL**. It just isn't called that inside the document, because by 1998 it had been folded into "the C++ Standard Library" as a whole.

---

### 0.3 Why the Standard Itself Never Says "STL"

I searched the entire 776-page document you gave me for the literal string "STL" or "Standard Template Library." **It appears nowhere.**

That's not an oversight — it reflects a real distinction:

> The STL and the C++ Standard Library are two distinct entities, though sometimes the parts of the C++ Standard Library directly influenced/inherited from the STL are called "the STL".

In other words:
- **"STL"** = the informal/historical name people use, referring to Stepanov's original design and the chapters it produced (§23–§25, plus pieces of §20).
- **"C++ Standard Library"** = the *official* name in ISO/IEC 14882, covering everything: containers/iterators/algorithms **and also** streams, strings, locales, exceptions, numerics, etc.

This is why your README chapters are titled "Containers library," "Iterators library," "Algorithms library" — that's the standard's own vocabulary. "STL" is the name for that same material in everyday programmer speech (forums, older books, your professors).

**Practical implication for you at 1337:** if a subject PDF says "implement using the STL," it means: *use these C++98 standard containers/iterators/algorithms* — exactly the chapters 14, 23, 24, 25 you're studying. They are the same thing.

---

### 0.4 The Four Pillars and How They Connect

> The STL provides a set of common classes for C++, such as containers and associative arrays, that can be used with any built-in type or user-defined type that supports some elementary operations. STL algorithms are independent of containers, which significantly reduces the complexity of the library.

The STL design rests on **decoupling** — each pillar knows as little as possible about the others:

```
┌─────────────┐        ┌─────────────┐        ┌──────────────┐
│  CONTAINERS │ ──────▶│  ITERATORS  │◀────── │  ALGORITHMS  │
│ vector, list│ expose │ the "glue"  │are used │ sort, find,  │
│ map, set... │        │  layer      │   by    │ transform...│
└─────────────┘        └─────────────┘        └──────────────┘
                              ▲
                              │ built using
                       ┌─────────────┐
                       │  TEMPLATES  │
                       │  (Ch. 14)   │
                       │ the language
                       │  mechanism  │
                       └─────────────┘
```

- **Templates** (§14) are the *language feature* that makes all of this possible — generic code generated at compile time.
- **Containers** (§23) *use* templates to store any type, and each one *exposes* an iterator.
- **Iterators** (§24) are the **only thing algorithms know about**. An algorithm never sees a `vector` or a `list` directly — only an iterator.
- **Algorithms** (§25) are template functions written purely in terms of iterators, so the *same* `std::sort` line of code can work on a `vector<int>`, a `vector<MyClass>`, or even a raw C array — anything that hands it the right kind of iterator.

> Iterators are the major feature that allow the generality of the STL — an algorithm to reverse a sequence can be implemented using bidirectional iterators, and then the same implementation can be used on lists, vectors and deques. User-created containers only have to provide an iterator that implements one of the five standard iterator interfaces, and all the algorithms provided in the library become available to them for free.

This is the entire point of the STL: **write an algorithm once, run it on any container that exposes the right iterator category** — no inheritance, no virtual functions, no runtime cost. This is also exactly why your cpp07 project exists: 1337 wants you to *build* this decoupling yourself with templates before you fully appreciate why the real STL is shaped the way it is.

---

### 0.5 A Mental Model

```
Templates   →  the GRAMMAR     (how to write generic code)
Containers  →  the NOUNS       (where data lives)
Iterators   →  the VERBS' BRIDGE (how you reach into the nouns)
Algorithms  →  the VERBS       (what you do to the data)
```

Concretely, every single STL-style line you'll write follows this shape:

```cpp
std::vector<int> v;                          // container — a noun
v.push_back(1); v.push_back(2); v.push_back(3);

std::sort(v.begin(), v.end());               // algorithm + iterators (begin/end)
//        └────┬────┘  └───┬───┘
//          verb        the bridge into the noun

template<class T>                            // <- the grammar underneath it ALL
void printAll(typename std::vector<T>::iterator first,
              typename std::vector<T>::iterator last) {
    for (; first != last; ++first) std::cout << *first << " ";
}
```

Take away the templates, and none of this compiles for arbitrary `T`. Take away iterators, and `sort` would need a separate copy-pasted version for every container type. That's the relationship in one sentence:

**Templates are the *mechanism*; containers, iterators, and algorithms are the *application* of that mechanism, deliberately split into three independent pieces so any one of them can be swapped out without touching the others.**

---

## 1. Templates

### 1.1 What is a Template?

> *"A template defines a family of classes or functions."*
> — ISO/IEC 14882:1998, §14 [temp]

A **template** is a blueprint that lets you write a single class or function that works with **any type**, decided at compile time. Instead of writing `maxInt`, `maxDouble`, `maxChar`... you write `max<T>` once.

```
compile time
     ↓
template<class T>     →  T = int   →  max<int>(...)   (a real function)
max(T a, T b)         →  T = float →  max<float>(...) (another real function)
                      →  T = MyClass → max<MyClass>(...) (yet another!)
```

The compiler **instantiates** (generates) a concrete version for each type you use.

---

### 1.2 Class Templates

**Syntax** (§14.5.1):
```cpp
template < template-parameter-list > class ClassName { ... };
```

**Example from the Standard (§14.5.1):**
```cpp
template<class T>
class Array {
    T*  v;      // pointer to array of T
    int sz;
public:
    explicit Array(int);
    T&  operator[](int);
    T&  elem(int i) { return v[i]; }
};

// Using the template:
Array<int>    v1(20);       // Array of int, size 20
Array<double> v2(30);       // Array of double, size 30

v1[3]    = 7;
v2[3]    = 3.14;
```

**Key rule:** `Array` alone is NOT a type. `Array<int>` IS a type (a *specialization*).

**Member functions defined outside the class:**
```cpp
// Must repeat the template header
template<class T>
T& Array<T>::operator[](int i) {
    return v[i];
}
```

---

### 1.3 Function Templates

**Syntax** (§14.5.5):
```cpp
template<class T>
ReturnType functionName(Parameters) { ... }
```

**Example:**
```cpp
template<class T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

int    x = max(3, 5);         // T deduced as int
double y = max(1.2, 3.4);     // T deduced as double
// explicit:
int    z = max<int>(3, 5);
```

**Overloading function templates** (§14.5.5.1):
Function templates can be overloaded with each other and with normal functions:
```cpp
template<class T>
void print(T val) { /* generic */ }

void print(const char* s) { /* specialized for C-strings */ }

print(42);       // calls template: print<int>
print("hello");  // calls non-template: print(const char*)
```

---

### 1.4 Template Parameters

Three kinds (§14.1):

| Kind | Syntax | Example |
|------|--------|---------|
| **Type** | `class T` or `typename T` | `template<class T>` |
| **Non-type** | a value | `template<int N>` |
| **Template** | another template | `template<template<class> class C>` |

`class` and `typename` are **identical** for type parameters — use either.

**Default template arguments:**
```cpp
template<class T, class Allocator = allocator<T> >
class vector { ... };      // Allocator has a default

vector<int>          v1;   // uses allocator<int>
vector<int, MyAlloc> v2;   // uses custom allocator
```

**Rule:** Once you give one parameter a default, ALL following parameters must also have defaults (§14.1 ¶11).

---

### 1.5 Template Specialization

#### Full (Explicit) Specialization (§14.7.3)
Override the generic template for a **specific type**:

```cpp
// Generic template:
template<class T>
class stream { /* works for any T */ };

// Full specialization for char:
template<>
class stream<char> {
    // Completely different implementation for char!
};
```

**Function template full specialization:**
```cpp
template<class T>
void sort(Array<T>& v) { /* generic sort */ }

template<>
void sort<char*>(Array<char*>&) { /* optimized for char* */ }
```

The `template<>` prefix signals an explicit specialization. No template parameters remain.

#### Partial Specialization (§14.5.4)
Specialize for a **subset of types**, keeping some parameters generic:

```cpp
// Primary template:
template<class T, class U>
class Pair { /* general */ };

// Partial: when both types are the same:
template<class T>
class Pair<T, T> { /* optimization when T==U */ };

// Partial: pointer types:
template<class T>
class Pair<T*, T*> { /* special handling for pointers */ };
```

> **Rule (§14.5.4):** Partial specialization is only for **class templates**, not function templates.

---

### 1.6 Template Instantiation

**Implicit instantiation** (§14.7.1):
The compiler generates the code automatically when you first use a specialization:

```cpp
template<class T>
class Z {
public:
    void f();
    void g();
};

void h() {
    Z<int>    a;      // instantiates Z<int>  (class only, not members yet)
    Z<char>*  p;      // NO instantiation (just a pointer)
    Z<double>* q;     // NO instantiation (just a pointer)

    a.f();            // NOW instantiates Z<int>::f()
    p->g();           // instantiates Z<char> AND Z<char>::g()
}
```

**Explicit instantiation** (§14.7.2):
Force the compiler to generate a specific instantiation:
```cpp
template class Array<int>;       // force-instantiate entire class
template void sort<double>(Array<double>&);  // force-instantiate function
```

**The One Definition Rule (§14.4):**
A non-exported template must be defined in every translation unit where it is implicitly instantiated. This is why template implementations usually go in **header files** (or `.tpp` files included by headers).

---

### 1.7 Non-type Template Parameters

Instead of a type, use a **compile-time value** (§14.1 ¶4):
- Integral or enumeration type
- Pointer to object or function
- Reference to object or function
- Pointer to member

```cpp
template<class T, int N>     // N is a non-type parameter
class FixedArray {
    T data[N];               // array size known at compile time!
public:
    T& operator[](int i) { return data[i]; }
    int size() const { return N; }
};

FixedArray<int, 10>   a;     // array of 10 ints, no heap allocation
FixedArray<double, 5> b;     // array of 5 doubles
```

**Restrictions (§14.1 ¶7):**
```cpp
template<double d> class X;      // ERROR: floating point not allowed
template<double* pd> class Y;    // OK: pointer to double IS allowed
template<double& rd> class Z;    // OK: reference IS allowed
```

---

### 1.8 Template Template Parameters

A template that takes **another template** as a parameter (§14.1 ¶2):

```cpp
template<class T> class MyArray { /* ... */ };

template<class K,
         class V,
         template<class T> class C = MyArray>  // C is a template parameter
class Map {
    C<K> keys;
    C<V> values;
};

Map<int, std::string>             m1;  // uses default MyArray
Map<int, std::string, std::vector> m2; // uses std::vector
```

---

## 2. Containers

### 2.1 Container Requirements

> *"Containers are objects that store other objects. They control allocation and deallocation of these objects through constructors, destructors, insert and erase operations."*
> — ISO/IEC 14882:1998, §23.1 [lib.container.requirements]

Every standard container provides (§23.1, Table 65):

| Expression | Return Type | Meaning |
|---|---|---|
| `X::value_type` | `T` | Type of stored element |
| `X::iterator` | Iterator | Iterator pointing to `T` |
| `X::const_iterator` | Const Iterator | Read-only iterator |
| `X::size_type` | Unsigned integral | Size type |
| `X::difference_type` | Signed integral | Distance between iterators |
| `a.begin()` | `iterator` | Iterator to first element |
| `a.end()` | `iterator` | Past-the-end iterator |
| `a.size()` | `size_type` | Number of elements |
| `a.empty()` | bool | `a.size() == 0` |
| `a.swap(b)` | void | Exchange contents |
| `a == b` | bool | Element-wise equality |
| `a < b` | bool | Lexicographic comparison |

**The Element type `T` must be:**
- `CopyConstructible`
- `Assignable`

---

### 2.2 `vector`

**Header:** `<vector>`  
**Iterator category:** Random access

A **dynamically-sized array**. Elements are stored **contiguously** in memory, like a C array, but it grows automatically.

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v;          // empty vector

    v.push_back(10);             // add to end: [10]
    v.push_back(20);             // [10, 20]
    v.push_back(30);             // [10, 20, 30]

    std::cout << v[1];           // 20 (no bounds check)
    std::cout << v.at(1);        // 20 (with bounds check, throws if OOB)
    std::cout << v.front();      // 10
    std::cout << v.back();       // 30

    v.pop_back();                // removes last: [10, 20]
    std::cout << v.size();       // 2

    // Iterator loop:
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << " ";
}
```

**Capacity vs Size (§23.2.4.2):**
```cpp
std::vector<int> v;
v.reserve(100);                  // pre-allocate space for 100 elements
std::cout << v.size();           // 0  (no elements yet)
std::cout << v.capacity();       // 100 (memory reserved)
```
- `size()` = number of actual elements
- `capacity()` = allocated memory slots (>= size)
- `reserve()` avoids repeated reallocations

**Complexity:**
- `push_back` / `pop_back` → O(1) amortized
- `insert` / `erase` in middle → O(n)
- `operator[]` / `at` → O(1)

---

### 2.3 `list`

**Header:** `<list>`  
**Iterator category:** Bidirectional

A **doubly-linked list**. No contiguous memory, but O(1) insert/erase **anywhere**.

> *"A list is a kind of sequence that supports bidirectional iterators and allows constant time insert and erase operations anywhere within the sequence."* — §23.2.2

```cpp
#include <list>

std::list<int> lst;

lst.push_back(10);               // [10]
lst.push_front(5);               // [5, 10]
lst.push_back(20);               // [5, 10, 20]

std::list<int>::iterator it = lst.begin();
++it;                            // points to 10
lst.insert(it, 7);               // [5, 7, 10, 20]
lst.erase(it);                   // removes 10: [5, 7, 20]

lst.pop_front();                 // removes 5: [7, 20]
lst.pop_back();                  // removes 20: [7]
```

**List-specific operations (§23.2.2.4):**
```cpp
std::list<int> a = {1, 2, 3};
std::list<int> b = {4, 5, 6};

a.splice(a.end(), b);            // move all of b into a: a=[1,2,3,4,5,6], b=[]

std::list<int> c = {3, 1, 4, 1, 5};
c.sort();                        // [1, 1, 3, 4, 5]
c.unique();                      // [1, 3, 4, 5] (removes consecutive duplicates)
c.reverse();                     // [5, 4, 3, 1]
```

**vs vector:**
| | `vector` | `list` |
|---|---|---|
| Memory layout | Contiguous | Scattered (nodes) |
| Random access | O(1) via `[]` | O(n) — no `[]` |
| Insert at end | O(1) amortized | O(1) |
| Insert in middle | O(n) | O(1) (with iterator) |
| Iterator type | Random access | Bidirectional |

---

### 2.4 `deque`

**Header:** `<deque>`  
**Iterator category:** Random access

A **double-ended queue**. Like `vector` but fast at both ends.

```cpp
#include <deque>

std::deque<int> dq;

dq.push_back(10);                // [10]
dq.push_front(5);                // [5, 10]    ← fast!
dq.push_back(20);                // [5, 10, 20]
dq.push_front(1);                // [1, 5, 10, 20]

std::cout << dq[2];              // 10 — random access works!
dq.pop_front();                  // [5, 10, 20]
dq.pop_back();                   // [5, 10]
```

**When to use:** When you need fast access from both ends but also `operator[]`.  
`std::stack` and `std::queue` use `deque` as their default underlying container.

---

### 2.5 `map`

**Header:** `<map>`  
**Iterator category:** Bidirectional  
**Ordered by:** Key (using `operator<` by default)

> *"A map is a kind of associative container that supports unique keys and provides for fast retrieval of values of another type T based on the keys."* — §23.3.1

```cpp
template <class Key, class T,
          class Compare   = less<Key>,
          class Allocator = allocator<pair<const Key, T> > >
class map { ... };
```

```cpp
#include <map>
#include <string>

std::map<std::string, int> scores;

scores["Alice"] = 95;
scores["Bob"]   = 87;
scores["Carol"] = 92;

// Lookup:
std::cout << scores["Alice"];    // 95
std::cout << scores.at("Bob");   // 87 (throws if key absent)

// find() (safe — doesn't insert on miss):
std::map<std::string,int>::iterator it = scores.find("Dave");
if (it == scores.end())
    std::cout << "Dave not found";
else
    std::cout << it->second;     // it->first = key, it->second = value

// Iterating (always sorted by key):
for (it = scores.begin(); it != scores.end(); ++it)
    std::cout << it->first << ": " << it->second << "\n";
// Output: Alice: 95, Bob: 87, Carol: 92  (alphabetical order)

// Insert:
scores.insert(std::make_pair("Dave", 78));

// Erase:
scores.erase("Bob");
std::cout << scores.size();      // 3
```

**`operator[]` WARNING:** `map["key"]` **inserts** a default-constructed value if key doesn't exist! Use `find()` for safe lookup.

**`multimap`:** Same as `map` but allows duplicate keys. No `operator[]`.

---

### 2.6 `set`

**Header:** `<set>`  
**Iterator category:** Bidirectional  
**Ordered by:** Element value

A container of **unique, sorted values** — like `map` but storing only keys (no associated values).

```cpp
#include <set>

std::set<int> s;
s.insert(30);
s.insert(10);
s.insert(20);
s.insert(10);              // duplicate — silently ignored

// s is always sorted: {10, 20, 30}

std::cout << s.count(10);  // 1 (present)
std::cout << s.count(99);  // 0 (absent)

s.erase(20);               // {10, 30}

// find:
std::set<int>::iterator it = s.find(10);
if (it != s.end()) std::cout << "found: " << *it;

// iterate (always sorted):
for (it = s.begin(); it != s.end(); ++it)
    std::cout << *it << " ";   // 10 30
```

**`multiset`:** Like `set` but allows duplicates.

---

### 2.7 `stack` / `queue` / `priority_queue`

**Header:** `<stack>`, `<queue>`  
These are **container adaptors** — they wrap an underlying container (default: `deque`) and restrict the interface.

#### `stack` (LIFO) — §23.2.3.3
```cpp
#include <stack>

std::stack<int> stk;
stk.push(1);
stk.push(2);
stk.push(3);

std::cout << stk.top();    // 3
stk.pop();                 // removes 3
std::cout << stk.top();    // 2
std::cout << stk.size();   // 2
std::cout << stk.empty();  // false
```

#### `queue` (FIFO) — §23.2.3.1
```cpp
#include <queue>

std::queue<int> q;
q.push(1);
q.push(2);
q.push(3);

std::cout << q.front();    // 1 (oldest)
std::cout << q.back();     // 3 (newest)
q.pop();                   // removes 1
std::cout << q.front();    // 2
```

#### `priority_queue` (largest element always on top) — §23.2.3.2
```cpp
#include <queue>

std::priority_queue<int> pq;
pq.push(30);
pq.push(10);
pq.push(50);
pq.push(20);

std::cout << pq.top();     // 50 (max element)
pq.pop();
std::cout << pq.top();     // 30
```

---

## 3. Iterators

### 3.1 Iterator Categories

> *"Iterators are a generalization of pointers that allow a C++ program to work with different data structures in a uniform manner."*
> — ISO/IEC 14882:1998, §24.1 [lib.iterator.requirements]

The standard defines **5 iterator categories** in a hierarchy (§24.1, Table 71):

```
Random Access
      ↓
Bidirectional
      ↓
   Forward
      ↓
   Input         Output
```

Each category inherits all capabilities of those below it.

| Category | Read | Write | `++` | `--` | `+n` / `[n]` | Used by |
|---|---|---|---|---|---|---|
| **Input** | ✓ once | — | ✓ | — | — | `istream_iterator` |
| **Output** | — | ✓ once | ✓ | — | — | `ostream_iterator` |
| **Forward** | ✓ | ✓ | ✓ | — | — | `forward_list` (C++11) |
| **Bidirectional** | ✓ | ✓ | ✓ | ✓ | — | `list`, `map`, `set` |
| **Random Access** | ✓ | ✓ | ✓ | ✓ | ✓ | `vector`, `deque`, arrays |

#### Input Iterator requirements (§24.1.1, Table 72):
```cpp
X u(a);     // copy-constructible
u = a;      // copy-assignable
a == b;     // equality comparable
a != b;
*a;         // dereferenceable (read)
a->m;       // member access
++r;        // pre-increment
r++;        // post-increment
```

#### Bidirectional adds (§24.1.4):
```cpp
--r;        // pre-decrement
r--;        // post-decrement
```

#### Random Access adds (§24.1.5):
```cpp
r += n;
a + n;      // advance n steps
n + a;
r -= n;
a - n;
b - a;      // distance between iterators
a[n];       // random access
a < b;      // ordering
a > b;
a >= b;
a <= b;
```

#### The fundamental iterator loop pattern:
```cpp
// [first, last)  — half-open range
// first points to first element
// last  points ONE PAST the last element

for (ContainerType::iterator it = c.begin(); it != c.end(); ++it) {
    // *it is the current element
    // it->member accesses member of element
}
```

---

### 3.2 Iterator Traits

**Header:** `<iterator>` (§24.3.1)

`iterator_traits<Iterator>` gives you information about **any** iterator type:

```cpp
template<class Iterator>
struct iterator_traits {
    typedef Iterator::difference_type   difference_type;
    typedef Iterator::value_type        value_type;
    typedef Iterator::pointer           pointer;
    typedef Iterator::reference         reference;
    typedef Iterator::iterator_category iterator_category;
};
```

**Why this matters for templates:**
```cpp
// Works for any iterator type:
template<class Iterator>
typename std::iterator_traits<Iterator>::difference_type
my_distance(Iterator first, Iterator last) {
    typename std::iterator_traits<Iterator>::difference_type n = 0;
    while (first != last) { ++first; ++n; }
    return n;
}

std::vector<int> v(10);
std::cout << my_distance(v.begin(), v.end());  // 10
```

**Tag dispatch** — the standard uses iterator categories to pick the most efficient algorithm:
```cpp
// advance() works for all, but is O(n) for bidirectional,
// O(1) for random access. The tags let the compiler pick:
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};
```

---

### 3.3 Reverse Iterators

**Header:** `<iterator>` — Template class `reverse_iterator` (§24.4.1)

Wraps any bidirectional iterator and reverses the direction of traversal:

```cpp
#include <vector>
#include <iostream>

std::vector<int> v;
v.push_back(1); v.push_back(2); v.push_back(3);

// Forward:
for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    std::cout << *it << " ";     // 1 2 3

// Reverse:
for (std::vector<int>::reverse_iterator rit = v.rbegin(); rit != v.rend(); ++rit)
    std::cout << *rit << " ";    // 3 2 1
```

`rbegin()` → points to last element  
`rend()` → points "before" first element  
`++rit` moves **backward** through the container

---

### 3.4 Insert Iterators

Insert iterators allow algorithms to **insert into** a container rather than overwrite (§24.4.2).

```cpp
#include <iterator>
#include <vector>
#include <algorithm>

std::vector<int> src = {1, 2, 3};
std::vector<int> dst;

// copy() normally OVERWRITES, but with back_inserter it APPENDS:
std::copy(src.begin(), src.end(), std::back_inserter(dst));
// dst is now {1, 2, 3}

std::vector<int> dst2;
std::copy(src.begin(), src.end(), std::front_inserter(dst2));
// dst2 is now {3, 2, 1} (each inserted at front reverses order)
```

| Adaptor | Inserts at | Underlying call |
|---|---|---|
| `back_insert_iterator<C>` | back | `c.push_back(value)` |
| `front_insert_iterator<C>` | front | `c.push_front(value)` |
| `insert_iterator<C>` | given position | `c.insert(pos, value)` |

**Factory functions:** `back_inserter(c)`, `front_inserter(c)`, `inserter(c, pos)`.

---

## 4. Algorithms

**Header:** `<algorithm>`

> *"This clause describes components that C++ programs may use to perform algorithmic operations on containers and other sequences."*
> — ISO/IEC 14882:1998, §25 [lib.algorithms]

All algorithms work on **iterator ranges** `[first, last)` and are **container-independent**. The same `sort` works on `vector`, `deque`, arrays, etc.

---

### 4.1 Non-Modifying Sequence Operations

#### `for_each` (§25.1.1)
Apply a function to every element:
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

void print(int x) { std::cout << x << " "; }

std::vector<int> v;
v.push_back(1); v.push_back(2); v.push_back(3);

std::for_each(v.begin(), v.end(), print);   // 1 2 3
```

#### `find` / `find_if` (§25.1.2)
```cpp
std::vector<int> v;
v.push_back(10); v.push_back(20); v.push_back(30);

// find by value:
std::vector<int>::iterator it = std::find(v.begin(), v.end(), 20);
if (it != v.end())
    std::cout << "Found: " << *it;   // Found: 20

// find_if with a predicate (function returning bool):
bool greaterThan15(int x) { return x > 15; }

it = std::find_if(v.begin(), v.end(), greaterThan15);
// it points to 20
```

#### `count` / `count_if` (§25.1.6)
```cpp
std::vector<int> v;
v.push_back(1); v.push_back(2); v.push_back(2); v.push_back(3);

int n = std::count(v.begin(), v.end(), 2);       // n = 2

bool isEven(int x) { return x % 2 == 0; }
int m = std::count_if(v.begin(), v.end(), isEven); // m = 2
```

#### `equal` (§25.1.8)
```cpp
std::vector<int> a, b;
a.push_back(1); a.push_back(2); a.push_back(3);
b.push_back(1); b.push_back(2); b.push_back(3);

bool same = std::equal(a.begin(), a.end(), b.begin());  // true
```

---

### 4.2 Modifying Sequence Operations

#### `copy` (§25.2.1)
```cpp
std::vector<int> src;
src.push_back(1); src.push_back(2); src.push_back(3);
std::vector<int> dst(3);  // must have enough space!

std::copy(src.begin(), src.end(), dst.begin());
// OR use back_inserter (no pre-sizing needed):
std::vector<int> dst2;
std::copy(src.begin(), src.end(), std::back_inserter(dst2));
```

#### `fill` / `fill_n` (§25.2.6)
```cpp
std::vector<int> v(5);
std::fill(v.begin(), v.end(), 42);      // [42, 42, 42, 42, 42]
std::fill_n(v.begin(), 3, 0);           // [0,  0,  0,  42, 42]
```

#### `transform` (§25.2.3)
Apply a function to each element and write results to output:
```cpp
std::vector<int> v;
v.push_back(1); v.push_back(2); v.push_back(3);
std::vector<int> result(3);

int timesTwo(int x) { return x * 2; }
std::transform(v.begin(), v.end(), result.begin(), timesTwo);
// result = [2, 4, 6]

// Two-range version (binary operation):
std::vector<int> a, b, c(3);
a.push_back(1); a.push_back(2); a.push_back(3);
b.push_back(10); b.push_back(20); b.push_back(30);

int add(int x, int y) { return x + y; }
std::transform(a.begin(), a.end(), b.begin(), c.begin(), add);
// c = [11, 22, 33]
```

#### `replace` / `replace_if` (§25.2.4)
```cpp
std::vector<int> v;
v.push_back(1); v.push_back(2); v.push_back(2); v.push_back(3);

std::replace(v.begin(), v.end(), 2, 99);   // [1, 99, 99, 3]

bool isOdd(int x) { return x % 2 != 0; }
std::replace_if(v.begin(), v.end(), isOdd, 0);   // [0, 99, 99, 0]
```

#### `remove` / `remove_if` (§25.2.7)
> **IMPORTANT:** `remove` does NOT shrink the container. It moves elements and returns a new "end" iterator. You must call `erase` yourself.

```cpp
std::vector<int> v;
v.push_back(1); v.push_back(2); v.push_back(3); v.push_back(2); v.push_back(4);

// The erase-remove idiom:
v.erase(std::remove(v.begin(), v.end(), 2), v.end());
// v = [1, 3, 4]

bool isEven(int x) { return x % 2 == 0; }
v.erase(std::remove_if(v.begin(), v.end(), isEven), v.end());
// v = [1, 3]
```

#### `reverse` (§25.2.9)
```cpp
std::vector<int> v;
v.push_back(1); v.push_back(2); v.push_back(3);

std::reverse(v.begin(), v.end());   // [3, 2, 1]
```

---

### 4.3 Sorting & Binary Search

#### `sort` (§25.3.1)
Requires **random access iterators** (works with `vector`, `deque`, arrays — NOT `list` or `map`).

> *"All the operations in §25.3 have two versions: one that takes a function object of type Compare and one that uses operator<."*

```cpp
std::vector<int> v;
v.push_back(3); v.push_back(1); v.push_back(4); v.push_back(1); v.push_back(5);

// Default: ascending order using operator<:
std::sort(v.begin(), v.end());      // [1, 1, 3, 4, 5]

// With custom comparator (descending):
bool descending(int a, int b) { return a > b; }
std::sort(v.begin(), v.end(), descending);   // [5, 4, 3, 1, 1]
```

**Sorting with structs:**
```cpp
struct Student {
    std::string name;
    int grade;
};

bool byGrade(const Student& a, const Student& b) {
    return a.grade > b.grade;   // higher grade first
}

std::vector<Student> students;
// ... fill students ...
std::sort(students.begin(), students.end(), byGrade);
```

**Complexity:** O(n log n) average.

#### `stable_sort` (§25.3.1.2)
Like `sort`, but **preserves relative order** of equal elements. O(n log² n).

#### Binary Search (§25.3.3)
**Precondition:** Range must already be sorted.

```cpp
std::vector<int> v;
v.push_back(1); v.push_back(2); v.push_back(3); v.push_back(4); v.push_back(5);

// binary_search: is it there? (O(log n))
bool found = std::binary_search(v.begin(), v.end(), 3);   // true
bool found2 = std::binary_search(v.begin(), v.end(), 99); // false

// lower_bound: iterator to first element >= value
std::vector<int>::iterator lb = std::lower_bound(v.begin(), v.end(), 3);
// *lb == 3

// upper_bound: iterator to first element > value
std::vector<int>::iterator ub = std::upper_bound(v.begin(), v.end(), 3);
// *ub == 4

// equal_range: pair<lower_bound, upper_bound>
std::pair<std::vector<int>::iterator,
          std::vector<int>::iterator> range;
range = std::equal_range(v.begin(), v.end(), 3);
// range.first points to 3, range.second points to 4
```

#### `min` / `max` / `min_element` / `max_element`
```cpp
std::cout << std::min(3, 7);      // 3
std::cout << std::max(3, 7);      // 7

std::vector<int> v;
v.push_back(5); v.push_back(1); v.push_back(8); v.push_back(3);

std::vector<int>::iterator minIt = std::min_element(v.begin(), v.end());
std::vector<int>::iterator maxIt = std::max_element(v.begin(), v.end());
std::cout << *minIt;   // 1
std::cout << *maxIt;   // 8
```

---

## 5. Quick Cheat Sheet

### Pick Your Container

```
Need fast random access?           → vector  (or deque if also need push_front)
Need fast insert/erase anywhere?   → list
Need sorted unique keys?           → set
Need key→value mapping?            → map
Need LIFO (stack)?                 → stack
Need FIFO (queue)?                 → queue
Need max always accessible?        → priority_queue
Allow duplicate keys in map?       → multimap
Allow duplicate values in set?     → multiset
```

### Iterator Compatibility

```
Input    ← Forward ← Bidirectional ← Random Access
                           ↑                ↑
              list, map, set       vector, deque, array

Use the WEAKEST iterator category your algorithm needs.
```

### Algorithm Quick Reference

| Algorithm | Header | Iterator Needed | Notes |
|---|---|---|---|
| `for_each` | `<algorithm>` | Input | Apply function to all |
| `find` | `<algorithm>` | Input | Linear search |
| `find_if` | `<algorithm>` | Input | Search with predicate |
| `count` | `<algorithm>` | Input | Count occurrences |
| `count_if` | `<algorithm>` | Input | Count matching |
| `equal` | `<algorithm>` | Input | Compare two ranges |
| `copy` | `<algorithm>` | Input + Output | Copy elements |
| `fill` | `<algorithm>` | Forward | Set all to value |
| `transform` | `<algorithm>` | Input + Output | Map function over range |
| `replace` | `<algorithm>` | Forward | Replace value |
| `remove` | `<algorithm>` | Forward | Logical remove (use + erase!) |
| `reverse` | `<algorithm>` | Bidirectional | Reverse in place |
| `sort` | `<algorithm>` | **Random Access** | O(n log n) |
| `stable_sort` | `<algorithm>` | **Random Access** | Preserves equal order |
| `binary_search` | `<algorithm>` | Forward (sorted!) | O(log n) |
| `lower_bound` | `<algorithm>` | Forward (sorted!) | First ≥ value |
| `upper_bound` | `<algorithm>` | Forward (sorted!) | First > value |
| `min` / `max` | `<algorithm>` | — | Compare two values |
| `min_element` | `<algorithm>` | Forward | Smallest in range |
| `max_element` | `<algorithm>` | Forward | Largest in range |

### Common Gotchas

```cpp
// ❌ WRONG: map[] inserts on miss!
if (myMap["key"] == 0) { ... }   // inserts "key" if not present

// ✓ CORRECT: use find()
if (myMap.find("key") != myMap.end()) { ... }

// ❌ WRONG: remove() doesn't shrink the vector
std::remove(v.begin(), v.end(), 42);  // elements moved but size unchanged

// ✓ CORRECT: erase-remove idiom
v.erase(std::remove(v.begin(), v.end(), 42), v.end());

// ❌ WRONG: sort needs random access — won't compile with list!
std::sort(myList.begin(), myList.end());

// ✓ CORRECT: list has its own sort member:
myList.sort();

// ❌ WRONG: template implementation in .cpp (linker error)
// template<class T> class Foo { ... };  (header)
// template<class T> void Foo<T>::bar() { ... }  (separate .cpp)

// ✓ CORRECT: put full template implementation in the header (or .tpp included by header)
```

---

## References

- ISO/IEC 14882:1998 — *Programming Languages: C++*
  - §14 Templates
  - §23 Containers library
  - §24 Iterators library
  - §25 Algorithms library
- Stepanov, A. & Lee, M. — original Standard Template Library design (HP Labs, 1994), incorporated into ANSI/ISO C++ draft standard, clauses 17–27. The historical/informal name "STL" is **not** used anywhere in ISO/IEC 14882:1998 itself — see [§0](#0-what-is-the-stl) above.
