# C++ Template Pairs — ISO/IEC 14882:1998(E)

**Source document:** ISO/IEC 14882:1998(E) — *Programming Languages — C++*, First Edition (C++98)
**Total pairs identified:** 26 (4 grammar pairs + 22 standard-library specialization pairs)

---

## Overview

Two categories of template pairs exist in this standard:

**A. Grammar Parameter–Argument Pairs (Chapter 14 / Annex A.12)**
The C++ grammar defines exactly three kinds of template parameters, each with a corresponding argument form. These are the fundamental building blocks for all templates in the language.

**B. Standard Library Explicit Specialization Pairs (Chapters 18–26)**
The standard library defines a set of primary class templates that are explicitly specialized for specific types. Each pair consists of a primary template declaration and one `template<>` specialization.

---

## Part A — Grammar Parameter–Argument Pairs

Defined in §14.1 [temp.param], §14.3 [temp.arg], and summarized in Annex A.12 [gram.temp].

### G1 — Type Parameter (`class`)

| Field | Value |
|---|---|
| **ID** | G1 |
| **Parameter syntax** | `class identifieropt [= type-id]` |
| **Argument syntax** | `type-id` |
| **Section** | 14.1 / 14.3.1 |
| **Cross-ref** | [temp.param] / [temp.arg.type] |

A type template parameter introduced with the `class` keyword. At instantiation, any valid type-id may be supplied. Local types, unnamed types, and types with no linkage are excluded from use as arguments (§14.3.1 §2).

**Example:**
```cpp
template<class T> class vector { /* ... */ };
vector<int> v;       // T = int
vector<MyClass> w;   // T = MyClass
```

---

### G2 — Type Parameter (`typename`)

| Field | Value |
|---|---|
| **ID** | G2 |
| **Parameter syntax** | `typename identifieropt [= type-id]` |
| **Argument syntax** | `type-id` |
| **Section** | 14.1 / 14.3.1 |
| **Cross-ref** | [temp.param] / [temp.arg.type] |

Semantically identical to G1. The standard states: *"There is no semantic difference between class and typename in a template-parameter"* (§14.1 §2). `typename` is preferred in modern usage to distinguish type parameters from class names.

**Example:**
```cpp
template<typename T> T max(T a, T b) { return a > b ? a : b; }
```

---

### G3 — Non-Type Parameter

| Field | Value |
|---|---|
| **ID** | G3 |
| **Parameter syntax** | `type-specifier declarator [= constant-expression]` |
| **Argument syntax** | `assignment-expression` (must be a constant expression) |
| **Section** | 14.1 / 14.3.2 |
| **Cross-ref** | [temp.param] / [temp.arg.nontype] |

A value (non-type) template parameter. The parameter must have one of the following types (§14.1 §4):
- Integral or enumeration type
- Pointer to object or pointer to function
- Reference to object or reference to function
- Pointer to member

Floating-point, class, and void types are explicitly prohibited (§14.1 §7).

**Example:**
```cpp
template<int N> class array { int data[N]; };
array<10> a;           // N = 10 (integral constant)

template<int* p> class X { };
int buf[5];
X<buf> x;              // p = pointer with external linkage
```

---

### G4 — Template Template Parameter

| Field | Value |
|---|---|
| **ID** | G4 |
| **Parameter syntax** | `template < template-parameter-list > class identifieropt [= id-expression]` |
| **Argument syntax** | `id-expression` (must name a primary class template) |
| **Section** | 14.1 / 14.3.3 |
| **Cross-ref** | [temp.param] / [temp.arg.template] |

A template parameter that itself takes a class template as its argument. Only primary class templates are considered for matching; partial specializations are not (§14.3.3 §1).

**Example:**
```cpp
template<class T> class myarray { /* ... */ };

template<class K, class V, template<class T> class C = myarray>
class Map {
    C<K> key;
    C<V> value;
};

Map<int, string> m;          // C = myarray (default)
Map<int, string, vector> m2; // C = vector (explicit)
```

---

## Part B — Standard Library Explicit Specialization Pairs

These are `(primary template, explicit specialization)` pairs where the library mandates a `template<>` definition for a specific type argument. All specializations are in `namespace std`.

---

### `numeric_limits` Specializations — `<limits>` §18.2 [lib.numeric.limits]

Primary template: `template<class T> class numeric_limits`

