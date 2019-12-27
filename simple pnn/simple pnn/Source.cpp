#include "Header.h"
#include "Create_train.h"
#include "PNN.h"
#include "Menu.h"
#include <string>

void func(){}
int main() {
	//Create_train train;
	//train.start2();
	PNN temp("train2.txt");
	//temp.train();
	temp.train2();


	std::string data;
	Menu main;
	main.set_ask();
	main.set_headline("Input:");
	main.set_func(&func, "tcp http");
	main.set_func(&func, "tcp private");
	main.set_func(&func, "imcp ecr_i");

	switch (main.start()) {
	case 1: data = data + "tcp;http;"; break;
	case 2: data = data + "tcp;private;"; break;
	case 3: data = data + "imcp;ecr_i;"; break;
	}

	for (int i = 0; i < 5; i++) {
		int d;
		//std::cout << "Input num less than 100 [" << i << "]: ";
		std::cout << "Input num [" << i << "]: ";
		std::cin >> d;
		CIN_ELIMINATION_ERROR(false);
		/*if (d > 100) {
			int d_t = 0;
			while (d - d_t > 100) {
				d_t++;
			}
			d = d - d_t * 2;
			if (d < 0) {
				d = rand() % 101;
			}
			std::cout << "Your input bigger then 100 new num: " << d << std::endl;
		}*/
		data = data + std::to_string(d) + ";";
	}
	std::cout << temp.get_atack2(data);

	system("pause");
}