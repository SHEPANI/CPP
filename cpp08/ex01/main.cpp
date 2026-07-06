
#include "Span.hpp"

int main()
{
    try
    {
        std::cout << "example 1: subject example\n";
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    try
    {
        std::cout << "\nexample 2: simple example\n";
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        sp.addNumber(17);
        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        std::cout << "\nexample 3: fill span with add_multiple_Numbers vector\n";
        Span sp = Span(100);
        std::vector<int> vec;
        vec.push_back(1);
        vec.push_back(3);
        vec.push_back(4);
        vec.push_back(6);
        vec.push_back(9);
        vec.push_back(2);
        sp.add_Multiple_Numbers(vec.begin(), vec.end());
        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        std::cout << "\nexample 3: fill span with add_multiple_Numbers list\n";
        Span sp = Span(7);
        sp.addNumber(6);
        sp.addNumber(1000);
        std::list<int> lst;
        lst.push_back(11);
        lst.push_back(21);
        lst.push_back(32);
        lst.push_back(37);
        sp.add_Multiple_Numbers(lst.begin(), lst.end());
        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
        lst.push_back(1);
        lst.push_back(3);
        lst.push_back(6);
        lst.push_back(4);
        lst.push_back(9);
        lst.push_back(2);
        sp.add_Multiple_Numbers(lst.begin(), lst.end());
        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        std::cout << "\nexample 3: fill span with add_multiple_Numbers deque\n";
        Span sp = Span(10000);
        sp.addNumber(6);
        sp.addNumber(1000);
        std::list<int> deck;
        deck.push_back(11);
        deck.push_back(21);
        deck.push_back(32);
        deck.push_back(37);
        sp.add_Multiple_Numbers(deck.begin(), deck.end());
        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
        deck.push_back(1);
        deck.push_back(3);
        deck.push_back(6);
        deck.push_back(4);
        deck.push_back(9);
        deck.push_back(2);
        sp.add_Multiple_Numbers(deck.begin(), deck.end());
        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}