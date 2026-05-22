#include "A.hpp"
#include "C.hpp"
#include "B.hpp"
#include <iostream>

Base* generate(void)
{
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
        (void)dynamic_cast<A&>(p);
        std::cout << "A\n";
        return;
    }
    catch(...)
    {
    }

    try
    {
        (void)dynamic_cast<B&>(p);
        std::cout << "B\n";
        return;
    }
    catch(...)
    {
    }

    try
    {
        (void)dynamic_cast<C&>(p);
        std::cout << "C\n";
    }
    catch(...)
    {
    }
}


int main()
{
    std::srand(std::time(0));
    Base* a = generate();
    identify(a);
    identify(*a);
    delete a;
    return 0;
}