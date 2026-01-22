/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:02:45 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/22 05:14:37 by lhchiban         ###   ########.fr       */
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

FragTrap::FragTrap(const FragTrap& Other) : ClapTrap(Other)
{
    std::cout << "FragTrap " << this->name << " copy constructor called" << std::endl;
}


FragTrap::FragTrap(std::string Name) : ClapTrap(Name)
{
    this->name = Name;
    this->hitPoints = 100;
    this->energyPoints = 100;
    this->attackDamage = 30;
    std::cout << "FragTrap " << this->name 
    << " constructed by parameterized constructor" << std::endl;
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap " << this->name << " destructed" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& Other)
{
    if (this != &Other)
        ClapTrap::operator=(Other);
    return (*this);
}

void FragTrap::highFivesGuys()
{
    std::cout << "FragTrap " << this->name 
    << " raises its hand: \"High fives, guys! Give me some love!\"" << std::endl;
}