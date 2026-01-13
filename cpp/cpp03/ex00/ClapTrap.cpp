#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap() 
    : name("Default"), hitPoints(10), energyPoints(10), attackDamage(0)
{
    std::cout << "ClapTrap " << this->name << " constructed!" << std::endl;
}

ClapTrap::ClapTrap(std::string name) 
    : name(name), hitPoints(10), energyPoints(10), attackDamage(0)
{
    std::cout << "ClapTrap " << this->name << " constructed!" << std::endl;
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap " << this->name << " destructed!" << std::endl;
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
