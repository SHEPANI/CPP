#include <iostream>
#include <sstream>

class bigint
{
    std::string store;
    void remove_zeros();
    std::string add_string(const std::string &a, const std::string &b) const;
    unsigned long long from_string(const std::string &s) const;
    public :
        bigint();
        bigint(const bigint &o);
        bigint(const std::string &s);
        bigint(unsigned long long n);
        
        bigint &operator=(const bigint &o);



        bigint operator+(const bigint &o) const;
        bigint &operator+=(const bigint &o);
    
        bigint &operator++();
        bigint operator++(int);

        
        
        bigint operator<<(const bigint &o) const;
        bigint &operator<<=(const bigint &o);
        bigint &operator>>=(const bigint &o);
        bigint  operator>>(const bigint &o) const;


        bool operator<(const bigint &o)const;
        bool operator<=(const bigint &o)const;

        bool operator>(const bigint &o)const;
        bool operator>=(const bigint &o)const;
        
        bool operator==(const bigint &o)const;
        bool operator!=(const bigint &o)const;
        
        friend std::ostream &operator<<(std::ostream &s, const bigint &o);
};