#include <iostream>
#include <math.h>
#include <iomanip>
#include <vector>
#define ERRORCODE 1

struct Res {
	double Result;
	double eps;
	double error;
	int iterations;
	bool flag = false;
};

double calculate(double x) {
	return (x * x + 2 * sin(x) - 1);
}

double funcI(double fm, double fM, double begin, double end, double eps, int &maxiter, bool &precision, double &error) {
	
	if (fm * fM < 0) {
		std::cout << "ERROR" << std::endl;
		return ERRORCODE;
	}
	
	double xk = (begin + end) / 2;
	double x0 = 0;
	double q;
	double lam;

	if (fm > 0) {
		q = 1 - (fm / fM);
	}
	else {
		q = 1 - (fM / fm);
	}

	lam = 1 / (fM);

	for (int i = 0; i < maxiter; i++) {
		x0 = xk;
		xk = x0 - lam * calculate(x0);
		if (fabs(xk - x0) * (q / (1 - q)) <= eps) {
			precision = true;
			maxiter = i;
			break;
		}
	}

	error = fabs(xk - x0) * (q/(1 - q));
	return xk;
}

double calculateDer(double x) {
	return 2 * x + 2 * cos(x);
}
double calculateDer2(double x) {
	return 2 - 2 * sin(x);
}

double funcD(double begin, double end, double eps, double m1, double &error, int &maxiter, bool &precision) {
	
	int i = 0;
	double xk;

	if (calculateDer2(begin) * calculate(begin) > 0) {
		xk = begin;
	}
	else if(calculateDer2(end) * calculate(end) > 0) {
		xk = end;
	}
	else {
		return ERRORCODE;
	}
	
	while (fabs(calculate(xk))/m1 > eps) {
		xk = xk - calculate(xk) / calculateDer(xk);
		i++;
		if (i > maxiter) {
			break;
		}
	}

	if (i < maxiter) {
		precision = true;
	}
	maxiter = i;
	error = fabs(calculate(xk)) / m1;
	return xk;
}


void printRes(std::vector<Res> Result) {
	std::cout << "|EPS|X|ERROR" << std::endl;

	for (auto iter = Result.begin(); iter != Result.end(); iter++) {
		std::cout << "|" << (*iter).eps << "|" << (*iter).Result << "|" << (*iter).error;
		if (!(*iter).flag) {
			std::cout << "\tprecision not reached\n";
		}
		else {
			std::cout << std::endl;
		}
	}
}

void printCount(std::vector<Res> ResI, std::vector<Res> ResT) {
	std::cout << "Iteration count:" << std::endl << "Iter Count|Tan count|EPS" << std::endl;
	for (int i = 0; i < ResI.size(); i++) {
		std::cout << "|" << std::setw(9) << ResI[i].iterations << "|" << std::setw(9) << ResT[i].iterations << "|" << ResI[i].eps << std::endl;
	}
}
int main() {
	
	std::vector<Res> ResultsIter;
	std::vector<Res> ResultsTan;
	struct Res Result;
	Result.eps = 1.e-2;
	Result.iterations = 200;

	std::cout << "Iterations:\n";
	std::cout << std::scientific << std::setprecision(15);
	for (int i = 0; i < 4; i++) {
		Result.Result = funcI(-4.9, -2.8, -2, -1.5, Result.eps, Result.iterations, Result.flag, Result.error);
		ResultsIter.push_back(Result);
		Result.eps = Result.eps / 1000.0;
		Result.iterations = 200;
		Result.flag = false;
	}
	Result.eps = 1.e-2;
	Result.iterations = 200;
	
	for (int i = 0; i < 4; i++) {
		Result.Result = funcI(2, 3.2, 0, 0.5, Result.eps, Result.iterations, Result.flag, Result.error);
		ResultsIter.push_back(Result);
		Result.eps = Result.eps / 1000.0;
		Result.iterations = 200;
		Result.flag = false;
	}

	printRes(ResultsIter);


	std::cout << "------------------------------------------------------------------------------------------\n\nTangents:\n";
	
	Result.eps = 1.e-2;
	Result.iterations = 200;
	for (int i = 0; i < 4; i++) {
		Result.Result = funcD(-2, -1.5, Result.eps, 2.86, Result.error, Result.iterations, Result.flag);
		ResultsTan.push_back(Result);
		Result.eps = Result.eps / 1000.0;
		Result.iterations = 200;
		Result.flag = false;
	}
	Result.eps = 1.e-2;
	Result.iterations = 200;

	for (int i = 0; i < 4; i++) {
		Result.Result = funcD(0, 0.5, Result.eps, 0.21, Result.error, Result.iterations, Result.flag);
		ResultsTan.push_back(Result);
		Result.eps = Result.eps / 1000.0;
		Result.iterations = 200;
		Result.flag = false;
	}
	printRes(ResultsTan);

	std::cout << "------------------------------------------------------------------------------------------\n\nTable two:\n";
	printCount(ResultsIter, ResultsTan);


}