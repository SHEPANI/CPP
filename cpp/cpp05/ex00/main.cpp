/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:41:27 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/29 13:00:49 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main()
{
    try
    {
        Bureaucrat b(1, "SPI");
        std::cout << b.getGrade() << "\n";
        b.inc_burGrade( 150);
        std::cout << b.getGrade() << "\n";
        b.dec_burGrade(150); 
        std::cout << b.getGrade() << "\n";
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what();
    }
    return 0;
}