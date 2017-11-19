#ifndef SPTDST_INCLUDED
#define SPTDST_INCLUDED

#include "utils.h"
#include "optimizer.h"
#include "mathdef.h"

namespace Optr
{

namespace Alg
{

	class SteepestDescentOptimizer : public Alg::Optimizer
	{
	public:
		SteepestDescentOptimizer(const Optr::MathFunction<catype, const Optr::VectorXc&>& func, 
					 const Optr::MathFunction<Optr::VectorXc, const Optr::VectorXc&>& dfunc, 
					 const catype epsilon, const Optr::VectorXc& initx);

		void Optimize();
		
		Optr::VectorXc GetOptimizeResult() const;
		catype GetEpsilon() const;
		void SetPrimitiveAndDerivateFunction(const Optr::MathFunction<catype, const Optr::VectorXc&>& func,
						     const Optr::MathFunction<Optr::VectorXc, const Optr::VectorXc&>& dfunc);
		void SetInitX(const Optr::VectorXc& initx);

	private:
		catype LinearSearchFunction(catype lambda);

	public:
		static catype MAX_SEARCH_STEP;		// 最大线性搜索长度
	private:
		Optr::MathFunction<catype, const Optr::VectorXc&> m_Func_;			// 待优化函数 
		Optr::MathFunction<Optr::VectorXc, const Optr::VectorXc&> m_DerivateFunc_;	// 待优化函数的导函数
		catype m_Epsilon_;			// 近似解求解精度

		Optr::VectorXc m_Result_;		// 近似解
		Optr::VectorXc m_IterateX_;		// 迭代点[在待优化函数的定义域内，且会在迭代时改变]
		Optr::VectorXc m_SearchDirection_;	// 搜索方向[在待优化函数导函数的定义域内，且会在迭代时改变]
	};	// class SteepestDescentOptimizer	

}	// namespace Alg

}	// namespace Optr

#endif	// SPTDST_INCLUDED
