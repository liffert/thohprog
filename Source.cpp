#include <iostream>
#include <iomanip>

#define default_n 4
#define default_m 5


const double def[default_n][default_m] = {
	{ 3, 19, 11,  8, 149},
	{ 9, 31,  3, 18, 257},
	{11,  7, 32, 13, 143},
	{12, 19, 12,  5, 144}
};

const double def_withdiag[default_n][default_m] = {
	{ 300, 19, 11,  8, 149},//так как не вышло привести матрицу к виду диагонального преобладания,
	{ 9, 310,  3, 18, 257},//то все элементы главной диагонали были увеличены
	{11,  7, 320, 13, 143},
	{12, 19, 12,  50, 144}
};

void create_matrix(double**& mat, const int n, const int m) {
	mat = new double* [n];
	for (int i = 0; i < n; i++) {
		mat[i] = new double[m]();
	}
}

void delmat(double**& mat, const int n) {
	for (int i = 0; i < n; i++) {
		delete[]mat[i];
	}
	delete[]mat;
	mat = nullptr;
}

void print_matrix(const double** mat, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cout << mat[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
void print_result(const double* res, const int n, std::string method) {
	std::cout << method << std::endl;
	for (int i = 0; i < n; i++) {
		std::cout << "X[" << i + 1 << "] = " << std::scientific << std::setprecision(15) << res[i] << std::endl;
	}
}
void fill_matrix(double ** &mat, const int n, const int m, bool Default) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (Default) {
				mat[i][j] = def[i][j];
			}
			else {
				mat[i][j] = def_withdiag[i][j];
			}
		}
	}
}

bool check_diag(double**& mat, const int n, const int m) {
	double sum = 0; 

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i == j) { continue; }
			sum = sum + fabs(mat[i][j]);
		}
		if (sum > fabs(mat[i][i])) {
			return false;
		}
		sum = 0;
	}
}

double* zeideliter(double**& mat, double eps, int &maxiter, bool& reach, const int n, const int m) {
	if (!check_diag(mat, n - 1, m - 1)) {
		return nullptr;
	}
	double* arr = new double[n]();
	double* arrT = new double[n]();
	int i = 0;

	for (int i = 0; i < n; i++) {
		mat[i][m - 1] = mat[i][m - 1] / mat[i][i];
	}

	for (int i = 0; i < n; i++) {
		double temp = mat[i][i];
		for (int j = 0; j < m - 1; j++) {
			if (i != j) {
				mat[i][j] = -mat[i][j] / temp;
			}
			else {
				mat[i][j] = 0;
			}
		}
	}

	double normal = 0;

	
	for (int i = 0; i < n; i++) {
		double sum = 0;
		for (int j = 0; j < m - 1; j++) {
			sum = sum + fabs(mat[i][j]);
		}
		if (sum > normal) {
			normal = sum;
		}
	}

	
	while (1) {

		for (int i = 0; i < n; i++) {
			arrT[i] = arr[i];
		}

		for (int i = 0; i < n; i++) {
			arr[i] = mat[i][m - 1];
			for (int j = 0; j < n; j++) {
				arr[i] = arr[i] + mat[i][j] * arr[j];
			}
		}

		
		double temp = 0;
		double norm = 0;
		for (int i = 0; i < 4; i++) {
			temp = fabs(arrT[i] - arr[i]);
			if (temp > norm) {
				norm = temp;
			}
		}
		i++;
		if (norm <= eps * (1 - normal) / normal) {
			reach = true;
			maxiter = i;
			break;
		}
		if(i > maxiter) {
			reach = false;
			break;
		}
	}

	delete[] arrT;
	return arr;

}



void cpy(double*& dest, double* source, int n) {
	for (int i = 0; i < n; i++) {
		dest[i] = source[i];
	}
}

void delete_row(double**& mat, double**& newmat, int n, int m, int p, int q) {
	int temp_i = 0;
	int temp_j = 0;
	for (int i = 0; i < n; i++) {
		temp_j = 0;
		if (i == p) { continue; }
		for (int j = 0; j < m; j++) {
			if (j == q) { continue; }
			newmat[temp_i][temp_j] = mat[i][j];
			temp_j++;
		}
		temp_i++;
	}
	bool f = true;
	delmat(mat, n);
	mat = newmat;
}

