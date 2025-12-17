/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cantact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 23:08:34 by lhchiban          #+#    #+#             */
/*   Updated: 2025/12/11 23:14:45 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Contact_HPP
# define   Contact_HPP

#include <iostream>

class Contact{
    private:
        std::string Contact_info[5];
    public:
        void set_info(std::string input_Contact_info, int count);
        std::string get_info(int field_info);
};

#endif