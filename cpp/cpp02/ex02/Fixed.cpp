/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 00:50:59 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/16 05:47:16 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() : _fixed(0)
{
}


Fixed::Fixed(const Fixed& fixOther)
{
    this->_fixed = fixOther.getRawBits();
}

Fixed& Fixed::operator=(const Fixed& fixOther)
{
    // if (this != &fixOther)
        this->_fixed = fixOther.getRawBits();
    return (*this);
}

Fixed::Fixed(int const raw)
{
    this->_fixed = raw << this->_fraction;
}

Fixed::Fixed(float const raw)
{
    this->_fixed = roundf(raw * (1 << _fraction)); //  roundf()
}

Fixed::~Fixed()
{
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
    return (static_cast<float>(_fixed) / (1 << _fraction));
}

int Fixed::toInt(void) const
{
    return (this->_fixed >> _fraction);
}

std::ostream& operator<<(std::ostream& os, const Fixed& fix)
{
    os << fix.toFloat();
    return os;
}


bool Fixed::operator>(const Fixed& fixOther) const
{
    return (this->_fixed > fixOther._fixed);
}
bool Fixed::operator<(const Fixed& fixOther) const
{
    return (this->_fixed < fixOther._fixed);
}
bool Fixed::operator!=(const Fixed& fixOther) const
{
    return (this->_fixed != fixOther._fixed);
}
bool Fixed::operator==(const Fixed& fixOther) const
{
    return (this->_fixed == fixOther._fixed);
}
bool Fixed::operator>=(const Fixed& fixOther) const
{
    return (this->_fixed >= fixOther._fixed);
}
bool Fixed::operator<=(const Fixed& fixOther) const
{
    return (this->_fixed <= fixOther._fixed);
}


Fixed Fixed::operator+(const Fixed& fixOther) const
{
    return (Fixed(toFloat() + fixOther.toFloat()));
}

Fixed Fixed::operator-(const Fixed& fixOther) const
{
    return (Fixed(toFloat() - fixOther.toFloat()));
}

// Fixed Fixed::operator/(const Fixed& fixOther) const
// {
    
// }
// Fixed Fixed::operator*(const Fixed& fixOther) const
// {
    
// }


Fixed Fixed::operator++() // way void
{
    this->_fixed += 1;
    return *this;
}

Fixed Fixed::operator++(int) // way int
{
    Fixed tmp(*this);
    this->_fixed += 1;
    return tmp;
}

Fixed Fixed::operator--()
{
    this->_fixed -= 1;
    return *this;    
}
Fixed Fixed::operator--(int)
{
    Fixed tmp(*this);
    this->_fixed -= 1;
    return tmp;
}


const Fixed& Fixed::max(const Fixed& a,const Fixed& b)
{
    if (a < b)
        return b;
    return a;
}

Fixed& Fixed::max(Fixed& a, Fixed& b)
{
    if (a < b)
        return b;
    return a;
}

Fixed& Fixed::min(Fixed& a, Fixed& b)
{
    if (a < b)
        return a;
    return b;
}

const Fixed& Fixed::min(const Fixed& a,const Fixed& b)
{
    if (a < b)
        return a;
    return b;
}
