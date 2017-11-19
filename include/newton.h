#ifndef NEWTON_INCLUDED
#define NEWTON_INCLUDED

#include "utils.h"
#include "optimizer.h"
#include "mathdef.h"

namespace Optr
{

namespace Alg
{

	class NewtonMethodOptimizer : Alg::Optimizer
	{
	public:
		NewtonMethodOptimizer(const Optr::MathFunction<catype, const Optr::VectorXc&>& func,
				      const Optr::MathFunction<Optr::VectorXc, const Optr::VectorXc&>& dfunc,
				      const Optr::MathFunction<Optr::MatrixXc, const Optr::VectorXc&>& ddfunc,
				      const catype epsilon, const Optr::VectorXc& initxi);	

		void Optimize();

		Optr::VectorXc GetOptimizeResult() const;
		catype GetEpsilon() const;
		Optr::VectorXc GetInitialIterateX() const;
		void SetPrimitiveAndDerivateFunctions(const Optr::MathFunction<catype, const Optr::VectorXc&>& func,
						      const Optr::MathFunction<Optr::VectorXc, const Optr::VectorXc&>& dfunc,
						      const Optr::MathFunction<Optr::MatrixXc, const Optr::VectorXc&>& ddfunc);
		void SetEpsilon(const catype epsilon);
		void SetInitialIterateX(const Optr::VectorXc& initx);

	private:
		catype LinearSearchFunction(catype lambda);
		
	public:
		static catype MAX_SEARCH_STEP;
	private:
		Optr::MathFunction<catype, const Optr::VectorXc&> m_Func_;			// 待优化函数
		Optr::MathFunction<Optr::VectorXc, const Optr::VectorXc&> m_DerivateFunc_;	// 待优化函数的导函数
		Optr::MathFunction<Optr::MatrixXc, const Optr::VectorXc&> m_SecondDetFunc_;	// 待优化函数的二阶导函数
		catype m_Epsilon_;			// 近似解求解精度
		
		Optr::VectorXc m_Result_;		// 近似解
		Optr::VectorXc m_IterateX_;		// 迭代点[在待优化函数的定义域内，且会在迭代时改变]
		Optr::VectorXc m_SearchDirection_;	// 搜索方向[在待优化函数对应导函数的定义域内，且会在迭代时改变]
	};	// class NewtonMethodOptimizer

}	// namespace Alg

}	// namespace Optr

#endif	// NEWTON_INCLUDED
