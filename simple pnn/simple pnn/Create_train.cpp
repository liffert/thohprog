#include "Create_train.h"
#include <ctime>

void Create_train::start() {
	srand(time(NULL));
	std::ofstream file(path);
	if (!file.is_open()) {
		std::cout << "File error\n";
		return;
	}
	std::string connect[] = { "tcp;http;", "tcp;private;", "imcp;ecr_i;"};
	std::string atack[] = { "normal;", "smurf;", "neptune;" };
	int conn;
	int num;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 15000; j++) {
			
			conn = rand() % 3;
			file << connect[conn];
			for (int k = 0; k < 5; k++) {
				num = rand() %101;
				file << num;
				file << ";";
			}
			file << atack[i] << "\n";
		}
	}

	file.close();
}


void Create_train::start2() {
	srand(time(NULL));
	std::ofstream file(path2);
	if (!file.is_open()) {
		std::cout << "File error\n";
		return;
	}
	std::string connect[] = { "tcp;http;", "tcp;private;", "imcp;ecr_i;" };
	std::string atack[] = { "normal;", "smurf;", "neptune;" };
	int conn;
	int num;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 15000; j++) {

			conn = rand() % 3;
			file << connect[conn];
			switch (i) {
			case 0:
				for (int k = 0; k < 5; k++) {
					num = rand() % 101;
					file << num;
					file << ";";
				}
				break;
			case 1:
				for (int k = 0; k < 5; k++) {
					num = rand() % 101;
					if (num % 2 != 0) { num++; }
					file << num;
					file << ";";
				}
				break;
			case 2:
				for (int k = 0; k < 5; k++) {
					num = rand() % 101;
					if (num % 2 == 0) { num++; }
					file << num;
					file << ";";
				}
				break;
			}
			file << atack[i] << "\n";
		}
	}

	file.close();
}
