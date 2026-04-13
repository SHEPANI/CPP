/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 21:53:59 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/24 02:08:09 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
{
    this->type = "Cat";
    this->brain = new Brain();
    std::cout << "Cat constructed\n";
}

Cat::Cat(const Cat& Other) : Animal(Other)
{
    this->brain = new Brain(*(Other.brain));
    std::cout << "Cat Copy constructor called\n";
}

Cat& Cat::operator=(const Cat& Other)
{
    if (this == &Other)
        return (*this);
    delete this->brain;
    this->brain = new Brain(*(Other.brain));
    this->type = Other.type;
    return (*this);
}

Cat::~Cat()
{
    delete this->brain;
    std::cout << "Cat Destructed\n";
}

void Cat::makeSound() const
{
    std::cout << "Meow\n";
}
