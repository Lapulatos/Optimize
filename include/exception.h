#ifndef EXCEPTION_INCLUDED
#define EXCEPTION_INCLUDED

#include "utils.h"
#include "funcs.h"

namespace Optr
{
	
	class Exception : public std::runtime_error
	{
	public:

		Exception(const char* file, const unsigned int line); 
		Exception(const char* file, const unsigned line, const std::string& expMesg);
		Exception(const Exception& exp);

		virtual const char* what() const noexcept;
	protected:
		std::string m_File_;
		std::string m_Line_;
	};	// class Exception

}	// namespace Optr

#endif	// EXCEPTION_INCLUDED
