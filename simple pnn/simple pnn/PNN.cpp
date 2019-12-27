#include "PNN.h"
#include <string>

void PNN::train() {
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cout << "Traint file error\n";
		return;
	}

	std::string buf;

	while (!file.eof()) {
		std::getline(file, buf);
		if (buf.empty()) { file.close(); return; }
		data_t temp;
		temp.connect = this->get_data(buf, 0);
		temp.connect2 = this->get_data(buf, 1);
		for (int i = 2; i < 7; i++) {
			temp.nums.push_back(std::stoi(this->get_data(buf, i)));
		}
		temp.atack = this->get_data(buf, 7);
		knowledge.push_back(temp);
	}
	file.close();
}

void PNN::train2() {
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cout << "Traint file error\n";
		return;
	}

	std::string buf;

	while (!file.eof()) {
		std::getline(file, buf);
		if (buf.empty()) { file.close(); return; }
		data_t temp;
		temp.connect = this->get_data(buf, 0);
		temp.connect2 = this->get_data(buf, 1);

		att_t nums;
		for (int i = 2; i < 7; i++) {
			int a = std::stoi(this->get_data(buf, i));
			if (a % 2 == 0) {
				nums.even++;
			}
			else if (a % 2 != 0) {
				nums.odd++;
			}
		}
		temp.atack = this->get_data(buf, 7);
		if (temp.atack == "smurf") {
			if (nums.even == 0) {
				smurf.odd++;
			}
			else if(nums.odd == 0) {
				smurf.even++;
			}
			else {
				smurf.mix++;
			}
		}
		else if (temp.atack == "neptune") {
			if (nums.even == 0) {
				neptun.odd++;
			}
			else if (nums.odd == 0) {
				neptun.even++;
			}
			else {
				neptun.mix++;
			}
		}
		else {
			if (nums.even == 0) {
				normal.odd++;
			}
			else if (nums.odd == 0) {
				normal.even++;
			}
			else {
				normal.mix++;
			}
		}
	}
	file.close();
}

std::string PNN::get_atack(std::string input) {
	if (input.empty()) { std::cout << "Input empty\n"; return ""; }
	data_t temp;
	temp.connect = this->get_data(input, 0);
	temp.connect2 = this->get_data(input, 1);
	for (int i = 2; i < 7; i++) {
		temp.nums.push_back(std::stoi(this->get_data(input, i)));
	}


	int comp = 0;
	data_t winner;
	for (auto iter : knowledge) {
		int t_c = compare(iter, temp);
		if (t_c != 0 && t_c > comp) {
			comp = t_c;
			winner = iter;
		}
	}
	if (comp == 2) {
		return "Not response\n";
	}
	return winner.atack + " Result: " + std::to_string(comp) + "\n";
}

std::string PNN::get_atack2(std::string input) {
	if (input.empty()) { std::cout << "Input empty\n"; return ""; }
	data_t temp;
	temp.connect = this->get_data(input, 0);
	temp.connect2 = this->get_data(input, 1);
	
	att_t nums;
	for (int i = 2; i < 7; i++) {
		int a = std::stoi(this->get_data(input, i));
		if (a % 2 == 0) {
			nums.even++;
		}
		else if (a % 2 != 0) {
			nums.odd++;
		}
	}


	if (nums.even == 0) {
		if (smurf.get_type() == "odd") { return "smurf\n"; }
		if (normal.get_type() == "odd") { return "normal\n"; }
		if (neptun.get_type() == "odd") { return "netpune\n"; }
	}
	else if (nums.odd == 0) {
		if (smurf.get_type() == "even") { return "smurf\n"; }
		if (normal.get_type() == "even") { return "normal\n"; }
		if (neptun.get_type() == "even") { return "netpune\n"; }
	}
	else {
		if (smurf.get_type() == "mix") { return "smurf\n"; }
		if (normal.get_type() == "mix") { return "normal\n"; }
		if (neptun.get_type() == "mix") { return "netpune\n"; }
	}
}

std::string PNN::get_data(std::string data, int i) {
	int sep = 0;
	std::string temp;
	for (int j = 0; j < data.length(); j++) {
		if (data[j] == ';') { sep++; continue; }
		if (sep > i) {
			return temp;
		}
		if (sep == i) {
			temp = temp + data[j];
		}
	}
	return temp;
}

int PNN::compare(data_t one, data_t two) {
	int comp = 0;
	if (one.connect != two.connect || one.connect2 != two.connect2) { return 0; }
	comp = comp + 2;

	auto One = one.nums.begin();
	while(1){
		if (One == one.nums.end()) { break; }
		auto Two = two.nums.begin();
		while(1){
			if (Two == two.nums.end()) { break; }
			if (*One == *Two) {
				comp++;
				One = one.nums.erase(One);
				Two = two.nums.erase(Two);
				break;
			}
			if (Two == two.nums.end()) { break; }
			Two++;
		}
		if (One == one.nums.end()) { break; }
		One++;
	}
	return comp;
}