/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:18:18 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/22 04:41:38 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>

int main() {
    std::cout << "\n\033[33m=== HARD TEST: CLAPTRAP ===\033[0m\n\n";

    ClapTrap alpha("Alpha");
    ClapTrap beta("Beta");

    std::cout << "\n-- Test 1: Normal attacks --\n";
    alpha.attack("Beta");
    beta.takeDamage(5);
    beta.beRepaired(3);

    std::cout << "\n-- Test 2: Multiple attacks until energy depletes --\n";
    for (int i = 0; i < 15; i++) {
        alpha.attack("Beta");
    }

    std::cout << "\n-- Test 3: Damage beyond HP --\n";
    beta.takeDamage(100);
    beta.attack("Alpha"); 
    beta.beRepaired(10);  

    std::cout << "\n-- Test 4: Self repair and multiple small attacks --\n";
    ClapTrap gamma("Gamma");
    gamma.beRepaired(5);
    for (int i = 0; i < 3; i++) {
        gamma.attack("Alpha");
        gamma.takeDamage(2);
    }

    std::cout << "\n-- Test 5: Copy constructor & assignment --\n";
    ClapTrap copyGamma(gamma);
    ClapTrap assignTest;
    assignTest = alpha;
    copyGamma.attack("Beta");
    assignTest.attack("Gamma");

    std::cout << "\n-- Test 6: Edge cases --\n";
    ClapTrap zeroEnergy("Zero");
    zeroEnergy.takeDamage(0);
    zeroEnergy.beRepaired(0);
    zeroEnergy.attack("Alpha");

    std::cout << "\n\033[33m=== END OF HARD TEST ===\033[0m\n";
    return 0;
}