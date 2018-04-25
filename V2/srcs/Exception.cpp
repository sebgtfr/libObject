/**
* \file				Exception.cpp
* \author			Sébastien Le Maire
* \version			1.0
* \date				23 Février 2018
*/

#include "Objects/Exception.hpp"

char const * const Objects::Exception::MSGS_ERROR[Objects::Exception::NO_ERROR] =
{
	"bad allocation",
	"Trying to read on null pointer",
	"index given is out of range"
};
