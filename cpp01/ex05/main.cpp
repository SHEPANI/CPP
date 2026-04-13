/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:18:39 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/15 15:31:31 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main()
{
    Harl harl; 
    Harl harl1(harl);
    
    harl.complain("INFO");
    std::cout << "\n";
    harl.complain("WARNING");
    std::cout << "\n";
    harl.complain("ERROR"); 
    std::cout << "\n";
    harl.complain("DEBUG");
    return 0;
}