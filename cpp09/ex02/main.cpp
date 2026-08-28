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
        vecend = exact_time() - vecstrat;
        (void)(vecend);
        // (void)(vecend);
        // double deckstrat = 0, deckend = 0;
        // deckstrat = exact_time();
        // deckend = exact_time() - deckend;

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}