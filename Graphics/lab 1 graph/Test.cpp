#include "Test.h"
#include "Brezenhem.h"
#include "DDA.h"
#include "Woo.h"

int Test::get_min(int Array[], int N) {
	int min = 0;
	for (int i = 0; i < N; i++) {
		if (Array[i] < Array[min]) {
			min = i;
		}
	}
	return min;
}
int Test::get_max(int Array[], int N) {
	int max = 0;
	for (int i = 0; i < N; i++) {
		if (Array[i] > Array[max]) {
			max = i;
		}
	}
	return max;
}
double Test::get_avarage() {
	double avg = 0;
	for (int i = 0; i < 12; i++) {
		avg = avg + times[i];
	}
	avg = avg / static_cast<double>(10);
	return avg;
}
std::vector<double> Test::test() {
	std::vector<double> results;
	Brezenhem temp;
	for (int i = 0; i < 12; i++) {
		int start = clock();
		temp.line(0, 0, 150, 150);
		times[i] = clock() - start;
	}
	times[get_max(times, 12)] = 0;
	times[get_min(times, 12)] = 0;

	results.push_back(get_avarage());

	DDA tempd;
	for (int i = 0; i < 12; i++) {
		int start = clock();
		tempd.line(0, 0, 150, 150);
		times[i] = clock() - start;
	}
	times[get_max(times, 12)] = 0;
	times[get_min(times, 12)] = 0;

	results.push_back(get_avarage());

	Woo tempw;
	for (int i = 0; i < 12; i++) {
		int start = clock();
		tempw.line(0, 0, 150, 150);
		times[i] = clock() - start;
	}
	times[get_max(times, 12)] = 0;
	times[get_min(times, 12)] = 0;

	results.push_back(get_avarage());
	return results;
}