#include <string>
#include <iostream>
#include <sstream>
#include <exception>


class bigint
{
    private :
        std::string store;
        void remove_zeroes();
        unsigned long long too_innt(const std::string &str) const;
        std::string soomme(const std::string &a, const std::string &b) const;
    public :
        bigint();
        bigint(unsigned long long nbr);
        bigint(const std::string &str);
        bigint(const bigint &str);
        bigint &operator=(const bigint &obj);
        ~bigint();

        bigint operator+(const bigint &obj) const;
        bigint &operator+=(const bigint &obj);
        bigint operator++(int);
        bigint &operator++();

        bigint operator<<(const bigint &obj) const;
        bigint &operator<<=(const bigint &obj);
        bigint operator>>(const bigint &obj) const;
        bigint &operator>>=(const bigint &obj);

        bool operator<(const bigint &obj) const;
        bool operator<=(const bigint &obj) const;
        bool operator>(const bigint &obj) const;
        bool operator>=(const bigint &obj) const;

        bool operator==(const bigint &obj) const;
        bool operator!=(const bigint &obj) const;

        friend  std::ostream &operator<<(std::ostream &out, const bigint &obj);
        
};