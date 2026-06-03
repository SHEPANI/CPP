#include <iostream>


template <class myType>
myType GetMax(myType a, myType b)
{
    return (a > b ? a : b);
}
template<class T>
class Array {
    T*  v;
    int sz;
public:
    Array(){};
    ~Array(){};
    // explicit Array(int size);
    // T& operator[](int i);
    // T& elem(int i) { return v[i]; }
    // ...
};
template<class T> void h(const T&){std::cout << "const\n";};   // A
// template<class T> void h(Array<T>&){std::cout << "non-const\n";};  // B: more specialized

int main()
{
    // {
    //     int *a;
    //     a = new int[10]();
    //     for (int i = 0; i < 10;i++)
    //         std::cout << *a++ << "\n";
    // }

    // {
    //     int x, y;
    //     std::cout << GetMax <int> (x=10,y=15) << "\n";
    //     // or
    //     double i, j;
    //     std::cout << GetMax (i=13, j=39.8) << "\n";
    //     std::string str1 = "hello";
    //     std::string str2 = "wborld";
    //     std::cout << GetMax <std::string> (str1, str2) << "\n";
    //     // or this shulde set err
    //     // std::cout <<GetMax <std::string> (x, j) << "\n";
    //     // std::cout <<GetMax  (x, j) << "\n";
    // }
    // {
    //     Array<int>       z1;
    //     h(z1);    // calls B: h(Array<T>&) is more specialized

    //     const Array<int> z2;
    //     h(z2);    // calls A: h(Array<T>&) is not callable for const
    // }
    {
        int * b = new int[100];

        for (int i = 0; i < 100; ++i) {
            b[i] = 424242; // Fill memory with junk
        }
        delete []b;
        int * a = new int[100];
        std::cout << "a[5] = " << a[5] << "\n";
        delete[] a;
        int * c = new int[100]();
        std::cout << "c[5]() = " << c[5] << "\n";
        delete[] a;
    }
}