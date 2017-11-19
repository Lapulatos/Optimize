#include "gldseg.h"

namespace Optr
{

namespace Alg
{

	catype GoldenSegmentataionOptimizer::GOLDEN_SEGMENTATION_RATIO = 0.61803398875f;

	GoldenSegmentataionOptimizer::GoldenSegmentataionOptimizer(const Optr::MathFunction<catype, catype>& func, const catype epsilon, const catype startp, const catype endp) :
		m_Func_(func), m_Epsilon_(epsilon), m_Result_((catype)0.0f), m_LeftOptStart_(startp), m_RghtOptEnd_(endp)
	{}

	void GoldenSegmentataionOptimizer::Optimize()
	{
		catype a = m_LeftOptStart_, b = m_RghtOptEnd_;
		catype x2 = a + GOLDEN_SEGMENTATION_RATIO*(b - a);
		catype x1 = a + b - x2;

		catype left = m_Func_(x1);
		catype right = m_Func_(x2);
	
#ifdef DEBUG
		int step = 0;
#endif	// DEBUG
		while(true)
		{
#ifdef DEBUG
                        std::cout << "step: " << step++ << std::endl
                                  << "range: [" << a << ", " << b << "]" << std::endl
                                  << "x range: [" << x1 << ", " << x2 << "]" << std::endl
                                  << "x value: (" << left << ", " << right << ")" << std::endl
                                  << "result: " << ((a + b) / 2.0f)<< std::endl;
#endif // DEBUG
			if(left > right)
			{
				a = x1;
		
				if(std::fabs(b - a) < m_Epsilon_)
				{
					m_Result_ = (a + b) / 2.0f;
					return ;
				}
				else
				{
					x1 = x2;
					x2 = a + GOLDEN_SEGMENTATION_RATIO*(b - a);
					left = right;
					right = m_Func_(x2);
				}
			}
			else
			{
				b = x2;
				
				if(std::fabs(b - a) < m_Epsilon_)
				{
					m_Result_ = (a + b) / 2.0f;
					return ;
				}
				else
				{
					x2 = x1;
					x1 = a + (1.0f - GOLDEN_SEGMENTATION_RATIO)*(b - a);
					right = left;
					left = m_Func_(x1);
				}
			}
		}
	}

	catype GoldenSegmentataionOptimizer::GetOptimizeResult() const
	{
		return m_Result_;
	}

	catype GoldenSegmentataionOptimizer::GetEpsilon() const
	{
		return m_Epsilon_;
	}

	catype GoldenSegmentataionOptimizer::GetLeftOptimizeStartPoint() const
	{
		return m_LeftOptStart_;
	}

	catype GoldenSegmentataionOptimizer::GetRightOptimizeEndPoint() const
	{
		return m_RghtOptEnd_;
	}

	void GoldenSegmentataionOptimizer::SetOptimizeMathFunction(const Optr::MathFunction<catype, catype>& func)
	{
		m_Func_ = func;
	}

	void GoldenSegmentataionOptimizer::SetEpsilon(const catype epsilon)
	{
		m_Epsilon_ = epsilon;
	}
	
	void GoldenSegmentataionOptimizer::SetLeftOptimizeStartPoint(const catype startp)
	{
		m_LeftOptStart_ = startp;
	}

	void GoldenSegmentataionOptimizer::SetRightOptimizeEndPoint(const catype endp)
	{
		m_RghtOptEnd_ = endp;
	}

}	// namespace Alg

}	// namespace Optr
