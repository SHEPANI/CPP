#include <stdexcept>
#include <iostream>

template <class T>
Array<T>::Array() : arr(NULL), arrSize(0)
{
};

template <class T>
Array<T>::Array(unsigned int n) : arrSize(n)
{
    if (n > 0)
        arr = new T[n]();
    else
        arr = NULL;
};

template <class T>
Array<T>::Array(const Array<T>& Other) : arr(NULL), arrSize(0)
{
    *this = Other;
}

template <class T>
Array<T>& Array<T>::operator=(const Array<T>& Other)
{
    if (this != &Other) 
    {
        delete[] this->arr; 
        this->arrSize = Other.arrSize;
        if (this->arrSize > 0) 
        {
            this->arr = new T[this->arrSize]();
            for (unsigned int i = 0; i < this->arrSize; i++)
                this->arr[i] = Other.arr[i];
        }
        else
            this->arr = NULL;
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
const T& Array<T>::operator[](unsigned int index) const
{
    if (index >= arrSize || arr == NULL) 
            throw std::out_of_range("Index out of bounds");
    return arr[index];
}


template <class T>
Array<T>::~Array()
{
    delete[] arr;
}