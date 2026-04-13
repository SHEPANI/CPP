/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:41:27 by lhchiban          #+#    #+#             */
/*   Updated: 2026/04/12 22:50:09 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
// #include "ShrubberyCreationForm.hpp"

int main()
{
    try
    {
        Intern a;
        AForm* form;
        form = a.makeForm("Presidential pardon for", "HOME");
        // std::cout << a;
        // ShrubberyCreationForm B1("Home");
        // a.signForm(B1);
        // B1.execute(a);
        delete form;
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what();
    }

    return 0;
}