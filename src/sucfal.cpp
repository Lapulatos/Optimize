#include "sucfal.h"

namespace Optr
{

namespace Alg
{

	SuccessFailureOptimizer::SuccessFailureOptimizer(const Optr::MathFunction<catype, catype>& func, const catype epsilon, const catype steplen, const catype initx) :
		m_Func_(func), m_Epsilon_(epsilon), m_Result_((catype)0.0f), m_InitStepLen_(steplen), m_InitX_(initx)
	{}

	void SuccessFailureOptimizer::Optimize()
	{
		catype h = m_InitStepLen_, x = m_InitX_;
		catype phi1 = m_Func_(x), phi2 = 0.0f;

#ifdef DEBUG
		int step = 0;
#endif	// DEBUG
		while(true)
		{
			phi2 = m_Func_(x + h);
#ifdef DEBUG
                        std::cout << "step: " << step++ << std::endl
                                  << "step(h): " << h << std::endl
                                  << "x: " << x << ", (x + h): " << (x + h) << std::endl
                                  << "phi1: " << phi1 << ", phi2: " << phi2 << std::endl;
#endif  // DEBUG
			if(phi2 < phi1)
			{
				x += h;
				phi1 = phi2;
				h *= 2;
			}
			else
			{
				if(std::fabs(h) <= m_Epsilon_)
				{
					m_Result_ = x;
					return ;
				}
				else
				{
					h = -h / 4.0f;
				}
			}
		}
	}

	catype SuccessFailureOptimizer::GetOptimizeResult() const
	{
		return m_Result_;
	}

	catype SuccessFailureOptimizer::GetEpsilon() const
	{
		return m_Epsilon_;
	}

	catype SuccessFailureOptimizer::GetInitialStepLength() const
	{
		return m_InitStepLen_;
	}

	catype SuccessFailureOptimizer::GetInitialX() const
	{
		return m_InitX_;
	}

	void SuccessFailureOptimizer::SetOptimizeMathFunction(const Optr::MathFunction<catype, catype>& func)
	{
		m_Func_ = func;
	}

	void SuccessFailureOptimizer::SetEpsilon(const catype epsilon)
	{
		m_Epsilon_ = epsilon;
	}

	void SuccessFailureOptimizer::SetInitialStepLength(const catype steplen)
	{
		m_InitStepLen_ = steplen;
	}

	void SuccessFailureOptimizer::SetInitialX(const catype initx)
	{
		m_InitX_ = initx;
	}

}	// namespace Alg

}	// namespace Optr
