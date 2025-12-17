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
        PhoneBooks[index].set_info(input, i);
        if (PhoneBooks[index].get_info(i).empty()) { 
            std::cout << " Emty field\n";
            i -= 1;
        }
    }
    count++;
    if (count > 8)
        count = 8;
}

void PhoneBook::SEARCH_BY_INDEX()
{
    std::string target_index_chars;
    std::cout << "Index of the entry to display : ";
    std::getline(std::cin, target_index_chars);
    target_index = std::atoi(target_index_chars.c_str());
    if (target_index < 1 || target_index > count)
    {        
        std::cout << "Index Is Out Of Range Or Wrong" << std::endl;
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
    if (PhoneBooks[0].get_info(0).empty())
    {
        std::cout << " fields are emty\n";
        return;
    }
    j = 0;
    if (target_index > 0)
        j = target_index - 1;
    while (j < count)
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