| ID | Specialization | Description |
|---|---|---|
| S01 | `template<> class numeric_limits<bool>` | Boolean type |
| S02 | `template<> class numeric_limits<char>` | Narrow character |
| S03 | `template<> class numeric_limits<signed char>` | Signed byte |
| S04 | `template<> class numeric_limits<unsigned char>` | Unsigned byte |
| S05 | `template<> class numeric_limits<wchar_t>` | Wide character |
| S06 | `template<> class numeric_limits<short>` | Short integer |
| S07 | `template<> class numeric_limits<int>` | Integer |
| S08 | `template<> class numeric_limits<long>` | Long integer |
| S09 | `template<> class numeric_limits<unsigned short>` | Unsigned short |
| S10 | `template<> class numeric_limits<unsigned int>` | Unsigned int |
| S11 | `template<> class numeric_limits<unsigned long>` | Unsigned long |
| S12 | `template<> class numeric_limits<float>` | Single-precision float |
| S13 | `template<> class numeric_limits<double>` | Double-precision float |
| S14 | `template<> class numeric_limits<long double>` | Extended-precision float |

Each specialization provides implementation-defined constants such as `min()`, `max()`, `digits`, `epsilon()`, `is_integer`, `is_signed`, etc.

---

### `allocator` Specialization — `<memory>` §20.4.1 [lib.default.allocator]

Primary template: `template<class T> class allocator`

| ID | Specialization | Description |
|---|---|---|
| S15 | `template<> class allocator<void>` | Void allocator — provides only `pointer`, `const_pointer`, `value_type` typedefs and `rebind`. Reference-to-void members are impossible and are omitted. |

---

### `char_traits` Specializations — `<string>` §21.1.3 [lib.char.traits.specializations]

Primary template: `template<class charT> struct char_traits`

| ID | Specialization | Section | Description |
|---|---|---|---|
| S16 | `template<> struct char_traits<char>` | 21.1.3.1 | Narrow character traits. `int_type` = `int`, uses `EOF`. Narrow-oriented iostream classes. |
| S17 | `template<> struct char_traits<wchar_t>` | 21.1.3.2 | Wide character traits. `int_type` = `wint_t`, uses `WEOF`. Wide-oriented iostream classes. |

---

### `ctype` Specializations — `<locale>` §22.2.1 [lib.locale.ctype]

| ID | Primary | Specialization | Section | Description |
|---|---|---|---|---|
| S18 | `template<class charT> class ctype` | `template<> class ctype<char>` | 22.2.1.3 | Char specialization avoids virtual dispatch for classification; exposes a mask table directly. |
| S19 | `template<class charT> class ctype_byname` | `template<> class ctype_byname<char>` | 22.2.1.4 | Locale-named char ctype; derives from `ctype<char>`. |

---

### `complex` Specializations — `<complex>` §26.2 [lib.complex]

Primary template: `template<class T> class complex`

| ID | Specialization | Description |
|---|---|---|
| S20 | `template<> class complex<float>` | Single-precision complex number |
| S21 | `template<> class complex<double>` | Double-precision complex number |
| S22 | `template<> class complex<long double>` | Extended-precision complex number |

The three floating-point specializations guarantee interoperability: a `complex<double>` can be constructed from a `complex<float>`, and so on.

---

## Summary Table

| ID | Kind | Primary / Parameter Form | Specialization / Argument Form | Header / Section |
|---|---|---|---|---|
| G1 | Grammar | `class identifieropt` | `type-id` | §14.1/14.3.1 |
| G2 | Grammar | `typename identifieropt` | `type-id` | §14.1/14.3.1 |
| G3 | Grammar | `type-specifier declarator` (non-type) | `assignment-expression` | §14.1/14.3.2 |
| G4 | Grammar | `template<...> class identifier` | class template name (`id-expression`) | §14.1/14.3.3 |
| S01–S14 | Stdlib | `template<class T> class numeric_limits` | `numeric_limits<bool/char/…/long double>` | `<limits>` §18.2 |
| S15 | Stdlib | `template<class T> class allocator` | `allocator<void>` | `<memory>` §20.4.1 |
| S16–S17 | Stdlib | `template<class charT> struct char_traits` | `char_traits<char/wchar_t>` | `<string>` §21.1.3 |
| S18 | Stdlib | `template<class charT> class ctype` | `ctype<char>` | `<locale>` §22.2.1.3 |
| S19 | Stdlib | `template<class charT> class ctype_byname` | `ctype_byname<char>` | `<locale>` §22.2.1.4 |
| S20–S22 | Stdlib | `template<class T> class complex` | `complex<float/double/long double>` | `<complex>` §26.2 |

---

*Extracted from ISO/IEC 14882:1998(E), 776 pages, First edition 1998-09-01.*
