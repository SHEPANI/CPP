#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>

class PmergeMe
{
        std::vector<int> basevec;
        std::vector<int> vec_container;
        std::list<int> list_container;
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe& operator=(const PmergeMe &other);
        PmergeMe(char** args, size_t size);
        std::vector<int>& get_Vec_Con(); 
        std::list<int>& get_List_Con();
        ~PmergeMe();
};

template <typename T>
void printNumbers(T &numbers)
{
    typename T::iterator it = numbers.begin();
    for (;it != numbers.end();it++)
    {
        if (it != numbers.begin())
            std::cout << " ";
        std::cout << *it;
    }
    std::cout << "\n";
}

#endif