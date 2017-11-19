#ifndef MATHDEF_INCLUDED
#define MATHDEF_INCLUDED

#include "utils.h"
#include "exception.h"

namespace Optr
{

	template <typename... Args>
	class DefinitionDomain
	{
	public:
		DefinitionDomain(const Optr::FunctionHandler<bool, Args...>& dfhandler, bool flag = false) :
			m_DefFunc_(dfhandler)
		{}

		DefinitionDomain(const DefinitionDomain<Args...>& dfunc) :
			m_DefFunc_(dfunc.m_DefFunc_)
		{}

		DefinitionDomain& operator= (const DefinitionDomain<Args...>& dfunc)
		{
			if(&dfunc != this)
				m_DefFunc_ = dfunc.m_DefFunc_;
			return (*this);
		}
		
		bool operator() (Args... args) const
		{
			return m_DefFunc_(args...);
		}

	protected:
		Optr::FunctionHandler<bool, Args...> m_DefFunc_;	// expression of the definition domain
	};	// template class DefinitionDomain

	template <typename R, typename... Args>
	class MathFunction
	{
	public:
		MathFunction(const FunctionHandler<bool, Args...>& dfhandler, const FunctionHandler<R, Args...>& fhandler) :
			m_Function_(fhandler), m_DefFunction_(dfhandler)
		{}

		MathFunction(const MathFunction<R, Args...>& func) :
			m_Function_(func.m_Function_), m_DefFunction_(func.m_DefFunction_)
		{}
	
		MathFunction& operator= (const MathFunction<R, Args...>& func)
		{
			if(&func != this)
			{
				m_Function_ = func.m_Function_;
				m_DefFunction_ = func.m_DefFunction_;
			}
			
			return (*this);
		}

		R operator() (Args... args)
		{
			if(m_DefFunction_(args...))
				return m_Function_(args...);
			else
				throw Optr::Exception(__FILE__, __LINE__, "parameter is out of the definition domain");
		}
		
	protected:
		Optr::FunctionHandler<R, Args...> m_Function_;
		Optr::DefinitionDomain<Args...> m_DefFunction_;
	};	// template class MathFunction

}	// namespace Optr

#endif	// MATHDEF_INCLUDED
