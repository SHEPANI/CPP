#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{};


PmergeMe::PmergeMe(const PmergeMe& other)
{};

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{};

PmergeMe::PmergeMe(char** args, size_t size)
{
    std::string arg;
    std::stringstream ss;
    int nm = 0;

    for (size_t i = 1; i < size; i++)
    {
        
    }
};

std::vector<int>& PmergeMe::get_Vec_Con()
{
    return vec_container;
};
std::list<int>& PmergeMe::get_List_Con()
{
    return list_container;
};

PmergeMe::~PmergeMe()
{};
