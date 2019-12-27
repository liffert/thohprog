#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

double Tfunc(double x) {
	return x * x * x + 3 * x + 1;
}

double DR(double x, double y) {
	return (2 * x * y) / (x * x + 1);
}

void k_calc(double x, double &Y, double &NY, double h) {
	double Karr[4];
	Karr[0] = h * DR(x, NY);
	Karr[1] = h * DR(x + h / 2, NY + Karr[0] / 2);
	Karr[2] = h * DR(x + h / 2, NY + Karr[1] / 2);
	Karr[3] = h * DR(x + h, NY + Karr[2]);
	Y = Y + h * NY + (Karr[0] + Karr[1] + Karr[2]) * h / 6;
	NY = NY + (Karr[0] + 2 * Karr[1] + 2 * Karr[2] + Karr[3]) / 6;

}

double RKM(std::vector<double>& Xarr, std::vector<double>& Yarr, std::vector<double>& DRarr, double& step, double eps) {
	double a = 0;
	double b = 1;
	int n = 10;
	double h;
	double x;
	double Y = 1;
	double NY = 3;

	while(1) {
		h = (b - a) / static_cast<double>(n);
		x = a;

		Y = 1;
		NY = 3;
		Yarr.clear();
		DRarr.clear();
		Xarr.clear();

		for (int i = 0; i <= n; i++) {
			Xarr.push_back(x);
			Yarr.push_back(Y);
			DRarr.push_back(NY);
			k_calc(x, Y, NY, h);
			x += h;
		}
		n++;
		if ((fabs(Tfunc(b) - *(Yarr.end() - 1)) < eps)) {
			step = n;
			return fabs(Tfunc(b) - *(Yarr.end() - 1));
		}
	}
}


void rec(std::vector<double>& Xarr, std::vector<double>& Yarr, std::vector<double>& DRarr, double &step, double eps) {
	double y;
	double x;
	double Y; 
	double NY;
	double tempS = 0;
	double a = 0;
	double b = 1;
	int n = (b - a) / sqrt(sqrt(eps));

	for (int i = 1; i < step; i++) {
		tempS = (Xarr[i] - Xarr[i - 1]) / n;
		x = Xarr[i - 1];
		Y = Yarr[i - 1];
		NY = DRarr[i - 1];

		for (int j = 0; j < n; j++) {
			k_calc(x, Y, NY, tempS);
			x = x + tempS;
		}
		y = Y;

		n = n * 2;
		tempS = (Xarr[i] - Xarr[i - 1]) / n;
		x = Xarr[i - 1];
		Y = Yarr[i - 1];
		NY = DRarr[i - 1];

		for (int j = 0; j < n; j++) {
			k_calc(x, Y, NY, tempS);
			x = x + tempS;
		}
		while (fabs(Y - y) > 15 * eps) {
			y = Y;
			n = n * 2;
			tempS = (Xarr[i] - Xarr[i - 1]) / n;
			x = Xarr[i - 1];
			Y = Yarr[i - 1];
			NY = DRarr[i - 1];

			for (int j = 0; j < n; j++) {
				k_calc(x, Y, NY, tempS);
				x = x + tempS;
			}
		}
		Yarr[i] = Y;
	}
	step = tempS;
}

int main() {
	std::vector <double> Xarr;
	std::vector <double> Yarr;
	std::vector <double> DRarr;
	double a = 0;
	double b = 1;

	double step = 0;
	double Ac = RKM(Xarr, Yarr, DRarr, step, 10e-2);

	std::cout << "-------------------------------------------------------\n";
	std::cout << "The third task\n";
	auto Y_i = Yarr.begin();
	for (auto iter : Xarr) {
		std::cout << iter << "\t\t" << *Y_i << "\t\t" << fabs(Tfunc(iter) - *Y_i) << std::endl;
		Y_i++;
	}
	double s = (b - a) / step;
	std::cout << "-------------------------------------------------------\n";
	std::cout << "\nThe first task\n";
	std::cout << "Value of integral in point B = " << b << ":\t" << *(Yarr.end() - 1) << std::endl << "With eps: " << 10e-2 << std::endl;
	std::cout << "Step: " << s << std::endl;
	std::cout << "-------------------------------------------------------\n";

	std::cout << "\nThe second task\n";
	rec(Xarr, Yarr, DRarr, step, Ac);
	Y_i = Yarr.begin();
	for (auto iter : Xarr) {
		std::cout << iter << "\t\t" << *Y_i << "\t\t" << fabs(Tfunc(iter) - *Y_i) << std::endl;
		Y_i++;
	}
	std::cout << "Step after double rec: " << step << std::endl;
	std::cout << "-------------------------------------------------------\n";
}