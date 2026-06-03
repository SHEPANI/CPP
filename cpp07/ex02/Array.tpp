#include "Array.hpp"
#include <stdexcept>

template <typename T>
Array<T>::Array() : arr(NULL), arrSize(0)
{
};

template <typename T>
Array<T>::Array(unsigned int n) : arrSize(n)
{
    if (n <= 0)
        arr = NULL;
    else
        arr = new T[n]();
};

template <typename T>
Array<T>::Array(const Array& Other) : arr(NULL), arrSize(0)
{
    *this = Other;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& Other) // in the parameters way work without <T>
{
    if (this != &Other) 
    {
        delete[] arr;
        arrSize = Other.arrSize;
        if (arrSize > 0) 
        {
            arr = new T[arrSize];
            for (unsigned int i = 0; i < arrSize; i++)
                arr[i] = Other.arr[i];
        }
        else
            arr = NULL;
    }
    return *this;
}


template <class T>
unsigned int Array<T>::size() const
{
    return this->arrSize;
}

template <class T>
T& Array<T>::operator[](unsigned int index)
{
    if (index >= arrSize || arr == NULL) 
            throw std::out_of_range("Index out of bounds");
    return arr[index];
}

template <class T>
const T& Array<T>::operator[](unsigned int index) const // way we need this second const
{
    if (index >= arrSize || arr == NULL) 
            throw std::out_of_range("Index out of bounds");
    return arr[index];
}


template <typename T>
Array<T>::~Array()
{
    delete[] arr;
}