#include <iostream>

#include "utils.h"
#include "exception.h"
#include "mathdef.h"
#include "inpoltn.h"
#include "sptdst.h"
#include "gldseg.h"
#include "sucfal.h"
#include "newton.h"

///////////////////////////////////////////////////////
catype func(catype x)
{
	return (x - 0.986f)*(x - 0.986f);
}

bool dfunc(catype x)
{
	if((x >= -10.0f) && (x <= 10.0f)) 
		return true;
	return false;
}

///////////////////////////////////////////////////////
unsigned int size = 2;

Optr::MatrixXc A = Optr::MatrixXc::Identity(size, size);
Optr::VectorXc b = 2.0f*Optr::VectorXc::Ones(size);
catype c = 2.0f;

catype funcv(const Optr::VectorXc& x)
{
	return (catype)((x.transpose()*A*x + b.transpose()*x)[0] + c);
}

Optr::VectorXc dfuncv(const Optr::VectorXc& x)
{
	return (2.0f*A*x + b);
}

Optr::MatrixXc ddfuncv(const Optr::VectorXc& x)
{
	return (2.0*A);
}

////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	try 
	{
		Optr::FunctionHandler<catype, catype> f(func);
		Optr::FunctionHandler<bool, catype> df(dfunc);
		Optr::MathFunction<catype, catype> mf(df, f);
	
		catype epsilon = 1e-7f;
		catype a = -1.1f, b = 1.3f;

			
		std::cout << "==================== Quadratic Interpolation Optimize ====================" << std::endl;
		std::cout << "Optimize Function: y = (x - 0.986)*(x - 0.986)" << std::endl;
		std::cout << "left bound a: " << a << std::endl;
		std::cout << "right boud b: " << b << std::endl;
		std::cout << "Quadratic Interpolation  Optimize Start ========================================" << std::endl;
		Optr::Alg::QuadraticInterpolationOptimizer qioptr(mf, epsilon, a, b);
		qioptr.Optimize();
		std::cout << "Optimize Result: " << qioptr.GetOptimizeResult() << " --> " << mf(qioptr.GetOptimizeResult()) << std::endl;
		std::cout << "Quadratic Interpolation Optimize Stop ========================================" << std::endl;		


                std::cout << "==================== Golden Segmentation Optimize ====================" << std::endl;
                std::cout << "Optimize Function: y = (x - 0.986)*(x - 0.986)" << std::endl;
		std::cout << "left bound a: " << a << std::endl;
		std::cout << "right boud b: " << b << std::endl;
                std::cout << "Golden Segmentation  Optimize Start ========================================" << std::endl;
                Optr::Alg::GoldenSegmentataionOptimizer gsoptr(mf, epsilon, a, b);
                gsoptr.Optimize();
                std::cout << "Optimize Result: " << gsoptr.GetOptimizeResult() << " --> " << mf(gsoptr.GetOptimizeResult()) << std::endl;
                std::cout << "Golden Segmentation Optimize Stop ========================================" << std::endl;
		

		catype x = 1.7f, steplen = 0.1f;
                std::cout << "==================== Success-Failure Optimize ====================" << std::endl;
                std::cout << "Optimize Function: y = (x - 0.986)*(x - 0.986)" << std::endl;
		std::cout << "initial x: " << x << std::endl;
		std::cout << "initial step length: " << steplen << std::endl;
                std::cout << "Success-Failure  Optimize Start ========================================" << std::endl;
                Optr::Alg::SuccessFailureOptimizer sfoptr(mf, epsilon, steplen, x);
                sfoptr.Optimize();
                std::cout << "Optimize Result: " << sfoptr.GetOptimizeResult() << " --> " << mf(sfoptr.GetOptimizeResult()) << std::endl;
                std::cout << "Success-Failure Optimize Stop ========================================" << std::endl;


		
		/////////////////////////////////////////////////
		Optr::FunctionHandler<catype, const Optr::VectorXc&> fv(funcv);
		Optr::FunctionHandler<bool, const Optr::VectorXc&> fvd([](const Optr::VectorXc& x){ return true; });
		Optr::MathFunction<catype, const Optr::VectorXc&> mfv(fvd, fv);

		Optr::FunctionHandler<Optr::VectorXc, const Optr::VectorXc&> dfv(dfuncv);
		Optr::FunctionHandler<bool, const Optr::VectorXc&> dfvd([](const Optr::VectorXc& x){ return true; });
		Optr::MathFunction<Optr::VectorXc, const Optr::VectorXc&> mdfv(dfvd, dfv);
		
		Optr::FunctionHandler<Optr::MatrixXc, const Optr::VectorXc&> ddfv(ddfuncv);
		Optr::FunctionHandler<bool, const Optr::VectorXc&> ddfvd([](const Optr::VectorXc& x){ return true; });
		Optr::MathFunction<Optr::MatrixXc, const Optr::VectorXc&> mddfv(ddfvd, ddfv);

		Optr::VectorXc initx = Optr::VectorXc::Ones(size);
		initx(1) = 0.0f;

		std::cout << "==================== Speedest Descent Optimize ====================" << std::endl;
		std::cout << "Optimize Function: f(x) = x'*A*x + b'*x + c" << std::endl;
		std::cout << "Matrix A: " << std::endl << A << std::endl;
		std::cout << "Vector b: (" << ::b.transpose() << ")'" << std::endl;		
		std::cout << "Scalar c: " << c << std::endl;
		std::cout << "init point: (" << initx.transpose() << ")'" << std::endl;		
		std::cout << "init result: " << mfv(initx) << std::endl;
		std::cout << "init gradient: (" << mdfv(initx).transpose() << ")'" << std::endl;
		std::cout << "Speedest Descent Optimize Start ========================================" << std::endl;
		Optr::Alg::SteepestDescentOptimizer sdoptr(mfv, mdfv, epsilon, initx);
		sdoptr.Optimize();
		std::cout << "Optimize Result: (" << sdoptr.GetOptimizeResult().transpose() << ")' --> " << mfv(sdoptr.GetOptimizeResult()) << std::endl;
		std::cout << "Speedest Descent Optimize Stop ========================================" << std::endl;		


                std::cout << "==================== Newton Method Optimize ====================" << std::endl;
                std::cout << "Optimize Function: f(x) = x'*A*x + b'*x + c" << std::endl;
                std::cout << "Matrix A: " << std::endl << A << std::endl;
                std::cout << "Vector b: (" << ::b.transpose() << ")'" << std::endl;
                std::cout << "Scalar c: " << c << std::endl;
                std::cout << "init point: (" << initx.transpose() << ")'" << std::endl;
                std::cout << "init result: " << mfv(initx) << std::endl;
                std::cout << "init gradient: (" << mdfv(initx).transpose() << ")'" << std::endl;
                std::cout << "init hessian matrix: " << std::endl << mddfv(initx) << std::endl;
                std::cout << "Newton Method Optimize Start ========================================" << std::endl;
                Optr::Alg::NewtonMethodOptimizer nmoptr(mfv, mdfv, mddfv, epsilon, initx);
                nmoptr.Optimize();
                std::cout << "Optimize Result: (" << nmoptr.GetOptimizeResult().transpose() << ")' --> " << mfv(nmoptr.GetOptimizeResult()) << std::endl;
                std::cout << "Newton Method Optimize Stop ========================================" << std::endl; 

	}
	catch(const Optr::Exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

