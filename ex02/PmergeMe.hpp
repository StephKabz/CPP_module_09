/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stkabang <stkabang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:38:05 by kingstephan       #+#    #+#             */
/*   Updated: 2026/04/14 12:17:38 by stkabang         ###   ########.fr       */
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