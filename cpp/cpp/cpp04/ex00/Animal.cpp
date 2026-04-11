/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 05:40:32 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/24 05:28:16 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal()
{
    std::cout << "Animal  Constracted\n";
}

Animal::Animal(const Animal& Other)
{
    std::cout << "Animal copy constractor  called\n";
    this->type = Other.type;
}

Animal& Animal::operator=(const Animal& Other)
{
    this->type = Other.type;
    return (*this);
}

Animal::~Animal()
{
    std::cout << "Animal destructed\n";
}

void Animal::makeSound() const
{
    std::cout << "Animal don't make sound\n";
}

std::string Animal::getType() const
{
    return (this->type);
}