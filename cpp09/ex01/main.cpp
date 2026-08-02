#include "RPN.hpp"

int main(int ac, char* av[])
{
    if (ac != 2 || !av || !av[0])
        return 1;

    RNP a;
    try
    {
        a.rnp(av[1]);
        std::cout << a.getStkRes() << "\n";
    }
    catch(const char* err)
    {
        std::cerr << err << '\n';
    }
    
}