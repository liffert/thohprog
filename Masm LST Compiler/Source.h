#include "Command.h"
class M {
public:

	void I_word(std::string word);
	void N_word(std::string word);
	void treatment(std::string line);
	void control(const std::string path);
	void clear_syn();
	M();
	~M();
private:
	void print_line_num();
	Command example;
	std::string path;
	int counter = 1;
	struct quantity {
		const int instraction = 9;
		const int directive = 3;
		const int regist = 15;
		const int type = 3;
		const int S_R = 2;
	}; quantity N;
	struct struct_s {
		int F_operand_index = NULL;
		bool F_operand_flag = true;
		int S_operand_index = NULL;
		bool stock_state = true;
	};struct_s syn;
	int line_num = 0;
};