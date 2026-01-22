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
#include <iostream>

int main()
{
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

    return 0;
}