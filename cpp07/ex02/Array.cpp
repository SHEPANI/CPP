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
Array<T>::Array(const Array<T>& Other) : arr(NULL), arrSize(0)
{
    *this = Other;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& Other) // in the parameters way work without <T> 
{
    if (this != &other) 
    {
        delete[] this->arr; // bad allocation issuse for new down
        this->arrSize = other.arrSize;
        if (this->arrSize > 0) 
        {
            this->arr = new T[this->arrSize]();
            for (unsigned int i = 0; i < this->arrSize; i++)
                this->arr[i] = other.arr[i];
        }
        else
            this->arr = NULL;
    }
    return *this;
}


template <class T>
unsigned int Array<T>::size() const
{
    return this->size;
}

template <class T>
T& Array<T>::operator[](unsigned int index)
{
    if (index >= _size || _elements == NULL) 
            throw std::out_of_range("Index out of bounds");
    return _elements[index];
}

template <class T>
const T& Array<T>::operator[](unsigned int index) const // way we need this second const
{
    if (index >= _size || _elements == NULL) 
            throw std::out_of_range("Index out of bounds");
    return _elements[index];
}


template <typename T>
Array<T>::~Array()
{
    delete[] arr;
}