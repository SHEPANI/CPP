

#include "Span.hpp"

Span::Span() : N(0)
{
};

Span::Span(const Span& Other){
    *this = Other;
};
const Span& Span::operator=(const Span& Other)
{
    if (this != &Other)
    {
        this->N = Other.N;
        this->numbers = Other.numbers;
    }
    return *this;
};
Span::Span(const unsigned int n)
{
    this->N = n;
};

void Span::addNumber(int nm)
{
    if (numbers.size() >= this->N)
        throw std::length_error("Span is full");
    numbers.push_back(nm);
};

int Span::longestSpan()
{
    if (numbers.size() < 2)
        throw std::out_of_range("numbers vector has less than 2 numbers");
    std::vector<int>::iterator min_nm = std::min_element(numbers.begin(), numbers.end());
    std::vector<int>::iterator max_nm = std::max_element(numbers.begin(), numbers.end());
    return (*max_nm - *min_nm);
}

int Span::shortestSpan()
{
    if (numbers.size() < 2)
        throw std::out_of_range("numbers vector has less than 2 numbers");
    std::vector<int> sorted(numbers.begin(), numbers.end());
    std::sort(sorted.begin(), sorted.end());
    std::vector<int> adDiffResult(sorted.size());
    std::adjacent_difference(sorted.begin(), sorted.end(),adDiffResult.begin());
    std::vector<int>::iterator span = std::min_element(adDiffResult.begin() + 1, adDiffResult.end());
    return (*span);
}




Span::~Span()
{
};