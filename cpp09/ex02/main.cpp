#include "PmergeMe.hpp"



int main(int ac, char* av[])
{
    if (ac == 1)
        return (std::cerr << "not enough numbers\n", 1);
    
    try
    {
        size_t size = static_cast<size_t>(ac);
        PmergeMe obj(av, size);
        std::cout << "Before: ";
        printNumbers(obj.get_Vec_Con());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}