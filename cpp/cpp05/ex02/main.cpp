/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:41:27 by lhchiban          #+#    #+#             */
/*   Updated: 2026/03/04 13:14:16 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main()
{
    try
    {
        Bureaucrat a;
        a.inc_burGrade(1);
        // Bureaucrat b(5, "SPI");
        // std::cout << b.getGrade() << "\n";
        // // b.inc_burGrade( 150);
        // std::cout << b.getGrade() << "\n";
        // // b.dec_burGrade(150); 
        // std::cout << b << "\n";
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what();
    }
    std::cout << "her\n";
    return 0;
}