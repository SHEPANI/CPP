/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:12:40 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/14 16:42:14 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP


#include <string>
#include <iostream>

class Zombie {
private:
    std::string _name;
public:
    void announce(void);
    void setName(std::string name);
    Zombie();
    ~Zombie();
};

Zombie* zombieHorde(int N, std::string name);

#endif