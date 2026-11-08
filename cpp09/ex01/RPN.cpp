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
        throw "Error calculation uncorrect\n";
}

void RNP::calculation(char op)
{
    double val2 = stk.top();
    stk.pop();
    double val1 = stk.top();
    stk.pop();
    double res = 0;
    if (op == '+')
        res = val1 + val2;
    else if (op == '-')
        res = val1 - val2;
    else if (op == '*')
        res = val1 * val2;
    else if (op == '/')
    {
        if (val2 == 0)
            throw "Error division by zero\n";
        res = val1 / val2;
    }
    stk.push(res);
}

double RNP::getStkRes()
{
    if (stk.empty())
        throw "Error\n";
    double res = stk.top();
    return (res);
}

RNP::~RNP()
{}