#ifndef GLDSEG_INCLUDED
#define GLDSEG_INCLUDED

#include "utils.h"
#include "mathdef.h"
#include "optimizer.h"

namespace Optr
{

namespace Alg
{

	class GoldenSegmentataionOptimizer : public Alg::Optimizer
	{
	public:
		GoldenSegmentataionOptimizer(const Optr::MathFunction<catype, catype>& func, const catype epsilon,
					     const catype startp, const catype endp);

		void Optimize();

		catype GetOptimizeResult() const;
		catype GetEpsilon() const;
		catype GetLeftOptimizeStartPoint() const;
		catype GetRightOptimizeEndPoint() const;
		void SetOptimizeMathFunction(const Optr::MathFunction<catype, catype>& func);
		void SetEpsilon(const catype epsilon);
		void SetLeftOptimizeStartPoint(const catype startp);
		void SetRightOptimizeEndPoint(const catype endp);
	
	public:
		static catype GOLDEN_SEGMENTATION_RATIO;	// 黄金分割比
	private:
		Optr::MathFunction<catype, catype> m_Func_;	// 待优化函数
		catype m_Epsilon_;		// 近似解求解精度
		catype m_Result_;		// 近似解

		catype m_LeftOptStart_;		// 左优化起始点[在待优化函数定义域内]
		catype m_RghtOptEnd_;		// 右优化终止点[在待优化函数定义域内]
	};	// class GoldenSegmentationOptimizer

}	// namespace Alg

}	// namespace Optr

#endif	// GLDSEG_INCLUDED
