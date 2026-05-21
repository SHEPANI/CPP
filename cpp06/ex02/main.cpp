#include "A.hpp"
#include "C.hpp"
#include "B.hpp"
#include "Base.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base* generate(void)
{
    std::srand(std::time(0));
    int	choices = rand() % 3;
    if (choices == 0)
        return new A();
    else if (choices == 1)
        return new B();
    else
        return new C();
}

void identify(Base* p)
{
    if (dynamic_cast<A*>(p))
        std::cout << "A\n";
    else if (dynamic_cast<B*>(p))
        std::cout << "B\n";
    else if (dynamic_cast<C*>(p))
        std::cout << "C\n";
}

void identify(Base& p)
{
    try
    {
        dynamic_cast<A&>(p);
        std::cout << "A\n";
        return;
    }
    catch(const std::exception& e)
    {
        std::cerr << "A : " <<  e.what() << '\n';
    }

    try
    {
        dynamic_cast<B&>(p);
        std::cout << "B\n";
        return;
    }
    catch(const std::exception& e)
    {
        std::cerr << "B : " << e.what() << '\n';
    }

    try
    {
        dynamic_cast<C&>(p);
        std::cout << "C\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << "C : " << e.what() << '\n';
    }
}


int main()
{
    Base* a = generate();
    identify(a);
    identify(*a);
    delete a;
    return 0;
}