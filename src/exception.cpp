#include "exception.h"

namespace Optr
{
	
	Exception::Exception(const char* file, const unsigned line) :
		std::runtime_error("Exception: something wrong happened in file: " + std::string(file) + ", at line: " + Optr::Convert<const unsigned int, std::string>(line) + ".")
	{}

	Exception::Exception(const char* file, const unsigned line, const std::string& expMesg) :
		std::runtime_error("Exception: " + expMesg + ". file: " + std::string(file) + ", at line: " + Optr::Convert<const unsigned int, std::string>(line) + ".")
	{}

        Exception::Exception(const Exception& exp) :
        	std::runtime_error(std::string(exp.what()))
        {}

        const char* Exception::what() const noexcept
        {
        	return std::runtime_error::what();
        }

}	// class Optr
