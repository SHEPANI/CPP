#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <numeric>
#include <algorithm>

class Span
{
    private:
        unsigned int N;
        std::vector<int> numbers;
    public:
        Span();
        Span(const Span& Other);
        const Span& operator=(const Span& Other);
        Span(const unsigned int n);
        ~Span();

        void addNumber(int nm);
        int longestSpan();
        int shortestSpan();

        template <typename iterator>  
        void add_Multiple_Numbers(iterator beginit,iterator endit)
        {
            if (numbers.size() + (unsigned int)(std::distance(beginit, endit)) > N)
                throw std::length_error("Span is full");
            for (iterator it = beginit; it != endit; it++)
                numbers.push_back(*it);
        }
};

#endif