#include "searchable_array_bag.hpp"
#include "array_bag.hpp"
#include <iostream>
    // searchable_array_bag::searchable_array_bag() : array_bag()
    // {

    // }
    // searchable_array_bag::~searchable_array_bag()
    // {

    // }
    // searchable_array_bag::searchable_array_bag(const searchable_array_bag &o) : array_bag(o)
    // {

    // }
    // searchable_array_bag &searchable_array_bag::operator=(const searchable_array_bag &o)
    // {
    //     if(this != &o)
    //     {
    //         array_bag::operator=(o);
    //     }
    //     return *this;
    // }

	// bool searchable_array_bag::has(int v) const
    // {
    //     for(int i = 0; i < size ; ++i)
    //     {
    //         // std::cout << "here bag" << std::endl;
    //         if(data[i] == v)
    //             return true;
    //     }
    //     return false;
    // }

searchable_array_bag::searchable_array_bag() : array_bag() {};
searchable_array_bag::searchable_array_bag(const searchable_array_bag& Other) : array_bag(Other){};
searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag& Other) {
    if (this != &Other)
    {
        *this = Other;
    }
    return (*this);
};

searchable_array_bag::~searchable_array_bag(){};

bool searchable_array_bag::haselement(int v) const
{
    for (int i = 0; i < size; i++)
    {
        if (data[i] == v)
            return true;
    }
    return false;
}