/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:23:59 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/21 21:24:04 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "ClapTrap.hpp"
#include <iostream>

int main()
{
    std::cout << "\n\033[33m=== CLAPTRAP TEST ===\033[0m\n";
    ClapTrap clapTrap("Clappy");
    clapTrap.attack("Enemy");
    clapTrap.takeDamage(5);
    clapTrap.beRepaired(3);

    std::cout << "\n\033[33m=== SCAVTRAP TEST ===\033[0m\n";
    ScavTrap scavTrap("Scavvy");
    scavTrap.attack("Target");
    scavTrap.takeDamage(20);
    scavTrap.beRepaired(10);
    scavTrap.guardGate();

    std::cout << "\n\033[33m=== FRAGTRAP TEST ===\033[0m\n";
    FragTrap fragTrap1("Fraggy");
    FragTrap fragTrap2("Trapster");

    fragTrap1.attack("Target1");
    fragTrap1.takeDamage(30);
    fragTrap1.beRepaired(20);
    fragTrap1.highFivesGuys();

    fragTrap2.attack("Target2");
    fragTrap2.takeDamage(50);
    fragTrap2.beRepaired(40);
    fragTrap2.highFivesGuys();

    std::cout << "\n\033[33m=== CONSTRUCTION/DESTRUCTION CHAINING ===\033[0m\n";
    std::cout << "Creating scope with ScavTrap:\n";
    {
        ScavTrap tempScav("TempScav");
        tempScav.guardGate();
    }
    std::cout << "ScavTrap scope ended.\n\n";

    std::cout << "Creating scope with FragTrap:\n";
    {
        FragTrap tempFrag("TempFrag");
        tempFrag.highFivesGuys();
    }
    std::cout << "FragTrap scope ended.\n";

    return 0;
}