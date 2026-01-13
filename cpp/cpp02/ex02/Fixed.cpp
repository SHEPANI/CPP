

#include "Fixed.hpp"

Fixed::Fixed() : _fixed(0)
{
    // std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed()
{
    // std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed& fixOther)
{
    // std::cout << "Copy constructor called" << std::endl;
    *this = fixOther;
}

Fixed::Fixed(int const raw)
{
    // std::cout << "Int constructor called" << std::endl;
    this->_fixed = raw << this->_fraction;
}

Fixed::Fixed(float const raw)
{
    // std::cout << "Float constructor called" << std::endl;
    this->_fixed = roundf(raw*(1 << this->_fraction));
}

Fixed& Fixed::operator=(const Fixed& fixOther)
{
    // std::cout << "Copy assignment operator called" << std::endl;
    if (this != &fixOther)
        this->_fixed = fixOther.getRawBits();
    return (*this);
}



int Fixed::getRawBits(void) const
{
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

Fixed& Fixed::min(Fixed& a, Fixed& b)
{
    return (a < b ? a : b);
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
    return (a < b ? a : b);
}

Fixed& Fixed::max(Fixed& a, Fixed& b)
{
    return (a > b ? a : b);
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
    return (a > b ? a : b);
}


Fixed Fixed::operator + (const Fixed& fixOther) const
{
    return (Fixed(this->toFloat() + fixOther.toFloat()));
}

Fixed Fixed::operator - (const Fixed& fixOther) const
{
    return (Fixed(this->toFloat() - fixOther.toFloat()));
}

Fixed Fixed::operator * (const Fixed& fixOther) const
{
    return (Fixed(this->toFloat() * fixOther.toFloat()));
}

Fixed Fixed::operator / (const Fixed& fixOther) const
{
    return (Fixed(this->toFloat() / fixOther.toFloat()));
}

Fixed& Fixed::operator ++ (void)
{
    this->_fixed++;
    return (*this);
}

Fixed Fixed::operator ++ (int)
{
    Fixed temp = *this;
    this->_fixed++;
    return (temp);
}

Fixed& Fixed::operator -- (void)
{
    this->_fixed--;
    return (*this);
}

Fixed Fixed::operator -- (int)
{
    Fixed temp = *this;
    this->_fixed--;
    return (temp);
}

bool Fixed::operator > (const Fixed& fixOther) const
{
    return (this->_fixed > fixOther._fixed);
}

bool Fixed::operator < (const Fixed& fixOther) const
{
    return (this->_fixed < fixOther._fixed);
}

bool Fixed::operator >= (const Fixed& fixOther) const
{
    return (this->_fixed >= fixOther._fixed);
}

bool Fixed::operator <= (const Fixed& fixOther) const
{
    return (this->_fixed <= fixOther._fixed);
}

bool Fixed::operator == (const Fixed& fixOther) const
{
    return (this->_fixed == fixOther._fixed);
}

bool Fixed::operator != (const Fixed& fixOther) const
{
    return (this->_fixed != fixOther._fixed);
}

std::ostream& operator<<(std::ostream& os, const Fixed& fix)
{
    os << fix.toFloat();
    return (os);
}