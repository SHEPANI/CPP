/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:17:50 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/15 17:53:22 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name)
{
    if (N < 0)
        return NULL;
    Zombie* Zombies;
    Zombies = new Zombie[N];
    for (int i = 0; i < N; i++)
        Zombies[i].setName(name);
    return (Zombies);
}