/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 22:41:14 by kingstephan       #+#    #+#             */
/*   Updated: 2026/04/01 14:38:30 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

//lit le fichier CSV.
BitcoinExchange::BitcoinExchange(const std::string &CSV_file)
{
	std::ifstream file(CSV_file.c_str());
	if (!file.is_open())
		throw BitcoinExchange::FileNotOpen();
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		size_t pos = line.find(',');
		if (pos == std::string::npos)
			continue;
		std::string key = line.substr(0, pos);
		std::string value_string = line.substr(pos + 1, line.size());
		float value = strtof(value_string.c_str(), NULL);
		bitcoin_data.insert(std::make_pair(key, value));
	}
};

// copy constructeur.
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	this->bitcoin_data = other.bitcoin_data;
};

// copy asignement.
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this == &other)
		return (*this);
	this->bitcoin_data = other.bitcoin_data;
	return (*this);
};

// destructeur
BitcoinExchange::~BitcoinExchange(){};

// lit le fichier texte.
void BitcoinExchange::Exchange(std::string input_file)
{
	std::ifstream file(input_file.c_str());
	if (!file.is_open())
		throw BitcoinExchange::FileNotOpen();
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		size_t pos = line.find('|');
		if (pos == std::string::npos)
		{
			std::cerr << "Error : Bad input => " << line << std::endl;
			continue;
		}
		std::string date = line.substr(0, pos);
		try
		{
			date = validate_date(date);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			continue;
		}
		float value = 0;
		try
		{
			value = validate_value(line.substr(pos + 1, line.size() - pos + 1));
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			continue;
		}
		std::map<std::string, float>::iterator it = this->bitcoin_data.lower_bound(date);
		if (it == this->bitcoin_data.end())
			it--;
		else if (it == this->bitcoin_data.begin() && it->first != date)
		{
			std::cerr << "Error : Bad input => " << date << " date in the past!" << std::endl;
			continue;
		}
		else if (it->first != date)
			it--;
		std::cout << date << " => " << value << " = " << it->second * value << std::endl;
	}
};

// retirer les espace blanc
std::string no_white_space(std::string line)
{
	size_t pos_start = line.find_first_not_of(" \t");
	if (pos_start == std::string::npos)
		return ("");
	size_t pos_end = line.find_last_not_of(" \t");
	return (line.substr(pos_start, pos_end - pos_start + 1));
};

// parsing de la date
bool parse_date(std::string date)
{
	if (date.size() != 10)
		return (false);
	for(int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!isdigit(date.at(i)))
			return (false);
	}
	if (date.at(4) != '-' || date.at(7) != '-')
		return (false);
	int month = std::atoi(date.substr(5, 2).c_str());
	if (month < 1 || month > 12)
		return (false);
	int day = std::atoi(date.substr(8, 2).c_str());
	if (day < 1 || day > 31)
		return (false);
	return (true);
};

// valider une date selon le format YYYY-MM-DD
std::string validate_date(std::string date)
{
	std::string new_date = no_white_space(date);
	if (!parse_date(new_date))
	{
		std::cerr << "invalid date => ";
		throw BitcoinExchange::BadInput();
	}
	return (new_date);
};

// valide une valeur de 0 et 1000
float validate_value(std::string value)
{
	value = no_white_space(value);
	char *end = NULL;
	float new_value = std::strtof(value.c_str(), &end);
	if (*end != '\0')
		throw BitcoinExchange::BadInput();
	if (new_value < 0)
		throw BitcoinExchange::NotAPostiveNumber();
	if (new_value > 1000)
		throw BitcoinExchange::NumberTooLarge();
	return (new_value);
};
