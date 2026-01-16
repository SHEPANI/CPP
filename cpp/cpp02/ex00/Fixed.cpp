/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 00:50:36 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/16 02:02:43 by lhchiban         ###   ########.fr       */
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
    std::cout << "Copy assignment operator called" << std::endl;
    // if (this != &fixOther) // way this protection
        this->_fixed = fixOther.getRawBits();
    return (*this);
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