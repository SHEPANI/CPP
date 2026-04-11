/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:15:58 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/16 17:06:45 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Zombie.hpp"

int main() {
    int N = 0;
    Zombie* newZombie_horde = zombieHorde( N , "spi");
    for (int i = 0;i < N;i++)
        newZombie_horde[i].announce();
    delete[] newZombie_horde;
    return 0;
}