
#include <array>
#include <iostream>

int main()
{
    int a[10];
    a[17] = 9;
    std::array<int, 10> b;
    b[17] = 15;
    std::cout << "a[17] = " << a[17] << "\nb[17] = " << b[17] <<"\n"; 
}