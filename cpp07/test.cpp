#include <iostream>


template <class myType>
myType GetMax(myType a, myType b)
{
    return (a > b ? a : b);
}

int main()
{
    // {
    //     int *a;
    //     a = new int[10]();
    //     for (int i = 0; i < 10;i++)
    //         std::cout << *a++ << "\n";
    // }

    {
        int x, y;
        std::cout << GetMax <int> (x=10,y=15) << "\n";
        // or
        double i, j;
        std::cout << GetMax (i=13, j=39.8) << "\n";
        std::string str1 = "hello";
        std::string str2 = "wborld";
        std::cout << GetMax <std::string> (str1, str2) << "\n";
        // or this shulde set err
        // std::cout <<GetMax <std::string> (x, j) << "\n";
    }
}