/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:19:20 by kingstephan       #+#    #+#             */
/*   Updated: 2026/04/01 18:57:54 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <algorithm>
#include <exception>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>

class RPN{
	private :
		std::stack<int> rpn_satck;
	public :
		RPN();
		RPN(const RPN &other);
		RPN& operator=(const RPN &other);
		~RPN();
		void calculate(std::string arg);
		class Error : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "Error!";
			};
		};
};

bool ft_is_operator(std::string str);


#endif