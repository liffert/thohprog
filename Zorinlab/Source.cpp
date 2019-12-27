#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <iomanip>

double calculate_sin(double x, double eps, long long int &n, double &Un) {

	double result;
	n = 1;

	if (x >= 0 && x < M_PI_4) {
		Un = x;
		result = Un;
		while (1) {
			Un = -((x * x) / (2 * n * (2 * n + 1))) * Un;
			if (fabs(Un) <= eps) {
				break;
			}
			result = result + Un;
			n++;
		}
	}
	else {
		Un = 1;
		result = Un;
		x = M_PI_2 - x;
		while (1) {
			Un = -((x * x) / (2 * n * (2 * n - 1))) * Un;
			if (fabs(Un) <= eps) {
				break;
			}
			result = result + Un;
			n++;
		}
	}

	return result;
}

double calculate_sin2(double x, long long int count, double& Un) {

	double result;

	if (x >= 0 && x < M_PI_4) {
		Un = x;
		result = Un;
		for (long long int n = 1; n <= count; n++) {
			Un = -((x * x) / (2 * n * (2 * n + 1))) * Un;
			if (n != count) {
				result = result + Un;
			}
		}
	}
	else {
		Un = 1;
		result = Un;
		x = M_PI_2 - x;
		for (long long int n = 1; n <= count; n++) {
			Un = -((x * x) / (2 * n * (2 * n - 1))) * Un;
			if (n != count) {
				result = result + Un;
			}
		}
	}

	return result;
}
double sin_second(double x, long long int count, double& Un) {
	double y = (x > 0 ? 1 : -1);
	x = std::fmod(fabs(x), (2 * M_PI));
	if (x >= 0 && x < M_PI_2) {
		y = y * calculate_sin2(fabs(x), count, Un);
	}
	else if (x >= M_PI_2 && x < M_PI) {
		y = y * calculate_sin2(fabs(M_PI - x), count, Un);
	}
	else if (x >= M_PI && x < 3 * M_PI_2) {
		y = y * (-calculate_sin2(fabs(x - M_PI), count, Un));
	}
	else {
		y = y * (-calculate_sin2(fabs(2 * M_PI - x), count, Un));
	}
	return y;
}
double sin_first(double x, double eps, long long int& n, double &Un) {
	double y = (x > 0 ? 1 : -1);
	x = std::fmod(fabs(x), (2 * M_PI));
	if (x >= 0 && x < M_PI_2) {
		y = y * calculate_sin(fabs(x), eps, n, Un);
	}
	else if (x >= M_PI_2 && x < M_PI) {
		y = y * calculate_sin(fabs(M_PI - x), eps, n, Un);
	}
	else if (x >= M_PI && x < 3*M_PI_2) {
		y = y * (-calculate_sin(fabs(x - M_PI), eps, n, Un));
	}
	else {
		y = y * (-calculate_sin(fabs(2*M_PI - x), eps, n, Un));
	}
	return y;
}

double my_cos(double x, double eps, long long int& n, double &Un) {
	return sin_first(x + M_PI_2, eps, n, Un);
}
double my_cos2(double x, long long int count, double& Un) {
	return sin_second(x + M_PI_2, count, Un);
}

int main() {
	double a = -31.3;
	double b = -4.9;
	double Un = NULL;
	long long int n = NULL;
	long long int n8;
	double h = (b - a) / 2.0;

	double x = (a + b) / 2.0;
	std::cout << "EPS   | N | COS               | Infelicity           | Un\n" << std::setprecision(15);

	for (double eps = 1.e-2; eps >= 1.e-14; eps = eps/1000) {
		double result = my_cos(x, eps, n, Un);
		std::cout << std::setw(5) << eps << " | " << n << " | " << std::setw(17) << result << " | " << std::setw(20) << fabs(result - cos(x)) << " | " << fabs(Un) << std::endl;
		if (eps == 1.e-8) {
			n8 = n;
		}
	}

	std::cout << "--------------------------------------------------------------------------------------------------\n";
	std::cout << "Xi                | Infelicity           | Un\n";
	for (int i = 0; i <= 10; i++) {
		x = a + h * i;
		std::cout << std::setw(17) << x << " | " << std::setw(20) << fabs(cos(x) - my_cos2(x, n8, Un)) << " | " << fabs(Un) << std::endl;
	}

	return 0;
}