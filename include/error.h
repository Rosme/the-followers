/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to
Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
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
    
    virtual ~Error() throw(){}
    
	virtual const char* what() const throw();

private:
	std::string m_what;
};

#endif