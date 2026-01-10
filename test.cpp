#include <string>
#include <iostream>



int main()
{
    std::string color ="hello";
    color += "bldssd";
    std::cout << color;

    return 0;
}

/*The hidden this pointer
Inside every member function, the keyword "this"
is a const pointer that holds the address of the current implicit object.
Most of the time, we don’t mention this explicitly, but just to prove we can:
*/

/*  If std::string doesn’t have enough memory to store a string,
 it will request additional memory (at runtime) using a form of memory allocation known as dynamic memory allocation.
 This ability to acquire additional memory is part of what makes std::string so flexible, but also comparatively slow.*/

/*std::string s = "Hello";
What happens internally in C++98:
The string literal "Hello" exists in read-only memory
std::string:
allocates memory on the heap (enough for 6 chars including '\0')
copies 'H' 'e' 'l' 'l' 'o' '\0' one by one

📌 This is the “expensive” part
Heap allocation + character copy = time + CPU*/

/*
TECHNICAL DIFFERENCES (What the compiler sees)
1. Default Access Level
struct: Members are public by default
class: Members are private by default
2. Default Inheritance (minor)
struct: Inherits publicly by default
class: Inherits privately by default
That's literally it from a technical standpoint!

PRACTICAL DIFFERENCES (How we use them)

Use struct when ALL of these are true:
✅ Simple collection of data - no complex logic
✅ No need to restrict access - all members can be public
✅ Aggregate initialization is sufficient - can use {} to initialize
✅ No invariants/setup/cleanup needed - no special initialization or destruction logic

Use class in ALL other cases:
✅ When you need data hiding (private members)
✅ When you need member functions that do more than simple operations
✅ When you have class invariants to maintain (rules about valid states)
✅ When you need constructors for complex initialization
✅ When you need destructors for cleanup

*/

/*

2️⃣ const with member functions (super important for 42)
Why do we need it?
It guarantees that the function does NOT modify the object.

Example
class Sample {
    int _value;

public:
    int getValue() const {
        return _value;
    }

    void setValue(int v) {
        _value = v;
    }
};

What does getValue() const mean?

➡️ Inside this function, you cannot change any member variable.

int getValue() const {
    _value = 10; // ❌ COMPILATION ERROR
}

42 likes this a LOT because it shows discipline and correctness.

3️⃣ const object
const Sample s;
s.getValue();     // ✅ OK
s.setValue(10);   // ❌ ERROR

Why?
➡️ A const object can only call const member functi*/