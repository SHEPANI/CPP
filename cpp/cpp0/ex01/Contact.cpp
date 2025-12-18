/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:46:02 by lhchiban          #+#    #+#             */
/*   Updated: 2025/12/11 23:14:45 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

std::string Contact::get_info(int field_info)
{
    return Contact_info[field_info];
} 

void Contact::set_info(std::string input_Contact_info, int count)
{
    Contact_info[count] = input_Contact_info;
}
