/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:16:56 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/16 17:19:53 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(const std::string& Newname) : weapon(NULL)
{
    name = Newname;
}

HumanB::~HumanB ()
{
}

void HumanB::setWeapon(Weapon &Neweapon)
{
    weapon = &Neweapon;
}


void HumanB::attack()
{
    if (weapon)
        std::cout << name << " attacks with their " << weapon->getType() << std::endl;
}