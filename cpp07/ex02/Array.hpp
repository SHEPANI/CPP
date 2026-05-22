#ifndef ARRAY_HPP
#define ARRAY_HPP

template <typename T> 
class Array
{
    private:
        T* arr;
        unsigned int arrSize;
    public:
        Array();
        Array(unsigned int n);
        Array(const Array& Other);
        Array& operator=(const Array& Other);
        unsigned int size();
        T& operator[](unsigned int index);
        const T& operator[](unsigned int index) const;
        ~Array();
};



#endif