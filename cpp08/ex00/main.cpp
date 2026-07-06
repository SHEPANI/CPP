

#include "easyfind.hpp"

int main()
{
    try
    {
        std::vector<int> vec;
        vec.push_back(2);
        vec.push_back(4);
        vec.push_back(3);
        std::vector<int>::iterator it =  easyfind<std::vector<int> >(vec, 3);
        std::cout << *it <<"\n";
        it =  easyfind<std::vector<int> >(vec, 34);
        std::cout << *it <<"\n";
        it =  easyfind<std::vector<int> >(vec, 1);
        std::cout << *it <<"\n";

    }
    catch(...)
    {
        std::cout << "error\n";
    }

    try
    {
        std::list<int> lst;
        lst.push_back(2);
        lst.push_back(4);
        lst.push_back(3);
        std::list<int>::iterator it =  easyfind<std::list<int> >(lst, 3);
        std::cout << *it <<"\n";
        it =  easyfind<std::list<int> >(lst, 5);
        std::cout << *it <<"\n";
        it =  easyfind<std::list<int> >(lst, 1);
        std::cout << *it <<"\n";

    }
    catch(...)
    {
        std::cout << "error\n";
    }

    try
    {
        std::deque<int> deq;
        deq.push_back(2);
        deq.push_back(4);
        deq.push_back(3);
        std::deque<int>::iterator it =  easyfind<std::deque<int> >(deq, 4);
        std::cout << *it <<"\n";
        it =  easyfind<std::deque<int> >(deq, 2);
        std::cout << *it <<"\n";
        it =  easyfind<std::deque<int> >(deq, 17);
        std::cout << *it <<"\n";

    }
    catch(...)
    {
        std::cout << "error\n";
    }
    



}