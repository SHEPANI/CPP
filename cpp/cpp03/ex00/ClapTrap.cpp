/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:17:59 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/21 23:14:35 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : name("Default"), hitPoints(10), energyPoints(10), attackDamage(0)
{
    std::cout << "ClapTrap " << this->name << " constructed!" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : name(name), hitPoints(10), energyPoints(10), attackDamage(0)
{
    std::cout << "ClapTrap " << this->name << " constructed by parameterized constructor" << std::endl;
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap " << this->name << " destructed!" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& Other)
{
    *this = Other;
    std::cout << "ClapTrap " << this->name << " copy constructor called" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& Other)
{
    this->energyPoints = Other.energyPoints;
    this->name = Other.name;
    this->hitPoints = Other.hitPoints;
    this->attackDamage = Other.attackDamage;
    return (*this);
}

void ClapTrap::attack(const std::string& target)
{
    if (this->energyPoints == 0 || this->hitPoints == 0)
    {
        std::cout << "ClapTrap " << this->name << " has no energy or hit points left to attack." << std::endl;
        return;
    }
    this->energyPoints--;
    std::cout << "ClapTrap " << this->name << " attacks " << target
              << ", causing " << this->attackDamage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (amount >= hitPoints)
    {
        hitPoints = 0;
        std::cout << "ClapTrap " << this->name << " has been destroyed!" << std::endl;
    }
    else
    {
        hitPoints -= amount;
        std::cout << "ClapTrap " << this->name << " takes " << amount
                  << " points of damage! Remaining hit points: " << hitPoints << std::endl;
    }
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->energyPoints == 0 || this->hitPoints == 0)
    {
        std::cout << "ClapTrap " << this->name << " has no energy or hit points left to repair." << std::endl;
        return;
    }
    this->energyPoints--;
    hitPoints += amount;
    std::cout << "ClapTrap " << this->name << " repairs itself for " << amount
              << " points! New hit points: " << hitPoints << std::endl;
}
