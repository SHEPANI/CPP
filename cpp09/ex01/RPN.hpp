#ifndef RNP_HPP
#define RNP_HPP

#include <iostream>
#include <sstream>
#include <stack>

class RNP
{
    private:
        std::stack<int> stk;
    public:
        RNP();
        RNP(const RNP& Other);
        const RNP& operator=(const RNP& Other);
        ~RNP();
        void rnp(std::string exp);
        void calculation(char op);
        int getStkRes();

};


#endif