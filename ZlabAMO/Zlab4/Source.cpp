#include <iostream>
#include <math.h>
#include <iomanip>
#include <vector>


double delta(double a, double b) {
	return fabs(a - b);
}
double func(double x) {
	return (sin(x) * sin(x) * x);
}
double F(double x) {
	//return (-(sin(2 * x) / 4) + (x / 2)); при первообразной взятой с варианта считает метод Ньютона считает не верно
	return ((2 * x * (x - sin(2 * x)) - cos(2 * x)) / 8);//по этому первообразная взята с вольфрама
}
double Newton(double a, double b) {
	return (F(b) - F(a));
}
double calc_h(double a, double b, double eps) {
	double M2 = 25.1625;
	return sqrt(12 * eps / ((b - a) * M2));
}
double trap(double a, double b, double eps, double& h, bool double_iter = false) {
	h = calc_h(a, b, eps);
	int n = 0;
	if (double_iter) { n = eps; }
	else { n = (b - a) / h; }
	h = (b - a) / static_cast<double>(n);
	double y = func(a)/2;
	double temp = 0;

	for (int i = 1; i < n; i++) {
		temp = a + h * i;
		y = y + func(temp);
	}


	y = y + func(b) / 2;
	y = y * h;
	return y;
}

double double_iteration(double a, double b, double eps, double &h) {
	int n = (b - a) / sqrt(eps);
	double integer[2];
	integer[0] = trap(a, b, n, h, true);
	n = n * 2;
	integer[1] = trap(a, b, n, h, true);

	while (delta(integer[0], integer[1]) > 3 * eps) {
		integer[0] = integer[1];
		n = n * 2;
		integer[1] = trap(a, b, n, h, true);
	}

	return integer[1];
}

std::vector<double> print_table1(double a, double b) {
	std::vector<double> ERRORS;
	std::cout << std::setw(24) << "EPS | " << std::setw(24) << "STEP | " << std::setw(24) << "NEWTON | " << std::setw(22) << "ERROR\n";
	double eps = 1e-3;
	std::cout << std::scientific << std::setprecision(15);
	while (eps >= 1e-6) {
		double step = 0;
		double trap_res = trap(a, b, eps, step);
		double newton_res = Newton(a, b);
		double error = fabs(trap_res - newton_res);
		ERRORS.push_back(error);
		std::cout << eps << " | " << step << " | " << newton_res << " | " << error << std::endl;
		eps = eps / 10;
	}
	return ERRORS;
}
void print_table2(double a, double b, const std::vector <double> deltas) {
	std::cout << std::setw(24) << "DELTA | " << std::setw(24) << "STEP | " << std::setw(22) << "ERROR\n";
	double eps = 1e-3;
	std::cout << std::scientific << std::setprecision(15);
	auto iter = deltas.begin();
	while (eps >= 1e-6) {
		double step = 0;
		double double_iter_res = double_iteration(a, b, *iter, step);
		std::cout << *iter << " | " << step << " | " << fabs(double_iter_res - Newton(a, b)) << "\tEPS = " << eps <<  std::endl;
		eps = eps / 10;
		iter++;
	}
}

int main() {
	int a = 1;
	int b = 27;
	std::cout << "FIRST TABLE\n";
	std::vector<double> deltas = print_table1(a, b);
	std::cout << std::endl;
	std::cout << "SECOND TABLE\n";
	print_table2(a, b, deltas);
}