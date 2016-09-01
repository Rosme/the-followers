/*
Copyright (C) - Jean-S�bastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "error.h"

#include <fstream>
#include <sstream>

//Error Exception
Error::Error(std::string const& what) throw()
	: m_what(what) {
}

const char* Error::what() const throw() {
	return m_what.c_str();
}