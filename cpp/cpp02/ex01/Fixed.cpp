/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 00:50:59 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/16 05:44:59 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() : _fixed(0)
{
    std::cout << "Default constructor called" << std::endl;
}


Fixed::Fixed(const Fixed& fixOther)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = fixOther;
}

Fixed& Fixed::operator=(const Fixed& fixOther)
{
    
    if (this != &fixOther) 
        this->_fixed = fixOther._fixed;
    std::cout << "Copy assignment operator called" << std::endl;
    return (*this);
}

Fixed::Fixed(int const raw)
{
    std::cout << "Int constructor called" << std::endl;
    this->_fixed = raw << this->_fraction;
}

Fixed::Fixed(float const raw)
{
    std::cout << "Float constructor called" << std::endl;
    this->_fixed = roundf(raw * (1 << _fraction)); //  roundf()
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
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
