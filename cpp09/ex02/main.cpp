#include "PmergeMe.hpp"

double exact_time()
{
    struct timeval t;
    gettimeofday(&t, 0);
    double mstime = t.tv_sec * 1000000.0 + t.tv_usec;
    return mstime;    
}


int main(int ac, char* av[])
{
    if (ac == 1)
        return (std::cerr << "not enough numbers\n", 1);
    
    try
    {
        double vecstrat = 0, vecend = 0;
        size_t size = static_cast<size_t>(ac);
        PmergeMe obj(av, size);
        std::cout << "Before: ";
        printNumbers(obj.get_Vec_Con());
        vecstrat = exact_time();
        obj.setVec(obj.get_Vec_Con());
        vecend = exact_time() - vecstrat;
        std::cout << "After: ";
        printNumbers(obj.get_Vec_Con());
        double deckstrat = 0, deckend = 0;
        deckstrat = exact_time();
        obj.setdeck(obj.get_deck_Con());
        deckend = exact_time() - deckstrat;
        std::cout.setf(std::ios::fixed);
        std::cout.precision(5);
        std::cout << "Time to process a range of " << obj.get_Vec_Con().size() << " elements with std::vector : " << vecend << " us\n";
        std::cout <<  "Time to process a range of " << obj.get_deck_Con().size() << " elements with std::deque : " << deckend << " us\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}