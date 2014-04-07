/*
Copyright (C) - Jean-Sébastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <string>
#include <list>

/**
 * Class derived from std::exception to manage the game exception in its on way
 **/
class Error : public std::exception {
public:
	Error(std::string const& what = "") throw();

	virtual const char* what() const throw();

private:
	std::string m_what;
};

#endif