/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:14:44 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/16 16:13:47 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main() {
    Zombie *newZombie1;
    newZombie1 = newZombie("Shepani");
    newZombie1->announce();
    randomChump("Shepani1");
    delete newZombie1;
    return 0;
}