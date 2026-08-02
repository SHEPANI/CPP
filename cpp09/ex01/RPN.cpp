#include "RPN.hpp"

RNP::RNP()
{}

RNP::RNP(const RNP& Other)
{
    *this = Other;
}

const RNP& RNP::operator=(const RNP& Other)
{
    if (&Other != this)
        *this = Other;
    return *this;
}

void RNP::rnp(std::string exp)
{
    std::string op = "+-/*";
    for (size_t i = 0; i < exp.size(); i++)
    {
        if (exp[i] == ' ')
            continue;
        if (isdigit(exp[i]))
            stk.push((exp[i] - '0'));
        else if (op.find(exp[i]) != std::string::npos)
        {
            if (stk.empty() || stk.size() == 1)
                throw "Error\n";
            calculation(exp[i]);
        }
        else
            throw "Error\n";
    }
    if (stk.size() > 1)
        throw "Error\n";
}

void RNP::calculation(char op)
{
    int val1 = stk.top();
    stk.pop();
    int val2 = stk.top();
    stk.pop();
    int res;
    if (op == '+')
    {
        std::stringstream ss(val1 + val2);
        if (!(ss >> res))
            throw "Error\n";

    }
    else if (op == '-')
    {
        std::stringstream ss(val1 - val2);
        if (!(ss >> res))
            throw "Error\n";

    }
    else if (op == '/')
    {
        std::stringstream ss(val1 / val2);
        if (!(ss >> res))
            throw "Error\n";

    }
    else
    {
        std::stringstream ss(val1 * val2);
        if (!(ss >> res))
            throw "Error\n";

    }
    stk.push(res);
}

int RNP::getStkRes()
{
    int res = stk.top();
    return (res);
}

RNP::~RNP()
{}