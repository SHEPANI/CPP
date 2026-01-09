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