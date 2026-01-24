/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 21:53:59 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/24 01:24:32 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat()
{
    this->type = "WrongCat";
    std::cout << "WrongCat constructed\n";
}

WrongCat::WrongCat(const WrongCat& Other) : WrongAnimal(Other)
{
    std::cout << "WrongCat Copy constructor called\n";
}

WrongCat& WrongCat::operator=(const WrongCat& Other)
{
    if (this == &Other)
        return (*this);
    this->type = Other.type;
    return (*this);
}

WrongCat::~WrongCat()
{
    std::cout << "WrongCat Destructed\n";
}

void WrongCat::makeSound() const
{
    std::cout << "Meow\n"; 
}
