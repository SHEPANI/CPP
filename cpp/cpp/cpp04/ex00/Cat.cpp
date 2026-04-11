/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 21:53:59 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/24 05:28:22 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
{
    this->type = "Cat";
    std::cout << "Cat constructed\n";
}

Cat::Cat(const Cat& Other) : Animal(Other)
{
    std::cout << "Cat Copy constructor called\n";
}

Cat& Cat::operator=(const Cat& Other)
{
    this->type = Other.type;
    return (*this);
}

Cat::~Cat()
{
    std::cout << "Cat Destructed\n";
}

void Cat::makeSound() const
{
    std::cout << "Meow\n"; 
}
