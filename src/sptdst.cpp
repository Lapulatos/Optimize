#include "sptdst.h"
#include "inpoltn.h"

namespace Optr
{

namespace Alg
{
	catype SteepestDescentOptimizer::MAX_SEARCH_STEP = 20.0f;

	SteepestDescentOptimizer::SteepestDescentOptimizer(const Optr::MathFunction<catype, const Optr::VectorXc&>& func,
                                         		   const Optr::MathFunction<Optr::VectorXc, const Optr::VectorXc&>& dfunc,
                                         		   const catype epsilon, const Optr::VectorXc& initx) :
		m_Func_(func), m_DerivateFunc_(dfunc), m_Epsilon_(epsilon), 
		m_IterateX_(initx), m_Result_(Optr::VectorXc::Zero(initx.x())), m_SearchDirection_(Optr::VectorXc::Zero(initx.x()))
	{}

	void SteepestDescentOptimizer::Optimize()
	{
		Optr:FunctionHandler<catype, catype> lsfunc(std::bind(&SteepestDescentOptimizer::LinearSearchFunction, std::ref(*this), std::placeholders::_1));
		Optr::FunctionHandler<bool, catype> lsdfunc([](catype lambda) 
		{ 
			if((lambda >= -MAX_SEARCH_STEP) && (lambda <= MAX_SEARCH_STEP))
				return true;
			return false;
		});
		Optr::MathFunction<catype, catype> lsf(lsdfunc, lsfunc);
		Optr::Alg::QuadraticInterpolationOptimizer qioptr(lsf, m_Epsilon_, -MAX_SEARCH_STEP, MAX_SEARCH_STEP);

		double lambda = 0.0f;

#ifdef DEBUG
		int step = 0;
#endif	// DEBUG

		while(true)
		{
			m_SearchDirection_ = -1.0f * m_DerivateFunc_(m_IterateX_);

			if(m_SearchDirection_.norm() <= m_Epsilon_)
			{
				m_Result_ = m_IterateX_;
				return ;
			}
			else
			{	
#ifdef DEBUG
				std::cout << "linear search for lambda: step: " << step << " start ==============================" << std::endl;		
#endif	// DEBUG
				qioptr.Optimize();
				lambda = qioptr.GetOptimizeResult();

#ifdef DEBUG
				std::cout << "---------------------------------------------------------" << std::endl;
				std::cout << "iterate point: (" << m_IterateX_.transpose() << ")'" << std::endl;
				std::cout << "search direction: (" << m_SearchDirection_.transpose() << ")'" << std::endl;
				std::cout << "lambda: " << lambda << std::endl;
				std::cout << "linear search for lambda step: " << step++ << " stop ==============================" << std::endl;
#endif	// DEBUG
	
				m_IterateX_ += lambda*m_SearchDirection_;
			}
		}
	}

	Optr::VectorXc SteepestDescentOptimizer::GetOptimizeResult() const
	{
		return m_Result_;
	}

	catype SteepestDescentOptimizer::GetEpsilon() const
	{
		return m_Epsilon_;
	}

	void SteepestDescentOptimizer::SetPrimitiveAndDerivateFunction(const Optr::MathFunction<catype, const Optr::VectorXc&>& func,
                                                     		       const Optr::MathFunction<Optr::VectorXc, const Optr::VectorXc&>& dfunc)
	{
		m_Func_ = func;
		m_DerivateFunc_ = dfunc;
	}

	void SteepestDescentOptimizer::SetInitX(const Optr::VectorXc& initx)
	{
		m_IterateX_ = initx;
	}

	catype SteepestDescentOptimizer::LinearSearchFunction(catype lambda)
	{
		Optr::VectorXc t = m_IterateX_ + lambda*m_SearchDirection_;
		return m_Func_(t);
	}

}	// namespace Alg

}	// namespace Optr
