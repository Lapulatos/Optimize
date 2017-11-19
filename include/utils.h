#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED


// for configurating this program
#include "config.h"

// system header included
#include <iostream>
#include <memory.h>
#include <cmath>
#include <exception>
#include <string>
#include <functional>
#include <algorithm>

// third-party header included
#include <Eigen/Eigen>



// computational accuracy definition
#ifdef COMPUTATIONAL_ACC_DOUBLE
	typedef double 	catype;
#else
 #ifdef COMPUTATIONAL_ACC_FLOAT
	typedef float 	catype;
 #else
  #error "no computational accuracy specified."
 #endif
#endif



// main namespace 
namespace Optr
{

	template <typename R, typename... Args>
	class FunctionHandler
	{
	public:
		FunctionHandler(const std::function<R(Args...)>& fhandler) :
			m_FuncHandler_(fhandler)
		{}
		
		FunctionHandler(const FunctionHandler<R, Args...>& cfhandler) :
			m_FuncHandler_(cfhandler.m_FuncHandler_)
		{}

		FunctionHandler& operator= (const FunctionHandler<R, Args...>& cfhandler)
		{
			if(&cfhandler != this)
				m_FuncHandler_ = cfhandler.m_FuncHandler_;
			return (*this);
		}
		
		R operator() (Args... args) const
		{
			return m_FuncHandler_(std::forward<Args>(args)...);
		}
				
	protected:
		std::function<R(Args...)> m_FuncHandler_;
	};	// template class FunctionHandler

	
	
	// basic caculation type definition
	typedef Eigen::Matrix<catype, Eigen::Dynamic, 1> VectorXc;
	typedef Eigen::Matrix<catype, Eigen::Dynamic, Eigen::Dynamic> MatrixXc;	

}	// namespace Optr

#endif	// UTILS_INCLUDED


