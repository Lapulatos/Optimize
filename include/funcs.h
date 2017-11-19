#ifndef FUNCS_INCLUDED
#define FUNCS_INCLUDED

namespace Optr
{
	template <typename A, typename B>
	B Convert(const A& a)
	{
		std::stringstream ss;
		B result;

		ss << a;
		ss >> result;

		return result;
	}

}	// namespace Optr

#endif	// FUNCS_INCLUDED
