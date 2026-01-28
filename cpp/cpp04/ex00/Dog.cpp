/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 21:54:19 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/24 05:28:28 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
    this->type = "Dog";
    std::cout << "Dog constructor called\n";
}

Dog::Dog(const Dog& Other) : Animal(Other)
{
    std::cout << "Dog Copy constructor called\n";
}

Dog& Dog::operator=(const Dog& Other)
{
    this->type = Other.type;
    return (*this);
}

Dog::~Dog()
{
    std::cout << "Dog Destructor called\n";
}

void Dog::makeSound() const
{
    std::cout << "woof\n"; 
}
