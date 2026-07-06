#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>


template <typename T>
typename T::iterator easyfind(T& container, int num)
{
    typename T::iterator it = std::find(container.begin(), container.end(), num);

    if (it == container.end())
    {
        throw -1;
    }
    return it;
}

#endif