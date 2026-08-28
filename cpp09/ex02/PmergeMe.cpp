#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{};


PmergeMe::PmergeMe(const PmergeMe& other)
{
    *this = other;
};

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        *this = other;
    }
    return *this;
};

PmergeMe::PmergeMe(char** args, size_t size)
{
    std::string arg;
    std::stringstream ss;
    int nm = 0;

    for (size_t i = 1; i < size; i++)
    {
        ss.clear();
        ss.str(args[i]);
        while (ss >> arg)
        {
            for (size_t j = 0; j < arg.size(); j++)
            {
                if (!isdigit(arg[j]))
                    throw std::runtime_error("bad argment\n");
            }

            ss.clear();
            ss.str(arg);
            if (!(ss >> nm))
                throw std::runtime_error("bad argment\n");

            if (std::find(vec_container.begin(), vec_container.end(), nm) != vec_container.end())
                throw std::runtime_error("duplicates arg\n");
            vec_container.push_back(nm);
            list_container.push_back(nm);
        }
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
