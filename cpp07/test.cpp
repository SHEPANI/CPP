#include <iostream>

int main()
{
    int *a;
    a = new int[10]();
    for (int i = 0; i < 10;i++)
        std::cout << *a++ << "\n";
}