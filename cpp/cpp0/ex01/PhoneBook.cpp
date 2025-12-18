/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:31:04 by lhchiban          #+#    #+#             */
/*   Updated: 2025/12/11 23:16:13 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
    count = 0;
    one_field_info = 0;
    target_index = 0;
}
void PhoneBook::ADD()
{
    int index = count % 8;
    std::string input;
    for (int i = 0; i < 5; i++)
    {
        if (i == 0)
            std::cout << "Enter first name : ";
        if (i == 1)
            std::cout << "Enter last name : ";
        if (i == 2)
            std::cout << "Enter nickname : ";
        if (i == 3)
            std::cout << "Enter phone number : ";
        if (i == 4)
            std::cout << "Enter your darkest secret : ";
        std::getline(std::cin, input);
        if (check_enfofile())
            std::exit(0);
        PhoneBooks[index].set_info(input, i);
        if (PhoneBooks[index].get_info(i).empty()) { 
            std::cout << "Empty field\n";
            i -= 1;
        }
    }
    count++;
}

int check_enfofile()
{
    if (std::cin.eof())
    {
        std::cout << "\nEnd of file reached. Exiting program." << std::endl;
        return 1;
    }
    return 0;
}

void PhoneBook::SEARCH_BY_INDEX()
{
    std::string target_index_chars;
    std::cout << "Index of the entry to display : ";
    std::getline(std::cin, target_index_chars);
    if (check_enfofile())
        std::exit(0);
    target_index = std::atoi(target_index_chars.c_str());
    if (target_index < 1 || target_index > count || target_index_chars.length() > 1)
    {        
        std::cout << "Index is out of Range or wrong" << std::endl;
        one_field_info = 3;
        return ;       
    }
    else
        one_field_info = 5;
    SEARCH();
}

void PhoneBook::SEARCH()
{
    int j;
    int max_index;

    max_index = (count > 8) ? 8 : count;
    if (PhoneBooks[0].get_info(0).empty())
    {
        std::cout << "fields are empty" << std::endl;
        return;
    }
    j = 0;
    if (target_index > 0)
        j = target_index - 1;
    while (j < max_index)
    {
        if (one_field_info == 3)
        {
            std::cout << "|" << std::setw(10) << j + 1 << "|";
            for (int i = 0; i < one_field_info; i++)
            {
                if (PhoneBooks[j].get_info(i).length() <= 10)
                    std::cout << std::setw(10) << PhoneBooks[j].get_info(i) << "|";
                else
                    std::cout << PhoneBooks[j].get_info(i).substr(0, 9) << ".|";
            }
            std::cout << std::endl;
        }
        else
        {
            for (int i = 0; i < one_field_info; i++)
            {
                if (i == 0)
                    std::cout << "first name: " << PhoneBooks[j].get_info(i) << std::endl;
                if (i == 1)
                    std::cout << "last name: " << PhoneBooks[j].get_info(i) << std::endl;
                if (i == 2)
                    std::cout << "nickname: " << PhoneBooks[j].get_info(i) << std::endl;
                if (i == 3)
                    std::cout << "phone number: " << PhoneBooks[j].get_info(i) << std::endl;
                if (i == 4)
                    std::cout << "darkest secret: " << PhoneBooks[j].get_info(i) << std::endl;
            }
        }
        if (target_index > 0)
            break;
        j++;
    }
}