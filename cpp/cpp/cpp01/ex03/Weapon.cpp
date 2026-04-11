/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:17:14 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/11 18:13:34 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string Newtype) 
{
    this->setType(Newtype);
}
Weapon::~Weapon()
{
}

void Weapon::setType(std::string Newtype)
{
    type = Newtype;
}

const std::string& Weapon::getType()
{
    return (type);
}