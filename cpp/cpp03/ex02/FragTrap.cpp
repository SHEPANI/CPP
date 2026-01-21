/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:02:45 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/21 18:41:50 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"


FragTrap::FragTrap() : ClapTrap()
{
    std::cout << "FragTrap " << this->name << " constructed" << std::endl;
    this->name = "default";
    this->hitPoints = 100;
    this->energyPoints = 100;
    this->attackDamage = 30;
}

FragTrap::FragTrap(const FragTrap& Other)
{
    std::cout << "FragTrap " << this->name << " copy contructer called" << std::endl;
    *this = Other;
}


FragTrap::FragTrap(std::string Name)
{
    this->name = Name;
    this->hitPoints = 100;
    this->energyPoints = 100;
    this->attackDamage = 30;
    std::cout << "FragTrap " << this->name << " constructed by parameterized contructer" << std::endl;
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap " << this->name << " destructed" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& Other)
{
    this->energyPoints = Other.energyPoints;
    this->name = Other.name;
    this->hitPoints = Other.hitPoints;
    this->attackDamage = Other.attackDamage;
    return (*this);
}

void FragTrap::highFivesGuys()
{
    std::cout << "FragTrap " << this->name << " raises its hand: \"High fives, guys! Give me some love!\" 🙏" << std::endl;
}