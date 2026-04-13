/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:25:06 by kingstephan       #+#    #+#             */
/*   Updated: 2026/04/13 14:58:01 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(){};

RPN::RPN(const RPN &other)
{
	this->rpn_satck = other.rpn_satck;
};

RPN& RPN::operator=(const RPN &other)
{
	if (this == &other)
		return (*this);
	this->rpn_satck = other.rpn_satck;
	return (*this);
};

RPN::~RPN(){};

void RPN::calculate(std::string arg)
{
	std::istringstream ss(arg);
	std::string token;
	while (ss >> token)
	{
		if (token.size() == 1 && isdigit(token[0]))
			rpn_satck.push(atoi(token.c_str()));
		else if (ft_is_operator(token) && rpn_satck.size() >= 2)
		{
			int b = this->rpn_satck.top();
			rpn_satck.pop();
			int a = this->rpn_satck.top();
			rpn_satck.pop();
			if (token == "*")
				this->rpn_satck.push(a * b);	
			else if (token == "-")
				this->rpn_satck.push(a - b);
			else if (token == "/")
			{
				if (b == 0)
					throw RPN::Error();
				this->rpn_satck.push(a / b);
			}
			else if (token == "+")
				this->rpn_satck.push(a + b);
		}
		else
			throw RPN::Error();
	}
	if (this->rpn_satck.size() != 1)
		throw RPN::Error();
	else
		std::cout << this->rpn_satck.top() << std::endl;
};

bool ft_is_operator(std::string str)
{
	if (str[0] != '*' && str[0] != '-' && str[0] != '+' && str[0] != '/')
		return (false);
	return (true);
}
