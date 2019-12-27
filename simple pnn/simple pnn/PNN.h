#pragma once
#include "Header.h"
#include <fstream>

class PNN {
public:
	PNN(std::string path) { this->path = path; }
	~PNN() {}

	void train();
	void train2();
	std::string get_atack(std::string input);
	std::string get_atack2(std::string input);


private:
	typedef struct data {
		std::string connect;
		std::string connect2;
		std::string atack;
		std::vector <int> nums;
	}data_t;

	std::string get_data(std::string data, int i);
	int compare(data_t one, data_t two);

	std::vector<data_t> knowledge;
	std::string path;
	
	typedef struct att {
		int even = 0;
		int odd = 0;
		int mix = 0;
		std::string get_type() {
			if (even > odd) {
				if (even > mix) {
					return "even";
				}
				else {
					return "mix";
				}
			}
			else {
				if (odd > mix) {
					return "odd";
				}
				else {
					return "mix";
				}
			}
		}
	}att_t;
	att_t smurf;
	att_t normal;
	att_t neptun;

};

