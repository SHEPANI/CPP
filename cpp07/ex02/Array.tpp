#include "Array.hpp"




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
    *this = other;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& Other) // in the parameters way work without <T>
{
    if (this != &other) 
    {
        delete[] arr;
        arrSize = other.arrSize;
        if (arrSize > 0) 
        {
            arr = new T[arrSize];
            for (unsigned int i = 0; i < arrSize; i++)
                arr[i] = other.arr[i];
        }
        else
            arr = NULL;
    }
    return *this;
}


template <class T>
unsigned int Array<T>::size()
{
    return this->size;
}

template <class T>
T& Array<T>::operator[](unsigned int index)
{
    
}

template <class T>
const T& Array<T>::operator[](unsigned int index) const // way we need this second const
{
    
}


template <typename T>
Array<T>::~Array()
{
    delete[] arr;
}