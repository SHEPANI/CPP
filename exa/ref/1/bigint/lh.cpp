#include "lh.hpp"


// void bigint::remove_zeros()
// {
//     while (store[0] == '0' && store.size() > 1)
//         store.erase(0,1);
// }

// std::string& reverse_r(std::string& res)
// {
    
// }

// std::string bigint::add_string(const std::string& a, const std::string& b)
// {
//     int i = a.length() -1, j = b.length() -1, c = 0, sum;
//     std::string res;
//     while (i >= 0 || j >= 0 || c)
//     {
//         sum = c + (i>=0?a[i--] -'0':0) + (j>=0?b[j--]-'0':0);
//         res += (sum%10) + '0';
//         c = sum/10;
//     }
//     return (reverse_r(res));
// }




bigint::bigint(): storenum("0")
{};

bigint::bigint(const std::string& num): storenum(num){
    remove_zeros();
};

bigint::bigint(unsigned long long num)
{
    std::stringstream temp;
    temp << num;
    temp >> storenum;
};

bigint::bigint(const bigint& other): storenum(other.storenum)
{};

bigint& bigint::operator=(const bigint& other)
{
    if (storenum != other.storenum)
        storenum = other.storenum;
    return *this;
}

bigint::~bigint()
{}

void bigint::remove_zeros()
{
    size_t size = storenum.size();
    for (size_t i =0 ; i < size;i++)
    {
        if (storenum[0] == '0' && size > 1)
            storenum.erase(1, 0);
    }
}

std::string& add_str(const std::string& str1,const std::string& str2)
{
    int i = str1.size()-1,j=str2.size() -1, baqi=0, sum2n = 0;
    std::string res;
    while (i >= 0 || j >= 0 || baqi)
    {
        sum2n = (i>=0?str1[i--]-'0':0) + (j>=0?str2[j--]-'0':0) + baqi;
        res = (sum2n%10) + '0';
        baqi = (sum2n/10);
    }
    std::reverse(res.begin(), res.end());
    return res;
}

unsigned long long bigint::strToNum(const std::string& strnum) const
{
    unsigned long long res = 0;
    int size = strnum.size();
    char c;
    for (int i = 0; i < size; i++)
    {
        c = strnum[i];
        if (!isdigit(c))
            throw std::invalid_argument("ERROR");
        res = res * 10 +(c - '0');
    }
}



bigint bigint::operator+(const bigint& other) const
{
    return bigint(add_str(other.storenum, storenum));
}

bigint& bigint::operator+=(const bigint& other)
{
    storenum = add_str(storenum, other.storenum);
    return *this;
}

bigint& bigint::operator++()
{
    *this = *this + 1;
    return (*this);
}

bigint bigint::operator++(int)
{
    bigint prefix(*this);
    *this = *this + 1;
    return prefix;
}




bigint bigint::operator>>(const bigint& other) const
{
    size_t numtoshift = strToNum(other.storenum);
    if (numtoshift >= storenum.size())
        return bigint(0);
    return bigint(storenum.substr(0, (storenum.size()-numtoshift)));
}

bigint bigint::operator<<(const bigint& other) const
{
    size_t numtoshift = strToNum(other.storenum);
    if (numtoshift <= 0)
        return *this;
    return bigint(storenum + std::string(numtoshift, '0'));
}

bigint& bigint::operator>>=(const bigint& other)
{
    return (*this = *this >> other);
}

bigint& bigint::operator<<=(const bigint& other)
{
    return (*this = *this << other);
}


bool bigint::operator!=(const bigint& other) const
{
    return storenum != other.storenum;
}
bool bigint::operator==(const bigint& other) const 
{
    return (storenum == other.storenum);
}
bool bigint::operator<=(const bigint& other) const
{
    return (storenum <= other.storenum);
}
bool bigint::operator>=(const bigint& other) const
{
    return (storenum >= other.storenum);
}
bool bigint::operator>(const bigint& other) const
{
    if (other.storenum != storenum)
        return (storenum.size() > other.storenum.size());
    return storenum > other.storenum;
}
bool bigint::operator<(const bigint& other) const
{
    if (other.storenum != storenum)
        return (storenum.size() < other.storenum.size());
    return storenum < other.storenum;
}