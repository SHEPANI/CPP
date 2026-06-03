#ifndef ITER_H
#define ITER_H
#include <cstddef> 
#include <iostream>

template <typename T, typename Func>
void iter(T* arr,const size_t len,Func func)
{
    for (size_t i = 0; i < len; i++)
    {
        func(arr[i]);
    }
}

template <typename T>
void printArrElement(T const& element)
{
    std::cout << element << " ";
}

#endif
