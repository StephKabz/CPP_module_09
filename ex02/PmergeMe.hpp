/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:38:05 by kingstephan       #+#    #+#             */
/*   Updated: 2026/04/13 17:36:42 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <algorithm>
#include <exception>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <vector>
#include <utility>
#include <deque>
#include <sys/time.h>

class PmergeMe
{
	private : 
	public :
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe& operator=(const PmergeMe &other);
		~PmergeMe();
		void sortVector(std::vector<int> &vec);
		void sortDeque(std::deque<int> &deq);
		int check_arg(std::string argv);
		class InvalidArg : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "Error : Invalid Argument!";
			};
		};
};

bool compare_pairs(std::pair<int,int> a, std::pair<int,int> b);

#endif