#include "MutantStack.hpp"


int main()
{
    {
        MutantStack<int> mstack;
        mstack.push(5);
        mstack.push(17);
        std::cout << mstack.top() << std::endl;
        mstack.pop();
        std::cout << mstack.size() << std::endl;
        mstack.push(3);
        mstack.push(5);
        mstack.push(737);
        //[...]
        mstack.push(0);
        MutantStack<int>::iterator it = mstack.begin();
        MutantStack<int>::iterator ite = mstack.end();
        ++it;
        --it;
        while (it != ite)
        {
            std::cout << *it << std::endl;
            ++it;
        }
        std::stack<int> s(mstack);
    }
    std::cout << "\ntest the same code with list instead of stack default deque\n\n";
    {
        MutantStack<int, std::list<int> > mstacklst;
        mstacklst.push(5);
        mstacklst.push(17);
        std::cout << mstacklst.top() << std::endl;
        mstacklst.pop();
        std::cout << mstacklst.size() << std::endl;
        mstacklst.push(3);
        mstacklst.push(5);
        mstacklst.push(737);
        //[...]
        mstacklst.push(0);
        MutantStack<int, std::list<int> >::iterator it = mstacklst.begin();
        MutantStack<int, std::list<int> >::iterator ite = mstacklst.end();
        ++it;
        --it;
        while (it != ite)
        {
            std::cout << *it << std::endl;
            ++it;
        }
    }
    std::cout << "\ntest the same code with vector instead of stack default deque\n\n";
    {
        MutantStack<int, std::vector<int> > mstackvec;
        mstackvec.push(5);
        mstackvec.push(17);
        std::cout << mstackvec.top() << std::endl;
        mstackvec.pop();
        std::cout << mstackvec.size() << std::endl;
        mstackvec.push(3);
        mstackvec.push(5);
        mstackvec.push(737);
        //[...]
        mstackvec.push(0);
        MutantStack<int, std::vector<int> >::iterator it = mstackvec.begin();
        MutantStack<int, std::vector<int> >::iterator ite = mstackvec.end();
        ++it;
        --it;
        while (it != ite)
        {
            std::cout << *it << std::endl;
            ++it;
        }
    }
    return 0;
}
