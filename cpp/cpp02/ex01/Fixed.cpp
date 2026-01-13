

#include "Fixed.hpp"

Fixed::Fixed() : _fixed(0)
{
    std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& fixOther)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &fixOther)
        this->_fixed = fixOther.getRawBits();
    return (*this);
}

Fixed::Fixed(const Fixed& fixOther)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = fixOther;
}

int Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return (this->_fixed);
}

void Fixed::setRawBits(int const raw)
{
    this->_fixed = raw;
}

float Fixed::toFloat(void) const
{
    return ((float)this->_fixed / (1 << this->_fraction));
}

int Fixed::toInt(void) const
{
    return (this->_fixed >> this->_fraction);
}
std::ostream& operator<<(std::ostream& os, const Fixed& fix)
{
    os << fix.toFloat();
    return (os);
}

Fixed::Fixed(int const raw)
{
    std::cout << "Int constructor called" << std::endl;
    this->_fixed = raw << this->_fraction;
}

Fixed::Fixed(float const raw)
{
    std::cout << "Float constructor called" << std::endl;
    this->_fixed = roundf(raw*(1 << this->_fraction));
}