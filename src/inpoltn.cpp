#include "inpoltn.h"

namespace Optr
{

namespace Alg
{

	QuadraticInterpolationOptimizer::QuadraticInterpolationOptimizer(const Optr::MathFunction<catype, catype>& func, const catype epsilon, const catype startp, const catype endp) :
		m_Func_(func), m_Epsilon_(epsilon), m_Result_((catype)0.0f), m_LeftOptStart_(startp), m_RghtOptEnd_(endp)
	{}

	void QuadraticInterpolationOptimizer::Optimize()
	{
                catype a = m_LeftOptStart_, b = m_RghtOptEnd_;

                catype x1 = a, x2 = (a + b) / 2.0f, x3 = b;
                catype c2 = 0.0f, c3 = 0.0f, a2 = 0.0f;
                catype f1 = 0.0f, f2 = 0.0f, f3 = 0.0f, x_ = x2, fx_ = m_Func_(x2);

#ifdef DEBUG
                int step = 0;
#endif

                while(true)
                {
                        if(std::fabs(b - a) <= m_Epsilon_)
                        {
                                m_Result_ = x_;
                                return ;
                        }

                        f1 = m_Func_(x1);
                        f2 = m_Func_(x2);
                        f3 = m_Func_(x3);

                        c2 = (f1 - f2) / (x1 - x2);
                        c3 = (f1 - f3) / (x1 - x3);
                        a2 = (c2 - c3) / (x2 - x3);
                        x_ = 0.5f*(x1 + x3 - c3/a2);
			fx_ = m_Func_(x_);
#ifdef DEBUG
                        std::cout << "step: " << step++ << std::endl
                                  << "range: [" << a << ", " << b << "]" << std::endl
                                  << "x range: (" << x1 << ", " << x2 << ", " << x3 << ")" << std::endl
                                  << "x value: (" << f1 << ", " << f2 << ", " << f3 << ")" << std::endl
                                  << "result: (" << x_ << ", " << m_Func_(x_) << ")" << std::endl;
#endif
			if(std::fabs(x2 - x_) <= m_Epsilon_)
			{
				if(fx_ <= f2)
					m_Result_ = x_;
				else
					m_Result_ = x2;
				return ;
			}
			else
			{
                        	if(fx_ <= f2)
                               	{
                                	if(x_ <= x2)
					{
                                        	x3 = x2;
						b = x2;
					}
					else
					{
                                       		x1 = x2;
						a = x2;
					}
                                        x2 = x_;
                                }
                                else
                                {
                                        if(x_ <= x2)
                                    		x1 = x_;
                                        else
                                                x3 = x_;
                                }
			}
                }
	}	

	catype QuadraticInterpolationOptimizer::GetOptimizeResult() const
	{
		return m_Result_;
	}

	catype QuadraticInterpolationOptimizer::GetEpsilon() const
	{
		return m_Epsilon_;
	}

	catype QuadraticInterpolationOptimizer::GetLeftOptimizeStartPoint() const
	{
		return m_LeftOptStart_;
	}

	catype QuadraticInterpolationOptimizer::GetRightOptimizeEndPoint() const
	{
		return m_RghtOptEnd_;
	}

	void QuadraticInterpolationOptimizer::SetOptimizeMathFunction(const Optr::MathFunction<catype, catype>& func)
	{
		m_Func_ = func;
	}

	void QuadraticInterpolationOptimizer::SetEpsilon(const catype epsilon)
	{
		m_Epsilon_ = epsilon;
	}

	void QuadraticInterpolationOptimizer::SetLeftOptimizeStartPoint(const catype startp)
	{
		m_LeftOptStart_ = startp;
	}

	void QuadraticInterpolationOptimizer::SetRightOptimizeEndPoint(const catype endp)
	{
		m_RghtOptEnd_ = endp;
	}

}	// namespace Alg

}	// namespace Optr
