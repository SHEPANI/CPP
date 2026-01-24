/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 05:40:32 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/24 02:02:56 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
    std::cout << "WrongAnimal  Constracted\n";
}

WrongAnimal::WrongAnimal(const WrongAnimal& Other)
{
    std::cout << "WrongAnimal copy constractor  called\n";
    this->type = Other.type;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& Other)
{
    if (this == &Other) // slove self assignment and Dynamic memory 
                        //allocation are delete for the same obj (this and other)
        return (*this);
    this->type = Other.type;
    return (*this);
}

WrongAnimal::~WrongAnimal()
{
    std::cout << "WrongAnimal destructed\n";
}

void WrongAnimal::makeSound() const
{
    std::cout << "WrongAnimal don't make sound\n";
}

std::string WrongAnimal::getType() const
{
    return (this->type);
}