#include "dfp.h"
#include "inpoltn.h"

namespace Optr
{

namespace Alg
{

	DFPOptimizer::DFPOptimizer(const Optr::MathFunction<catype, const Optr::VectorXc&>& func,
                                   const Optr::MathFunction<Optr::VectorXc, const Optr::VectorXc&>& dfunc,
                                   const catype epsilon, const Optr::VectorXc& initx) :
		m_Func_(func), m_DerivateFunc_(dfunc), m_Epsilon_(epsilon), 
		m_IterateX_(initx), m_Result_(Optr::VectorXc::Zero(initx.x())), m_SearchDirection_(Optr::VectorXc::Zero(initx.x()))
	{}

	void DFPOptimizer::Optimize()
	{
		Optr::FunctionHandler<catype, catype> lsfunc(std::bind(&DFPOptimizer::LinearSearchFunction, std::ref(*this), std::placeholders::_1));
		Optr::FunctionHandler<bool, catype> lsdfunc([](catype lambda) 
		{
			if((lambda >= 0) && (lambda <= 1.0f))
				return true;
			return false;
		});
		Optr::MathFunction<catype, catype> lsf(lsdfunc, lsfunc);
		Optr:Alg::QuadraticInterpolationOptimizer qioptr(lsf, m_Epsilon_, 0.0f, 1.0f);

		double lambda = 0.0f;
#ifdef DEBUG
                int step = 0;
#endif  // DEBUG
		
		Optr::VectorXc gk, sk, gkp1, xkp1;
		Optr::VectorXc dxk, dgk, rk;
		Optr::MatrixXc Hk = Optr::MatrixXc::Identity(m_IterateX_.rows(), m_IterateX_.rows());
		
		while(true)
		{
			gk = m_DerivateFunc_(m_IterateX_);
			
			if(gk.norm() <= m_Epsilon_)
			{
				m_Result_ = m_IterateX_;
				return ;
			}
			else
			{
#ifdef DEBUG
                                std::cout << "linear search for lambda: step: " << step << " start ==============================" << std::endl;
#endif  // DEBUG
				m_SearchDirection_ = -1.0f*Hk*gk;

				qioptr.Optimize();
				lambda = qioptr.GetOptimizeResult();

#ifdef DEBUG
                                std::cout << "---------------------------------------------------------" << std::endl;
                                std::cout << "xk: (" << m_IterateX_.transpose() << ")'" << std::endl;
                                std::cout << "search direction: (" << m_SearchDirection_.transpose() << ")'" << std::endl;
                                std::cout << "lambda: " << lambda << std::endl;
#endif  // DEBUG

				xkp1 = m_IterateX_ + lambda*m_SearchDirection_;
				gkp1 = m_DerivateFunc_(xkp1);

				if(gkp1.norm() <= m_Epsilon_)
				{
					m_Result_ = xkp1;
					return ;
				}
				else
				{
					dxk = xkp1 - m_IterateX_;
					dgk = gkp1 - gk;
					rk = Hk*dgk;
					Hk += (dxk*dxk.transpose()) / (dxk.transpose()*dgk) - (rk*rk.transpose())/(dgk.transpose()*rk);

					m_IterateX_ = xkp1;
				}
#ifdef DEBUG
				std::cout << "vector xkp1: (" << xkp1.transpose() << ")'" << std::endl;
				std::cout << "vector gk: (" << gk.transpose() << ")'" << std::endl;
				std::cout << "vector gkp1: (" << gkp1.transpose() << ")'" << std::endl;
				std::cout << "vector rk: (" << rk.transpose() << ")'" << std::endl;
				std::cout << "matrix Hk: " << std::endl << Hk << std::endl;
                                std::cout << "linear search for lambda step: " << step++ << " stop ==============================" << std::endl;
#endif	// DEBUG
			}
		}
	}

	Optr::VectorXc DFPOptimizer::GetOptimizeResult() const
	{
		return m_Result_;
	}

	catype DFPOptimizer::GetEpsilon() const
	{
		return m_Epsilon_;
	}

	Optr::VectorXc DFPOptimizer::GetInitialIterateX() const
	{
		return m_IterateX_;
	}

	void DFPOptimizer::SetPrimitiveAndDerivateFunctions(const Optr::MathFunction<catype, const Optr::VectorXc&>& func,
                                                      const Optr::MathFunction<Optr::VectorXc, const Optr::VectorXc&>& dfunc)
	{
		m_Func_ = func;
		m_DerivateFunc_ = dfunc;
	}

	void DFPOptimizer::SetEpsilon(const catype epsilon)
	{
		m_Epsilon_ = epsilon;
	}

	void DFPOptimizer::SetInitialIterateX(const Optr::VectorXc& initx)
	{
		m_IterateX_ = initx;
	}

	catype DFPOptimizer::LinearSearchFunction(catype lambda)
	{
		Optr::VectorXc t = m_IterateX_ + lambda*m_SearchDirection_;
		return m_Func_(t);
	}

}	// namespace Alg

}	// namespace Optr
