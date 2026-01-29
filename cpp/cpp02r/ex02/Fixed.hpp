
#include <iostream>
#include <cmath>

class Fixed
{
    private:
        int _fixed;
        static const int _fraction = 8;
    public:
        Fixed();
        Fixed(const Fixed& fixOther);
        Fixed(int const raw);
        Fixed(float const raw);
        Fixed& operator=(const Fixed& fixOther);
        ~Fixed();
        int getRawBits(void) const;
        void setRawBits(int const raw);
        float toFloat(void) const;
        int toInt(void) const;
    
        static const Fixed& max(const Fixed& a,const Fixed& b);
        static Fixed& min(Fixed& a, Fixed& b);
        static const Fixed& min(const Fixed& a,const Fixed& b);
        static Fixed& max(Fixed& a, Fixed& b);

        bool operator>(const Fixed& fixOther) const;
        bool operator<(const Fixed& fixOther) const;
        bool operator!=(const Fixed& fixOther) const;
        bool operator==(const Fixed& fixOther) const;
        bool operator>=(const Fixed& fixOther) const;
        bool operator<=(const Fixed& fixOther) const;

        Fixed operator+(const Fixed& fixOther) const;
        Fixed operator-(const Fixed& fixOther) const;
        Fixed operator/(const Fixed& fixOther) const;
        Fixed operator*(const Fixed& fixOther) const;
    
        Fixed operator++(int);
        Fixed& operator++();
        Fixed operator--(int);
        Fixed& operator--();
};

std::ostream& operator<<(std::ostream& os, const Fixed& fix);