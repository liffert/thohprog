#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

double Tfunc(double x) {
	return x * x * x + 3 * x + 1;
}

double DR(double y, double x) {
	return 2 * x * y / (x * x + 1);
}


double RKM(std::vector<double>& Xarr, std::vector<double>& Yarr, std::vector<double>& DRarr, double& step, double eps) {
	
	int a = 0;
	int b = 1;
	int n = 10;
	double Karr[4];

	double x;

	while (1) {
		step = static_cast<double>((b - a)) / static_cast<double>(n);
		Xarr.clear();
		Yarr.clear();
		DRarr.clear();
		double Y = 1;
		double DY = 3;
		for (int i = 0; i <= n; i++) {
			x = a + i * step;
			Karr[0] = step * DR(x, DY);
			Karr[1] = step * DR(x + step / 2, DY + Karr[0] / 2);
			Karr[2] = step * DR(x + step / 2, DY + Karr[1] / 2);
			Karr[3] = step * DR(x + step, DY + Karr[2]);

			Xarr.push_back(x);
			Yarr.push_back(Y);
			DRarr.push_back(DY);

			Y = Y + step * DY + (Karr[0] + Karr[1] + Karr[2]) / 6 * step;
			DY = DY + (Karr[0] + Karr[1] + Karr[2] + Karr[3]) / 6;
		}
		n++;
		if (fabs(Tfunc(b) - Y) < eps) {
			return fabs(Tfunc(b) - DY);
		}
	}
}


int main() {
	std::vector <double> Xarr;
	std::vector <double> Yarr;
	std::vector <double> DRarr;

	double step = 0;
	double a = RKM(Xarr, Yarr, DRarr, step, 10e-2);

	std::cout << "R method\n";
	for (auto iter : Xarr) {
		auto Y_i = Yarr.begin();
		std::cout << iter << "\t" << *Y_i << "\t" << fabs(Tfunc(iter - *Y_i)) << std::endl;
	}
	std::cout << "Step: " << step;

}