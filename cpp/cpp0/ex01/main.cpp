/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 23:08:48 by lhchiban          #+#    #+#             */
/*   Updated: 2025/12/11 23:23:05 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PhoneBook.hpp"


int main(int ac, char *av[])
{
    PhoneBook phonebook;
    std::string input;
    (void)ac,(void)av;
    while (true)
    {
        std::cout << "You have to set 3 type of input ADD | SEARCH | EXIT\nEnter one type : ";
        std::getline(std::cin, input);
        if (input == "EXIT")
            return(EXIT_SUCCESS);
        else if (input == "ADD")
            phonebook.ADD();
        else if (input == "SEARCH")
        {
            phonebook.one_field_info = 3;
            phonebook.SEARCH();
            phonebook.SEARCH_BY_INDEX();
            phonebook.target_index = 0;
        }
    }
    return 0;
}