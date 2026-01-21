/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:18:18 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/21 22:28:18 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"



#include "ClapTrap.hpp"
#include <iostream>

int main() {
    ClapTrap a("jds;");
    // std::cout << "\n\033[33m=== HARD TEST: CLAPTRAP ===\033[0m\n\n";

    // ClapTrap alpha("Alpha");
    // ClapTrap beta("Beta");

    // std::cout << "\n-- Test 1: Normal attacks --\n";
    // alpha.attack("Beta");
    // beta.takeDamage(5);
    // beta.beRepaired(3);

    // std::cout << "\n-- Test 2: Multiple attacks until energy depletes --\n";
    // for (int i = 0; i < 15; i++) {
    //     alpha.attack("Beta");
    // }

    // std::cout << "\n-- Test 3: Damage beyond HP --\n";
    // beta.takeDamage(100); // Should drop HP to 0
    // beta.attack("Alpha");  // Should not attack if no energy or dead
    // beta.beRepaired(10);   // Repair after death (check logic)

    // std::cout << "\n-- Test 4: Self repair and multiple small attacks --\n";
    // ClapTrap gamma("Gamma");
    // gamma.beRepaired(5);
    // for (int i = 0; i < 3; i++) {
    //     gamma.attack("Alpha");
    //     gamma.takeDamage(2);
    // }

    // std::cout << "\n-- Test 5: Copy constructor & assignment --\n";
    // ClapTrap copyGamma(gamma);
    // ClapTrap assignTest;
    // assignTest = alpha;
    // copyGamma.attack("Beta");
    // assignTest.attack("Gamma");

    // std::cout << "\n-- Test 6: Edge cases --\n";
    // ClapTrap zeroEnergy("Zero");
    // zeroEnergy.takeDamage(0); // 0 damage
    // zeroEnergy.beRepaired(0); // 0 repair
    // zeroEnergy.attack("Alpha"); // Normal attack

    // std::cout << "\n\033[33m=== END OF HARD TEST ===\033[0m\n";
    return 0;
}