#include "my.hpp"


void bigint::remove_zeroes()
{
    while (store.size() > 1 && store[0] == '0')
    {
        store.erase(0, 1);
    }
    

}

unsigned long long bigint::too_innt(const std::string &str) const
{
    unsigned long long r = 0;
    size_t i = 0;
    while (i < str.size())
    {
        if(!isdigit(str[i]))
            throw std::invalid_argument("err");
        r = r * 10 + (str[i] - '0');
        i++;
    }
    return r;
}

std::string revece_it(std::string r)
{
    char tmp;
    int begin = 0;
    int end  = r.size() - 1;
    while (begin < end)
    {
        tmp = r[begin];
        r[begin] = r[end];
        r[end] = tmp;
        end--;
        begin++;
    }
    return r;
}

std::string bigint::soomme(const std::string &a, const std::string &b) const
{
    int i = a.size() - 1;
    int j = b.size() - 1;
    int s= 0;
    int c = 0;
    std::string r;
    while (i >= 0 || j >= 0 || c)
    {
        s = c + (i >= 0? (a[i--] - '0') : 0) + (j >= 0? (b[j--] - '0') : 0);
        r += (s % 10) + '0';
        c = s / 10;
    }

    r = revece_it(r);
    return r;
}

bigint::bigint() : store("0")
{}


bigint::bigint(unsigned long long nbr)
{
    std::stringstream obj;
    obj << nbr;
    obj >> store;
}
bigint::bigint(const std::string &str) : store(str)
{
    remove_zeroes();
}

bigint::bigint(const bigint &str)
{
    store = str.store;
}


bigint &bigint::operator=(const bigint &obj)
{
    if(this != &obj)
    {
        store = obj.store;
    }
    return *this;
}

bigint::~bigint()
{}

bigint bigint::operator+(const bigint &obj) const
{
    return(bigint(soomme(store , obj.store)));
}

bigint &bigint::operator+=(const bigint &obj)
{
    *this = *this + obj;
    return *this;
}

bigint &bigint::operator++()
{
    *this = *this + 1;
    return *this;
}

bigint bigint::operator++(int)
{
    bigint tmp(*this);
    ++(*this);
    return tmp;
}

bigint bigint::operator<<(const bigint &obj) const
{
    int shift = too_innt(obj.store);
    if(shift <= 0)
        return *this;
    return (bigint(store + std::string(shift, '0')));
}

bigint &bigint::operator<<=(const bigint &obj)
{
    *this = *this << obj;
    return *this;
}

bigint bigint::operator>>(const bigint &obj) const
{
    int shift = too_innt(obj.store);
    if(shift >= (int) store.size())
        return bigint("0");
    return (store.substr(0, (store.size() - shift)));
}

bigint &bigint::operator>>=(const bigint &obj)
{
    *this  = *this >> obj;
    return *this;
}

bool bigint::operator<(const bigint &obj) const
{
    if(store.size() != obj.store.size())
        return store.size() < obj.store.size();
    return store < obj.store;
}

bool bigint::operator>(const bigint &obj) const
{
    return (obj < *this);
}

bool bigint::operator<=(const bigint &obj) const
{
        return !(*this > obj);
}

bool bigint::operator>=(const bigint &obj) const
{
    return !(*this < obj);
}


bool bigint::operator==(const bigint &obj) const
{
    if(store == obj.store)
        return true;
    return false;
}

bool bigint::operator!=(const bigint &obj) const
{
    return !( *this == obj);
}

std::ostream &operator<<(std::ostream &out, const bigint &obj)
{

    out << obj.store;
    return out;    
}
