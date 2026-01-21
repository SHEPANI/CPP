/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:18:37 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/21 23:14:05 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include <string>
#include <iostream>

class ClapTrap
{
    protected:
        std::string name;
        unsigned int hitPoints ;
        unsigned int energyPoints ;
        unsigned int attackDamage;
    public:
        ClapTrap(std::string name);
        ClapTrap(const ClapTrap& Other);
        ClapTrap& operator=(const ClapTrap& other);
        ~ClapTrap();
        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
};





#pragma endregion