double* complete_pivoting(double**& mat, int n, int m) {
	int k = 0;
	int N = n;
	int M = m;

	double*** history = new double** [n];
	for (int i = 0; i < n; i++) {
		create_matrix(history[i], 2, m - i);
	}

	for (int i = 0; i < m; i++) {
		history[0][0][i] = mat[0][i];
		history[0][1][i] = i + 1;
	}
	history[0][1][m - 1] = 0;


	while (1) {
		double max = 0;
		int p = 0;
		int q = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m - 1; j++) {
				if (max < fabs(mat[i][j])) {
					max = fabs(mat[i][j]);
					p = i;
					q = j;
				}
			}
		}
		if (max == 0) {
			return nullptr;
		}

		double* mc = new double[n];
		for (int i = 0; i < n; i++) {
			if (i == p) { continue; }
			mc[i] = 0 - (mat[i][q] / mat[p][q]);
		}

		double* copymain = new double[m];


		for (int i = 0; i < n; i++) {
			if (i == p) { continue; }
			cpy(copymain, mat[p], m);

			for (int j = 0; j < m; j++) {
				copymain[j] = copymain[j] * mc[i];
			}

			for (int j = 0; j < m; j++) {
				mat[i][j] = mat[i][j] + copymain[j];
			}

		}

		delete[] copymain;

		double** newmat;
		create_matrix(newmat, n - 1, m - 1);
		delete_row(mat, newmat, n, m, p, q);

		k++;
		n--;
		m--;

		int historyp = 0;
		for (int i = 0; i < m; i++) {
			history[k][0][i] = mat[0][i];
			if (i != q) {
				history[k][1][historyp] = history[k - 1][1][i];
				historyp++;
			}
		}
		delete[] mc;
		if (k >= N - 1) {
			break;
		}
	}
	k = 0;
	int t = n - 1;


	double* res = new double[N];

	for (int i = 0; i < N; i++) {
		res[i] = NAN;
	}
	
	
	for (int i = N - 1; i >= 0; i--) {
		
		int xptr = 0;
		for (int j = 0; j < M - 1 - i; j++) {
			if (isnan(res[static_cast<int>(history[i][1][j]) - 1])) {
				xptr = j;
			}
		}

		double bet = 0;
		for (int j = 0; j < N; j++) {
			if (j != static_cast<int>(history[i][1][xptr]) - 1) {
				double tempres = isnan(res[j]) ? 0 : res[j];
				int tempxptr = NAN;
				for (int z = 0; z < M - 1 - i; z++) {
					if (static_cast<int>(history[i][1][z] - 1 == j)) {
						tempxptr = z;
					}
				}
				if (tempxptr != NAN) {
					bet = bet - tempres * history[i][0][tempxptr];
				}
				else {
					bet = bet - tempres;
				}
			}
		}
		bet = bet + history[i][0][M - 1 - i];
		res[static_cast<int>(history[i][1][xptr]) - 1] = bet/ history[i][0][xptr];
	}


	for (int i = 0; i < N; i++) {
		delmat(history[i], 2);
	}
	delete[] history;

	delmat(mat, n);
	return res;
}
int main() {
	std::cout << "\t\t\tWARN WARN WARN WARN\n\t\tDifferent matrix for different method\n**************************************************************************************\n";


	double** matrix = nullptr;
	bool flag;
	int n = 4;
	int m = 5;
	int iter = 200;

	create_matrix(matrix, n, m);
	fill_matrix(matrix, n, m, false);
	
	double *result = zeideliter(matrix, 1.e-8, iter, flag, n, m);

	if (result != nullptr) {
		print_result(const_cast<double*>(result), n, "Zeidel iterations:");
		if (!flag) {
			std::cout << "**Prescision not reached\n\n**";
		}
		else {
			std::cout << "Iterations: " << iter << std::endl;
		}
	}
	else {
		std::cout << "Zeidel iterations failed" << std::endl;
	}


	fill_matrix(matrix, n, m, true);//если флаг в вызове изменить на false, то матрица будет заполнена данными матрицы с диагональным преобладанием
	//и как следствие можно увидеть, что оба метода дают одинаковый результат
	double * res = complete_pivoting(matrix, n, m);
	if (res != nullptr) {
		print_result(const_cast<const double*>(res), n, "Complete pivoting:");
	}
	else {
		std::cout << "Complete pivoting failed" << std::endl;
	}

	
	return 0;
}