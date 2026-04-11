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
    Bureaucrat a(2, "ahmed");
    std::cout << a << "\n";

    Bureaucrat b;
    b = a;
    std::cout << b << "\n";

    Bureaucrat c(a);
    std::cout << c << "\n";

    try
    {
        std::cout << a << "\n";
        a.inc_burGrade();
        std::cout << a << "\n";
        a.inc_burGrade();
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what();
    }

    try
    {
        std::cout << b << "\n";
        for (int i = 0; i < 150; i++)
            b.dec_burGrade();
        std::cout << b << "\n";
        
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what();
    }

    try
    {
        std::cout << c << "\n";
        c.inc_burGrade();
        std::cout << c << "\n";
        c.inc_burGrade();
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what();
    }

    try
    {
        std::cout << c << "\n";
        c.inc_burGrade();
        std::cout << c << "\n";
        c.inc_burGrade();
    }
    catch (int i)
    {
        std::cout << "Custom Error Caught: " << i;
    }
    return 0;
}