/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:22:47 by kingstephan       #+#    #+#             */
/*   Updated: 2026/04/13 17:20:34 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){};

PmergeMe::PmergeMe(const PmergeMe &other)
{
	(void)other;
};

PmergeMe& PmergeMe::operator=(const PmergeMe &other)
{
	(void)other;
	return (*this);
};

PmergeMe::~PmergeMe()
{};

void PmergeMe::sortVector(std::vector<int> &vec)
{
	if (vec.size() <= 1)
		return;
	std::vector<std::pair<int, int> > paires;
	for (size_t i = 0; i + 1 < vec.size(); i += 2)
	{
		int grand = std::max(vec[i], vec[i + 1]);
		int petit = std::min(vec[i], vec[i + 1]);
		paires.push_back(std::make_pair(grand, petit));
	}
	int last = -1;
	bool has_last = false;
	if (vec.size() % 2 != 0)
	{
		last = vec[vec.size() - 1];
		has_last = true;
	}
	std::sort(paires.begin(), paires.end(), compare_pairs);
	std::vector <int> grands;
	for (size_t j = 0; j < paires.size(); j++)
		grands.push_back(paires.at(j).first);
	sortVector(grands);
	std::vector <int> petits;
	for (size_t i = 0; i < paires.size(); i++)
		petits.push_back(paires.at(i).second);
	std::vector <int> chaines;
	chaines = grands;
	chaines.insert(chaines.begin(), petits[0]);
	std::vector <int> jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	while (jacobsthal.back() < (int)petits.size())
	{
		int size = (int)jacobsthal.size();
		int next = jacobsthal[size - 1] + 2 * jacobsthal[size - 2];
		jacobsthal.push_back(next);
	};
	int prev = 1;
	for (size_t i = 1; i < jacobsthal.size(); i++)
	{
		int current = std::min((size_t)jacobsthal[i], petits.size() - 1);
		for (int idx = current; idx >= prev ; idx--)
		{
			if (idx < (int)petits.size())
			{
				std::vector<int>::iterator pos = std::lower_bound(chaines.begin(), chaines.end(), petits[idx]);
				chaines.insert(pos, petits[idx]);
			}
		}
		prev = jacobsthal[i] + 1;
		if (prev > (int)petits.size())
			break;
	}
	if (has_last)
	{
		std::vector<int>::iterator pos = std::lower_bound(chaines.begin(), chaines.end(), last);
		chaines.insert(pos, last);
	}
	vec = chaines;
};

void PmergeMe::sortDeque(std::deque<int> &deq)
{
	if (deq.size() <= 1)
		return;
	std::deque<std::pair<int, int> > paires;
	for (size_t i = 0; i + 1 < deq.size(); i += 2)
	{
		int grand = std::max(deq[i], deq[i + 1]);
		int petit = std::min(deq[i], deq[i + 1]);
		paires.push_back(std::make_pair(grand, petit));
	}
	int last = -1;
	bool has_last = false;
	if (deq.size() % 2 != 0)
	{
		last = deq[deq.size() - 1];
		has_last = true;
	}
	std::sort(paires.begin(), paires.end(), compare_pairs);
	std::deque <int> grands;
	for (size_t j = 0; j < paires.size(); j++)
		grands.push_back(paires.at(j).first);
	sortDeque(grands);
	std::deque <int> petits;
	for (size_t i = 0; i < paires.size(); i++)
		petits.push_back(paires.at(i).second);
	std::deque <int> chaines;
	chaines = grands;
	chaines.insert(chaines.begin(), petits[0]);
	std::deque <int> jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	while (jacobsthal.back() < (int)petits.size())
	{
		int size = (int)jacobsthal.size();
		int next = jacobsthal[size - 1] + 2 * jacobsthal[size - 2];
		jacobsthal.push_back(next);
	};
	int prev = 1;
	for (size_t i = 1; i < jacobsthal.size(); i++)
	{
		int current = std::min((size_t)jacobsthal[i], petits.size() - 1);
		for (int idx = current; idx >= prev ; idx--)
		{
			if (idx < (int)petits.size())
			{
				std::deque<int>::iterator pos = std::lower_bound(chaines.begin(), chaines.end(), petits[idx]);
				chaines.insert(pos, petits[idx]);
			}
		}
		prev = jacobsthal[i] + 1;
		if (prev > (int)petits.size())
			break;
	}
	if (has_last)
	{
		std::deque<int>::iterator pos = std::lower_bound(chaines.begin(), chaines.end(), last);
		chaines.insert(pos, last);
	}
	deq = chaines;
};

int PmergeMe::check_arg(std::string argv)
{
	for (size_t i = 0; i < argv.size(); i++)
	{
		if (!isdigit(argv[i]))
			throw PmergeMe::InvalidArg();
	}
	char *end = NULL;
	long value = strtol(argv.c_str(), &end, 10);
	if (*end != '\0' || value < 0 || value > INT_MAX)
		throw PmergeMe::InvalidArg();
	return (static_cast<int>(value));
};

bool compare_pairs(std::pair<int,int> a, std::pair<int,int> b)
{
	return (a.first < b.first);
};
