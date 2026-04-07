/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 22:41:42 by kingstephan       #+#    #+#             */
/*   Updated: 2026/04/01 13:17:45 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <algorithm>
#include <exception>
#include <fstream>
#include <string>
#include <map>

class BitcoinExchange {
	private :
		std::map<std::string, float> bitcoin_data; //date and value per date.
		BitcoinExchange(); //default constucteur inutile sans fichier CSV.
	public :
		BitcoinExchange(const std::string &CSV_file); //lit le fichier CSV et remplie la map.
		BitcoinExchange(const BitcoinExchange &other); // copy constructeur.
		BitcoinExchange& operator=(const BitcoinExchange &other); // copy asignement.
		~BitcoinExchange(); // destructeur
		void Exchange(std::string input_file); // lit le fichier texte.
		class FileNotOpen : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "Error : Could not open file!";
			};
		};
		class NotAPostiveNumber : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "Error : not a positive number!";
			};
		};
		class NumberTooLarge : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "Error : too large a number!";
			};
		};
		class BadInput : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "Error : Bad input!";
			};
		};
};

std::string no_white_space(std::string line); // retirer les espace blanc
bool parse_date(std::string date); // parsing de la date
std::string validate_date(std::string date); // valider une date selon le format YYYY-MM-DD
float validate_value(std::string value); // valide une valeur de 0 et 1000 inclus

#endif