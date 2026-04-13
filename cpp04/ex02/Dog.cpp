/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 21:54:19 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/24 02:08:16 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
    this->type = "Dog";
    this->brain = new Brain();
    std::cout << "Dog constructor called\n";
}

Dog::Dog(const Dog& Other) : Animal(Other)
{
    this->brain = new Brain(*(Other.brain));
    std::cout << "Dog Copy constructor called\n";
}

Dog& Dog::operator=(const Dog& Other)
{
    if (this == &Other)
        return (*this);
    delete this->brain;
    this->brain = new Brain(*(Other.brain));
    this->type = Other.type;
    return (*this);
}

Dog::~Dog()
{
    delete this->brain;
    std::cout << "Dog Destructor called\n";
}

void Dog::makeSound() const
{
    std::cout << "woof\n"; 
}
