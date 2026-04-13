/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:42:54 by kingstephan       #+#    #+#             */
/*   Updated: 2026/04/13 18:02:12 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cerr << "Missing Arguments!" << std::endl;
		return (0);
	}
    PmergeMe pm;
    std::vector<int> vec;
	std::deque<int> deq;
	try
	{
		for (int i = 1; i < argc; i++)
		{
			vec.push_back(pm.check_arg(argv[i]));
			deq.push_back(pm.check_arg(argv[i]));
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
	struct timeval start, end;
    std::cout << "Before : ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
    gettimeofday(&start, NULL);
    pm.sortVector(vec);
    gettimeofday(&end, NULL);
	double elapsed = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
    std::cout << "After :  ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
	std::cout << "Time to process a range of " << vec.size() 
          << " elements with std::vector : " 
          << elapsed << " us" << std::endl;
	gettimeofday(&start, NULL);
    pm.sortDeque(deq);
    gettimeofday(&end, NULL);
	elapsed = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
	std::cout << "Time to process a range of " << deq.size() 
          << " elements with std::deque  : " 
          << elapsed << " us" << std::endl;
    return 0;
};

