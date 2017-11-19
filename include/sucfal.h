#ifndef SUCFAL_INCLUDED
#define SUCFAL_INCLUDED

#include "utils.h"
#include "optimizer.h"
#include "mathdef.h"

namespace Optr
{

namespace Alg
{

	class SuccessFailureOptimizer : public Alg::Optimizer
	{
	public:
		SuccessFailureOptimizer(const Optr::MathFunction<catype, catype>& func, const catype epsilon, const catype steplen, const catype initx);
		
		void Optimize();

		catype GetOptimizeResult() const;
		catype GetEpsilon() const;
		catype GetInitialStepLength() const;
		catype GetInitialX() const;		
		void SetOptimizeMathFunction(const Optr::MathFunction<catype, catype>& func);	
		void SetEpsilon(const catype epsilon);
		void SetInitialStepLength(const catype steplen);
		void SetInitialX(const catype initx);
	
	private:
		Optr::MathFunction<catype, catype> m_Func_;	// 待优化函数
		catype m_Epsilon_;		// 近似解求解精度
		catype m_Result_;		// 近似解
	
		catype m_InitStepLen_;		// 初始搜索步长
		catype m_InitX_;		// 初始搜索点[在待优化函数定义域内]
	};	// class SuccessFailureOptimizer

}	// namespace Alg

}	// namespace Optr

#endif	// SUCFAL_INCLUDED
