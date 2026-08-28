#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <sys/time.h>


class PmergeMe
{
        std::vector<int> basevec;
        std::vector<int> vec_container;
        std::deque<int> deck_container;
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe& operator=(const PmergeMe &other);
        PmergeMe(char** args, size_t size);
        void setVec(std::vector<int> &vec);
        void setdeck(std::deque<int> &deck);
        std::vector<int> sortedVec(std::vector<int> &veContainer);
        std::deque<int> sorteDeck(std::deque<int> &deckContainer);
        std::vector<int>& get_Vec_Con(); 
        std::deque<int>& get_deck_Con();
        std::vector<size_t> right_order(size_t wSize);

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