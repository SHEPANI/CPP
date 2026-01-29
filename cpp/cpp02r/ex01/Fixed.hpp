
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
};

std::ostream& operator<<(std::ostream& os, const Fixed& fix);
