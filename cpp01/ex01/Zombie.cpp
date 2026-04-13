/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:17:46 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/09 20:17:59 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Zombie.hpp"

Zombie::Zombie()
{
}

void Zombie::setName(std::string name)
{
    _name = name;
}


Zombie::~Zombie()
{
    std::cout << _name << " is destroyed." << std::endl;
}

void Zombie::announce(void)
{
    std::cout << _name << " : " << "BraiiiiiiinnnzzzZ..." << std::endl;
}