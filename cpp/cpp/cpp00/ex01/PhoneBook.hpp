/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 23:08:58 by lhchiban          #+#    #+#             */
/*   Updated: 2025/12/11 23:18:22 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"
#include <iomanip>
#include <cstdlib>
int check_enfofile();
int has_nonprintable(const std::string& str);

class PhoneBook{
    public:
        PhoneBook();
        void ADD();
        void SEARCH();
        void SEARCH_BY_INDEX();
        int  one_field_info;
        int  target_index;
    private:
        Contact PhoneBooks[8];
        int  count;
};

#endif