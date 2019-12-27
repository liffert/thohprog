#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <vector>
#include "Hex.h"
using namespace std;
bool entry_2 = false;

ofstream file;
string com[] = { "INC","DEC","ADD", "CLI", "CMP", "AND", "MOV", "OR", "JBE", "DB", "DD", "DW", "PUSH" };
string reg[] = { "AL", "AH", "BL", "BH", "DL", "DH", "CL", "CH", "EAX", "ECX", "EBX", "EDX", "ESI", "EDI", "EBP"};
string dir[] = { "SEGMENT", "END", "ENDS", "EQU", "IF", "ELSE", "ENDIF" };
string pre[] = { "WORD", "PTR", "BYTE", "DWORD" };
int IF = 0;

struct id {
	string name;
	int offset;
	int EQU;
	int addr = -1;
	bool segment = false;
	bool code = false;
	bool dw = false;
	bool db = false;
	bool dd = false;
	bool text = false;
};
vector <id> ID;
bool v_reg(string name) {
	for (int i = 0; i < 8; i++) {
		if (reg[i] == name) {
			return true;
		}
	}
	return false;
}
bool  t_reg(string name) {
	for (int i = 8; i < 15; i++) {
		if (reg[i] == name) {
			return true;
		}
	}
	return false;
}
void regE(string name) {
	for (int i = 0; i < 15; i++) {
		if (name == reg[i]) {
			return;
		}
	}
	::cout << "\tERROR\n";
	file << "\tERROR\n";
}

struct c{
	string com;
	string F;
	string S;
	bool flag = true;
	int offset = 0;
}; c command;

void clear() {
	command.com.clear();
	command.F.clear();
	command.S.clear();
	command.flag = true;
}
void E_A(string ad) {
	string temp;
	for (int i = 0; i < ad.length(); i++) {
		if (ad[i] != ' ' && ad[i] != '+') {
			temp += ad[i];
		}
		else {
			if (!t_reg(temp)) {
				::cout << "\tERROR\n";
			}
			temp.clear();
		}
	}
	if (!t_reg(temp)) {
		::cout << "\tERROR\n";
	}
}
string operand(string word, bool &db, bool &dw, bool &dd, bool &es, bool &code, int &add, bool &text) {
	string temp;
	for (int i = 0; i < ID.size(); i++) {
		if (ID[i].name == word) {
			if (ID[i].db) {
				db = ID[i].db;
			}
			else if (ID[i].dw) {
				dw = ID[i].dw;
			}
			else if (ID[i].dd) {
				dd = ID[i].dd;
			}
			if (ID[i].code) {
				code = true;
			}
			add = ID[i].addr;
			text = ID[i].text;
			return "0";
		}
	}
	temp += word[0] + word[1] + word[2];
	if (temp == "ES:") {
		es = true;
		temp.clear();
		for (int i = 3; i < word.length(); i++) {
			temp += word[i];
		}
		for (int i = 0; i < ID.size(); i++) {
			if (ID[i].name == word) {
				if (ID[i].db) {
					db = ID[i].db;
				}
				else if (ID[i].dw) {
					dw = ID[i].dw;
				}
				else if (ID[i].dd) {
					dd = ID[i].dd;
				}
				if (ID[i].code) {
					code = true;
				}
				text = ID[i].text;
				add = ID[i].addr;
				return "0";
			}
		}
	}
	temp.clear();
	string addres;
	for (int i = 0; i < word.length(); i++) {
		if (word[i] != ' ' && word[i] != ':') {
			if (word[i] == '[') {
				i++;
				while (word[i] != ']' && i < word.length()) {
					temp += word[i];
					i++;
				}
				addres = temp;
				temp.clear();
			}
			else {
				temp += word[i];
			}
		}
		else {
			if (temp == "WORD") {
				dw = true;
			}
			if (temp == "DWORD") {
				dd = true;
			}
			if (temp == "BYTE") {
				db = true;
			}
			if (temp == "ES" || temp == "DS") {
				es = true;
			}
			temp.clear();
		}
	}
	E_A(addres);
	return addres;
}
struct modrm {
	string name;
	string mod;
	string reg;
	string rm;
};
vector <modrm> MODRM;
void create_hash_table(std::string name, std::string mod, std::string rm, std::string reg) {
	struct modrm temp;
	temp.mod = mod;
	temp.name = name;
	temp.reg = reg;
	temp.rm = rm;
	MODRM.push_back(temp);
}
string mod(string name) {
	for (int i = 0; i < MODRM.size(); i++) {
		if (MODRM[i].name == name) {
			return MODRM[i].mod;
		}
	}
	return "0";
}
string rm_reg(string name) {
	for (int i = 0; i < MODRM.size(); i++) {
		if (MODRM[i].name == name) {
			return MODRM[i].reg;
		}
	}
	return "0";
}
string rm(string name) {
	for (int i = 0; i < MODRM.size(); i++) {
		if (MODRM[i].name == name) {
			return MODRM[i].rm;
		}
	}
	return "0";
}

int r(string word) {
	string temp;
	int a = 0;
	for (int i = 0; i < word.length(); i++) {
		if (word[i] != ' ' && word[i] != ':') {
			if (word[i] == '[') {
				a++;
				return a;
			}
			temp += word[i];
		}
		else {
			if (temp == "WORD") {
				a = a + 2;
			}
			if (temp == "DWORD") {
				a++;
			}
			if (temp == "BYTE") {
				a++;
			}
			if (temp == "ES" || temp == "DS") {
				a++;
			}
			temp.clear();
		}
	}
	return a;
}
void push() {
	/*::cout << "\tERROR\n";
	return;*/
	Hex s;
	bool dd = false;
	bool dw = false;
	bool db = false;
	bool es = false;
	bool code = false;
	bool text = false;
	int addres;
	if (entry_2) {
		::cout << s.conv(command.offset, 4) << "\t";
		file << s.conv(command.offset, 4) << "\t";
		string mem = operand(command.F, db, dw, dd, es, code, addres, text);
		if (code) {
			::cout << "2E: ";
			file << "2E: ";
		}
		if (es) {
			::cout << "26: ";
			file << "26: ";
		}
		if (db) {
			::cout << "\tERROR\n";
			file << "\tERROR\n";
			return;
		}
		if (dw) {
			::cout << "66| FF ";
			file << "66| FF ";
		}
		if (dd) {
			::cout << "FF ";
			file << "FF ";
		}
		if (mem != "0") {
			string mod;
			string temp2;
			string temp;
			int j = 0;
			for (int i = 0; i < mem.length(); i++) {
				if (mem[i] != ' ' && mem[i] != '+') {
					temp += mem[i];
				}
				else {
					if (!temp.empty()) {
						j = i;
						break;
					}
				}
			}
			temp2 = temp;
			temp.clear();
			for (int i = j; i < mem.length(); i++) {
				if (mem[i] != ' ' && mem[i] != '+') {
					temp += mem[i];
				}
				else {
					if (!temp.empty()) {
						break;
					}
				}
			}
			mod += "00" + ::rm(temp) + rm_reg(temp2) + "B";
			::cout << "34 " << s.conv_string(mod) << "\t";
			file << "34 " << s.conv_string(mod) << "\t";
		}
		else {
			::cout << "35 " << s.conv(addres, 4) << "r\t";
			file << "35 " << s.conv(addres, 4) << "r\t";
		}
	}
	int a = 0;
	for (int i = 0; i < ID.size(); i++) {
		if (ID[i].name == command.F) {
			a = ID[i].offset;
			break;
		}
	}
	if (a == 0) {
		command.offset += 1 + r(command.F);
	}
	else {
		command.offset += 2 + a;
		if (dw) {
			command.offset++;
		}
		if (db) {
			if (text) {
				command.offset -= 2;
			}
		}
	}
}
void directive() {
	Hex s;
	if (IF >= 0) {
		if (entry_2) {
			::cout << s.conv(command.offset, 4) << "\t";
			file << s.conv(command.offset, 4) << "\t";
		}
	}
	struct id temp;
	if (command.com == "SEGMENT") {
		temp.name = command.F;
		temp.segment = true;
		if (!entry_2) {
			ID.push_back(temp);
		}
	}
	else if (command.com == "EQU") {
		temp.name = command.F;
		if (entry_2) {
			::cout << "=" << s.conv(atoi(command.S.c_str()), 4) << "\t";
			file << "=" << s.conv(atoi(command.S.c_str()), 4) << "\t";
		}
		else {
			temp.EQU = atoi(command.S.c_str());
			if (!entry_2) {
				ID.push_back(temp);
			}
		}
	}
	else if (command.com == "ENDS") {
		command.offset = 0;
	}
	else if (command.com == "IF") {
		int a = 0;
		for (int i = 0; i < ID.size(); i++) {
			if (command.F == ID[i].name) {
				a = ID[i].EQU;
			}
		}
		if (a != 0) {
			IF = 1;
		}
		else {
			IF = -1;
		}
	}
	else if (command.com == "ELSE") {
		if (IF == -1) {
			IF = 0;
		}
		else if (IF == 1) {
			IF = -1;
		}
	}
	else if (command.com == "ENDIF") {
		IF = 0;
	}
}
void inc() {
	Hex s;
	regE(command.F);
	if (entry_2) {
		::cout << s.conv(command.offset, 4) << "\t";
		file << s.conv(command.offset, 4) << "\t";
		if (v_reg(command.F)) {
			string temp;
			temp += mod(command.F) + rm_reg("AL") + rm(command.F) + "B";
			::cout << "FE " << s.conv_string(temp) << "\t";
			file << "FE " << s.conv_string(temp) << "\t";
		}
		else if (t_reg(command.F)) {
			int a = 64;
			if (command.F == "EAX") {
				a = a + 0;
				::cout << s.conv(a);
			}
			if (command.F == "ECX") {
				a = a + 1;
				::cout << s.conv(a);
			}
			if (command.F == "EDX") {
				a = a + 2;
				::cout << s.conv(a);
			}
			if (command.F == "EBX") {
				a = a + 3;
				::cout << s.conv(a);
			}
			if (command.F == "EBP") {
				a = a + 5;
				::cout << s.conv(a);
			}
			if (command.F == "ESI") {
				a = a + 6;
				::cout << s.conv(a);
			}
			if (command.F == "EDI") {
				a = a + 7;
				::cout << s.conv(a);
			}
		}
		else {
			::cout << "ERROR\t";
			file << "ERROR\t";
		}
		::cout << "\t";
	}
	command.offset += 2;
}
void dec() {
	Hex s;
	bool dd = false;
	bool dw = false;
	bool db = false;
	bool es = false;
	bool code = false;
	bool text = false;
	int addres;
	if (entry_2) {
		::cout << s.conv(command.offset, 4) << "\t";
		file << s.conv(command.offset, 4) << "\t";
		string mem = operand(command.F, db, dw, dd, es, code, addres, text);
		if (code) {
			::cout << "2E: ";
			file << "2E: ";
		}
		if (es) {
			::cout << "26: ";
			file << "26: ";
		}
		if (db) {
			::cout << "FE ";
			file << "FE ";
		}
		if (dw) {
			::cout << "66| FF ";
			file << "66| FF ";
		}
		if (dd) {
			::cout << "FF ";
			file << "FF ";
		}
		if (mem != "0") {
			string mod;
			string temp2;
			string temp;
			int j = 0;
			for (int i = 0; i < mem.length(); i++) {
				if (mem[i] != ' ' && mem[i] != '+') {
					temp += mem[i];
				}
				else {
					if (!temp.empty()) {
						j = i;
						break;
					}
				}
			}
			temp2 = temp;
			temp.clear();
			for (int i = j; i < mem.length(); i++) {
				if (mem[i] != ' ' && mem[i] != '+') {
					temp += mem[i];
				}
				else {
					if (!temp.empty()) {
						break;
					}
				}
			}
			mod += "00" + ::rm(temp) + rm_reg(temp2) + "B";
			::cout << "0C " << s.conv_string(mod) << "\t";
			file << "0C " << s.conv_string(mod) << "\t";
		}
		else {
			::cout << "0D " << s.conv(addres, 4) << "r\t";
			file << "0D " << s.conv(addres, 4) << "r\t";
		}
	}
	int a = 0;
	for (int i = 0; i < ID.size(); i++) {
		if (ID[i].name == command.F) {
			a = ID[i].offset;
			break;
		}
	}
	if (a == 0) {
		command.offset += 1 + r(command.F);
	}
	else {
		command.offset += 2 + a;
		if (dw) {
			command.offset++;
		}
		if (db) {
			if (text) {
				command.offset -= 2;
			}
		}
	}
}
void add() {
	Hex s;
	if (entry_2) {
		::cout << s.conv(command.offset, 4) << "\t";
		file << s.conv(command.offset, 4) << "\t";
		if (v_reg(command.F) && v_reg(command.S)) {
			string temp;
			temp += mod(command.S) + rm_reg(command.F) + rm(command.S) + "B";
			::cout << "02 " << s.conv_string(temp) << "\t";
			file << "02 " << s.conv_string(temp) << "\t";
		}
		else if (t_reg(command.F) && t_reg(command.S)) {
			string temp;
			temp += mod(command.S) + rm_reg(command.F) + rm(command.S) + "B";
			::cout << "03 " << s.conv_string(temp) << "\t";
			file << "03 " << s.conv_string(temp) << "\t";
		}
		else {
			::cout << "\tERROR\n";
		}
	}
	command.offset += 2;
}
void cli() {
	Hex s;
	if (entry_2) {
		::cout << s.conv(command.offset, 4) << "\t" << "FA\t";
		file << s.conv(command.offset, 4) << "\t" << "FA\t";
	}
	command.offset++;
}
void cmp() {
	Hex s;
	bool dd = false;
	bool dw = false;
	bool db = false;
	bool es = false;
	bool code = false;
	bool text = false;
	int addres;
	regE(command.F);
	if (entry_2) {
		::cout << s.conv(command.offset, 4) << "\t";
		file << s.conv(command.offset, 4) << "\t";
		string mem = operand(command.S, db, dw, dd, es, code, addres, text);
		if (code) {
			::cout << "2E: ";
			file << "2E: ";
		}
		if (es) {
			::cout << "26: ";
			file << "26: ";
		}
		if (dw) {
			::cout << "ERROR\t";
			file << "ERROR\t";
		}
		if (mem != "0") {
			string mod;
			string temp2;
			string temp;
			int j = 0;
			for (int i = 0; i < mem.length(); i++) {
				if (mem[i] != ' ' && mem[i] != '+') {
					temp += mem[i];
				}
				else {
					if (!temp.empty()) {
						j = i;
						break;
					}
				}
			}
			temp2 = temp;
			temp.clear();
			for (int i = j; i < mem.length(); i++) {
				if (mem[i] != ' ' && mem[i] != '+') {
					temp += mem[i];
				}
				else {
					if (!temp.empty()) {
						break;
					}
				}
			}
			mod += "00" + ::rm(temp) + rm_reg(temp2) + "B";
			string mod2;
			mod2 += ::mod("[][]") + rm_reg(command.F) + rm("[][]") + "B";
			if (v_reg(command.F)) {
				::cout << "3A " << s.conv_string(mod2) << " " << s.conv_string(mod) << "\t";
				file << "3A " << s.conv_string(mod2) << " " << s.conv_string(mod) << "\t";
			}
			else {
				::cout << "3B " << s.conv_string(mod2) << " " << s.conv_string(mod) << "\t";
				file << "3B " << s.conv_string(mod2) << " " << s.conv_string(mod) << "\t";
			}
		}
		else {
			if (v_reg(command.F)) {
				::cout << "3A ";
				file << "3A ";
				string mod;
				mod += ::mod("disp32") + rm_reg(command.F) + rm("disp32") + "B";
				::cout << s.conv_string(mod) << " ";
				file << s.conv_string(mod) << " ";
				::cout << s.conv(addres, 4) << "r\t";
				file << s.conv(addres, 4) << "r\t";
			}
			else {
				::cout << "3B ";
				file << "3B ";
				string mod;
				mod += ::mod("disp32") + rm_reg(command.F) + rm("disp32") + "B";
				::cout << s.conv_string(mod) << " ";
				file << s.conv_string(mod) << " ";
				::cout << s.conv(addres, 4) << "r\t";
				file << s.conv(addres, 4) << "r\t";
			}
			
		}
	}
	int a = 0;
	for (int i = 0; i < ID.size(); i++) {
		if (ID[i].name == command.S) {
			a = ID[i].offset;
			break;
		}
	}
	if (a == 0) {
		command.offset += 2 + r(command.S);
	}
	else {
		command.offset += 2 + a;
	}
}
void anD() {
	Hex s;
	bool dd = false;
	bool dw = false;
	bool db = false;
	bool es = false;
	bool code = false;
	bool text = false;
	int addres;
	regE(command.S);
	if (entry_2) {
		::cout << s.conv(command.offset, 4) << "\t";
		file << s.conv(command.offset, 4) << "\t";
		string mem = operand(command.F, db, dw, dd, es, code, addres, text);
		if (code) {
			::cout << "2E: ";
			file << "2E: ";
		}
		if (es) {
			::cout << "26: ";
			file << "26: ";
		}
		if (dw) {
			::cout << "ERROR\t";
			file << "ERROR\t";
		}
		if (mem != "0") {
			string mod;
			string temp2;
			string temp;
			int j = 0;
			for (int i = 0; i < mem.length(); i++) {
				if (mem[i] != ' ' && mem[i] != '+') {
					temp += mem[i];
				}
				else {
					if (!temp.empty()) {
						j = i;
						break;
					}
				}
			}
			temp2 = temp;
			temp.clear();
			for (int i = j; i < mem.length(); i++) {
				if (mem[i] != ' ' && mem[i] != '+') {
					temp += mem[i];
				}
				else {
					if (!temp.empty()) {
						break;
					}
				}
			}
			mod += "00" + ::rm(temp) + rm_reg(temp2) + "B";
			string mod2;
			mod2 += ::mod("[][]") + rm_reg(command.S) + rm("[][]") + "B";
			if (v_reg(command.S)) {
				::cout << "20 " << s.conv_string(mod2) << " " << s.conv_string(mod) << "\t";
				file << "20 " << s.conv_string(mod2) << " " << s.conv_string(mod) << "\t";
			}
			else {
				::cout << "21 " << s.conv_string(mod2) << " " << s.conv_string(mod) << "\t";
				file << "21 " << s.conv_string(mod2) << " " << s.conv_string(mod) << "\t";
			}
		}
		else {
			if (v_reg(command.S)) {
				::cout << "20 ";
				file << "20 ";
				string mod;
				mod += ::mod("disp32") + rm_reg(command.S) + rm("disp32") + "B";
				::cout << s.conv_string(mod) << " ";
				file << s.conv_string(mod) << " ";
				::cout << s.conv(addres, 4) << "r\t";
				file << s.conv(addres, 4) << "r\t";
			}
			else {
				::cout << "21 ";
				file << "21 ";
				string mod;
				mod += ::mod("disp32") + rm_reg(command.S) + rm("disp32") + "B";
				::cout << s.conv_string(mod) << " ";
				file << s.conv_string(mod) << " ";
				::cout << s.conv(addres, 4) << "r\t";
				file << s.conv(addres, 4) << "r\t";
			}

		}
	}
	int a = 0;
	for (int i = 0; i < ID.size(); i++) {
		if (ID[i].name == command.F) {
			a = ID[i].offset;
		}
	}
	if (a == 0) {
		command.offset += r(command.F) + 2;
	}
	else {
		if (text) {
			command.offset -= 2;
		}
		command.offset += a + 2;
	}
}
void mov() {
	Hex s;
	bool dd = false;
	bool dw = false;
	bool db = false;
	bool es = false;
	bool code = false;
	bool text = false;
	int addres;
	if (entry_2) {
		::cout << s.conv(command.offset, 4) << "\t";
		file << s.conv(command.offset, 4) << "\t";
		if (v_reg(command.F) || t_reg(command.F)) {
			int a = 184;
			if (command.F == "EAX") {
				a = a + 0;
				::cout << s.conv(a) << "\t";
			}
			if (command.F == "ECX") {
				a = a + 1;
				::cout << s.conv(a) << "\t";
			}
			if (command.F == "EDX") {
				a = a + 2;
				::cout << s.conv(a) << "\t";
			}
			if (command.F == "EBX") {
				a = a + 3;
				::cout << s.conv(a) << "\t";
			}
			if (command.F == "EBP") {
				a = a + 5;
				::cout << s.conv(a) << "\t";
			}
			if (command.F == "ESI") {
				a = a + 6;
				::cout << s.conv(a) << "\t";
			}
			if (command.F == "EDI") {
				a = a + 7;
				::cout << s.conv(a) << "\t";
			}
			a = 176;
			if (command.F == "AL") {
				a = a + 0;
				::cout << s.conv(a) << "\t";
			}
			if (command.F == "BL") {
				a = a + 3;
				::cout << s.conv(a) << "\t";
			}
			if (command.F == "CL") {
				a = a + 1;
				::cout << s.conv(a) << "\t";
			}
			if (command.F == "DL") {
				a = a + 2;
				::cout << s.conv(a) << "\t";
			}
			if (command.F == "AH") {
				a = a + 4;
				::cout << s.conv(a) << "\t";
			}
			if (command.F == "BH") {
				a = a + 7;
				::cout << s.conv(a) << "\t";
			}
			if (command.F == "CH") {
				a = a + 5;
				::cout << s.conv(a) << "\t";
			}
			if (command.F == "DH") {
				a = a + 6;
				::cout << s.conv(a) << "\t";
			}
			bool f_equ = false;
			for (int i = 0; i < ID.size(); i++) {
				if (ID[i].name == command.S) {
					::cout << s.conv(ID[i].EQU) << "\t";
					file << s.conv(ID[i].EQU) << "\t";
					f_equ = true;
				}
			}
			if (!f_equ) {
				::cout << s.conv_string(command.S) << "\t";
				file << s.conv_string(command.S) << "\t";
			}
		}
		else {
			string mem = operand(command.F, db, dw, dd, es, code, addres, text);
			if (code) {
				::cout << "2E: ";
				file << "2E: ";
			}
			if (es) {
				::cout << "26: ";
				file << "26: ";
			}
			if (dw) {
				::cout << "66| C7 ";
				file << "66| C7 ";
			}
			if (dd) {
				::cout << "C7 ";
				file << "C7 ";
			}
			if (db) {
				::cout << "C6 ";
				file << "C6 ";
			}
			if (mem != "0") {
				string mod;
				string temp2;
				string temp;
				int j = 0;
				for (int i = 0; i < mem.length(); i++) {
					if (mem[i] != ' ' && mem[i] != '+') {
						temp += mem[i];
					}
					else {
						if (!temp.empty()) {
							j = i;
							break;
						}
					}
				}
				temp2 = temp;
				temp.clear();
				for (int i = j; i < mem.length(); i++) {
					if (mem[i] != ' ' && mem[i] != '+') {
						temp += mem[i];
					}
					else {
						if (!temp.empty()) {
							break;
						}
					}
				}
				mod += "00" + ::rm(temp) + rm_reg(temp2) + "B";
				string mod2;
				mod2 += ::mod("[][]") + rm_reg("EAX") + rm("[][]") + "B";
				::cout << s.conv_string(mod2) << " " << s.conv_string(mod) << "\t";
				file << s.conv_string(mod2) << " " << s.conv_string(mod) << "\t";
				bool f_equ = false;
				for (int i = 0; i < ID.size(); i++) {
					if (ID[i].name == command.S) {
						::cout << s.conv(ID[i].EQU) << "\t";
						file << s.conv(ID[i].EQU) << "\t";
						f_equ = true;
					}
				}
				if (!f_equ) {
					::cout << s.conv_string(command.S) << "\t";
					file << s.conv_string(command.S) << "\t";
				}
			}
			else {
				string mod;
				mod += ::mod("disp32") + rm_reg("EAX") + rm("disp32") + "B";
				::cout << s.conv_string(mod) << " ";
				file << s.conv_string(mod) << " ";
				::cout << s.conv(addres, 4) << "r\t";
				file << s.conv(addres, 4) << "r\t";
				bool f_equ = false;
				for (int i = 0; i < ID.size(); i++) {
					if (ID[i].name == command.S) {
						::cout << s.conv(ID[i].EQU) << "\t";
						file << s.conv(ID[i].EQU) << "\t";
						f_equ = true;
					}
				}
				if (!f_equ) {
					::cout << s.conv_string(command.S) << "\t";
					file << s.conv_string(command.S) << "\t";
				}
			}
		}
	}
	if (v_reg(command.F) || t_reg(command.F)) {
		if (v_reg(command.F)) {
			command.offset += 2;
		}
		else {
			command.offset += 5;
		}
	}
	else {
		int a = 0;
		for (int i = 0; i < ID.size(); i++) {
			if (ID[i].name == command.F) {
				a = ID[i].offset;
				command.offset += a + 2;
				if (ID[i].db) {
					command.offset++;
				}
				if (ID[i].dd) {
					command.offset += 4;
				}
				if (ID[i].text) {
					command.offset -= 2;
				}
				return;
			}
		}
		string buf;
		for (int i = 3; i < command.F.length(); i++) {
			buf += command.F[i];
		}
		for (int i = 0; i < ID.size(); i++) {
			if (ID[i].name == buf) {
				a = ID[i].offset;
				command.offset += a + 3;
				if (ID[i].db) {
					command.offset++;
					command.offset++;
				}
				if (ID[i].dd) {
					command.offset += 5;
				}
				if (ID[i].text) {
					command.offset -= 1;
				}
				return;
			}
		}
		a = r(command.F);
		command.offset += a + 2;
		if (dw) {
			command.offset++;
		}
		if (dd) {
			command.offset += 3;
		}
	}
}
void oR() {
	Hex s;
	bool dd = false;
	bool dw = false;
	bool db = false;
	bool es = false;
	bool code = false;
	bool text = false;
	int addres;
	if (entry_2) {
		::cout << s.conv(command.offset, 4) << "\t";
		file << s.conv(command.offset, 4) << "\t";
		string mem = operand(command.F, db, dw, dd, es, code, addres, text);
		if (code) {
			::cout << "2E: ";
			file << "2E: ";
		}
		if (es) {
			::cout << "26: ";
			file << "26: ";
		}
		if (dw) {
			::cout << "66| 81 ";
			file << "66| 81 ";
		}
		if (mem != "0") {
			string mod;
			string temp2;
			string temp;
			int j = 0;
			for (int i = 0; i < mem.length(); i++) {
				if (mem[i] != ' ' && mem[i] != '+') {
					temp += mem[i];
				}
				else {
					if (!temp.empty()) {
						j = i;
						break;
					}
				}
			}
			temp2 = temp;
			temp.clear();
			for (int i = j; i < mem.length(); i++) {
				if (mem[i] != ' ' && mem[i] != '+') {
					temp += mem[i];
				}
				else {
					if (!temp.empty()) {
						break;
					}
				}
			}
			mod += "00" + ::rm(temp) + rm_reg(temp2) + "B";
			string mod2;
			mod2 += ::mod("[][]") + rm_reg("ECX") + rm("[][]") + "B";
			if (!dw) {
				::cout << "83 " << s.conv_string(mod2) << " " << s.conv_string(mod) << "\t";
				file << "83 " << s.conv_string(mod2) << " " << s.conv_string(mod) << "\t";
			}
			else {
				::cout  << s.conv_string(mod2) << " " << s.conv_string(mod) << "\t";
				file  << s.conv_string(mod2) << " " << s.conv_string(mod) << "\t";
			}
			bool f_equ = false;
			for (int i = 0; i < ID.size(); i++) {
				if (ID[i].name == command.S) {
					::cout << s.conv(ID[i].EQU) << "\t";
					file << s.conv(ID[i].EQU) << "\t";
					f_equ = true;
				}
			}
			if (!f_equ) {
				::cout << s.conv_string(command.S) << "\t";
				file << s.conv_string(command.S) << "\t";
			}
		}
		else {
			if (!dw) {
				::cout << "80 ";
				file << "80 ";
			}
			string mod;
			mod += ::mod("disp32") + rm_reg("ECX") + rm("disp32") + "B";
			::cout << s.conv_string(mod) << " ";
			file << s.conv_string(mod) << " ";
			::cout << s.conv(addres, 4) << "r\t";
			file << s.conv(addres, 4) << "r\t";
			bool f_equ = false;
			for (int i = 0; i < ID.size(); i++) {
				if (ID[i].name == command.S) {
					::cout << s.conv(ID[i].EQU) << "\t";
					file << s.conv(ID[i].EQU) << "\t";
					f_equ = true;
				}
			}
			if (!f_equ) {
				::cout << s.conv_string(command.S) << "\t";
				file << s.conv_string(command.S) << "\t";
			}
		}
	}
	int a = 0;
	for (int i = 0; i < ID.size(); i++) {
		if (ID[i].name == command.F) {
			a = ID[i].offset;
		}
	}
	if (a == 0) {
		for (int i = 0; i < ID.size(); i++) {
			if (ID[i].name == command.S) {
				command.offset += 2 + r(command.F);
				return;
			}
		}
		command.offset += 3 + r(command.F);
	}
	else {
		for (int i = 0; i < ID.size(); i++) {
			if (ID[i].name == command.S) {
				command.offset += a + 2;
				return;
			}
		}
		command.offset += a + 3;
	}
}
void jbe() {
	Hex s;
	if (entry_2) {
		::cout << s.conv(command.offset, 4) << "\t76 ";
		file << s.conv(command.offset, 4) << "\t76 ";
		bool error_flag = true;
		for (int i = 0; i < ID.size(); i++) {
			if (ID[i].name == command.F) {
				error_flag = false;
			}
		}
		if (error_flag) {
			::cout << "\tERROR\n";
			file << "\tERROR\n";
		}
		else {
			for (int i = 0; i < ID.size(); i++) {
				if (ID[i].name == command.F) {
					if (ID[i].addr > command.offset) {
						::cout << s.conv(ID[i].addr - command.offset - 2) << " 90 90 90 90 ";
						file << s.conv(ID[i].addr - command.offset - 2) << " 90 90 90 90 ";
						command.offset += 6;
					}
					else {
						::cout << s.conv(256 - (ID[i].addr + command.offset)) << " ";
						file << s.conv(256 - (ID[i].addr + command.offset)) << " ";
						command.offset += 2;
					}
					return;
				}
			}
		}
	}
	else {
		for (int i = 0; i < ID.size(); i++) {
			if (ID[i].name == command.F) {
				command.offset += 2;
				return;
			}
		}
		command.offset += 6;
	}
}
void db() {
	Hex s;
	struct id temp;
	temp.name = command.F;
	if (entry_2) {
		::cout << s.conv(command.offset, 4) << "\t" << s.conv_string(command.S) << " ";
		file << s.conv(command.offset, 4) << "\t" << s.conv_string(command.S) << " ";
	}
	temp.addr = command.offset;
	int a = 0;
	for (int i = 0; i < ID.size(); i++) {
		if (ID[i].segment) {
			a++;
		}
	}
	if (command.S[0] == '\'') {
		if (a == 2) {
			temp.code = true;
			temp.offset = command.S.length() - 1;
		}
		else {
			temp.offset = command.S.length() - 2;
		}
		command.offset += command.S.length() - 2;
		temp.text = true;
	}
	else {
		if (a == 2) {
			temp.code = true;
			temp.offset = 5;
		}
		else {
			temp.offset = 4;
		}
		command.offset += 1;
	}
	if (!entry_2) {
		temp.db = true;
		ID.push_back(temp);
	}
}
void dd() {
	Hex s;
	struct id temp;
	temp.name = command.F;
	temp.addr = command.offset;
	int a = 0;
	for (int i = 0; i < ID.size(); i++) {
		if (ID[i].segment) {
			a++;
		}
	}
	if (a == 2) {
		temp.code = true;
		temp.offset = 5;
	}
	else {
		temp.offset = 4;
	}
	if (entry_2) {
		::cout << s.conv(command.offset, 4) << "\t" << s.conv_string(command.S) << " ";
		file << s.conv(command.offset, 4) << "\t" << s.conv_string(command.S) << " ";
	}
	else {
		temp.dd = true;
		ID.push_back(temp);
	}
	command.offset += 4;
}
void dw() {
	Hex s;
	struct id temp;
	temp.name = command.F;
	temp.addr = command.offset;
	int a = 0;
	for (int i = 0; i < ID.size(); i++) {
		if (ID[i].segment) {
			a++;
		}
	}
	if (a == 2) {
		temp.code = true;
		temp.offset = 5;
	}
	else {
		temp.offset = 4;
	}
	if (entry_2) {
		::cout << s.conv(command.offset, 4) << "\t" << s.conv_string(command.S) << " ";
		file << s.conv(command.offset, 4) << "\t" << s.conv_string(command.S) << " ";
	}
	else {
		temp.dw = true;
		ID.push_back(temp);
	}
	command.offset += 2;
}
void control() {
	if (IF >= 0) {
		if (command.com == "DW") {
			dw();
			return;
		}
		else if (command.com == "DD") {
			dd();
			return;
		}
		else if (command.com == "DB") {
			db();
			return;
		}
		else if (command.com == "JBE") {
			jbe();
			return;
		}
		else if (command.com == "OR") {
			oR();
			return;
		}
		else if (command.com == "MOV") {
			mov();
			return;
		}
		else if (command.com == "AND") {
			anD();
			return;
		}
		else if (command.com == "CMP") {
			cmp();
			return;
		}
		else if (command.com == "CLI") {
			cli();
			return;
		}
		else if (command.com == "ADD") {
			add();
			return;
		}
		else if (command.com == "DEC") {
			dec();
			return;
		}
		else if (command.com == "INC") {
			inc();
			return;
		}
		else if (command.com == "PUSH") {
			push();
			return;
		}
	}
	for (int i = 0; i < 7; i++) {
		if (command.com == dir[i]) {
			directive();
			return;
		}
	}
	if (entry_2) {
		if (IF >= 0) {
			Hex s;
			::cout << s.conv(command.offset, 4) << "\t";
			file << s.conv(command.offset, 4) << "\t";
		}
	}
}
string UP(string line) {
	for (int i = 0; i < line.length(); i++) {
		if (line[i] != '\'') {
			line[i] = toupper(line[i]);
		}
		else {
			i++;
			while (line[i] != '\'' && i < line.length()) {
				i++;
			}
			i--;
		}
	}
	return line;
}
void word(string str) {
	if (str[str.length() - 1] == ':') {
		if ((str[0] != 'E' || str[0] != 'D') && str[1] != 'S') {
			struct id temp;
			for (int i = 0; i < str.length() - 1; i++) {
				temp.name += str[i];
			}
			temp.addr = command.offset;
			ID.push_back(temp);
		}
		else {
			if (command.flag) {
				command.F += str;
			}
			else {
				command.S += str;
			}
		}
		return;
	}
	for (int i = 0; i < 15; i++) {
		if (str == reg[i]) {
			if (command.flag) {
				command.F += str;
			}
			else {
				command.S += str;
			}
			return;
		}
		if (i < 7 && str == dir[i]) {
			if (str == "EQU") {
				command.flag = false;
			}
			command.com = str;
			return;
		}
		if (i < 13 && str == com[i]) {
			if (str == "DB" || str == "DW" || str == "DD") {
				command.flag = false;
			}
			command.com += str;
			return;
		}
		if (i < 4 && str == pre[i]) {
			if (command.flag) {
				command.F += str + " ";
			}
			else {
				command.S += str + " ";
			}
			return;
		}
	}
	if (command.flag) {
		command.F += str;
	}
	else {
		command.S += str;
	}
}
void N16(string word) {
	for (int i = 0; i < word.length() - 1; i++){
		if (!isxdigit(word[i])) {
			::cout << "ERROR\n";
			return;
		}
	}
	if (command.flag) {
		command.F += word;
	}
	else {
		command.S += word;
	}
}
void N2(string word) {
	for (int i = 0; i < word.length() - 1; i++) {
		if (word[i] != '0' && word[i] != '1') {
			::cout << "ERROR\n";
			return;
		}
	}
	if (command.flag) {
		command.F += word;
	}
	else {
		command.S += word;
	}
}
void N10(string word) {
	for (int i = 0; i < word.length(); i++) {
		if (!isdigit) {
			::cout << "ERROR\n";
			return;
		}
	}
	if (command.flag) {
		command.F += word;
	}
	else {
		command.S += word;
	}
}
void test_number(string word) {
	if (word[word.length() - 1] == 'B') {
		N2(word);
		return;
	}
	if (word[word.length() - 1] == 'H') {
		N16(word);
		return;
	}
	N10(word);
}
void analize(string line) {
	line = UP(line);
	string temp;
	for (int i = 0; i < line.length(); i++) {
		if (isspace(line[i])) {}
		else if (isalpha(line[i]) != 0) {
			for (i; i < line.length(); i++) {
				if (isalnum(line[i]) != 0) {
					temp += line[i];
				}
				else {
					if (line[i] == ':') {
						temp += ":";
					}
					else {
						i--;
					}
					break;
				}
			}
			word(temp);
			temp = "";
		}
		else if (line[i] == '\'') {
			temp += line[i];
			i++;
			while (line[i] != '\'' && i < line.length()) {
				temp += line[i];
				i++;
			}
			temp += line[i];
			if (command.flag) {
				command.F += temp;
			}
			else {
				command.S += temp;
			}
			temp = "";
		}
		else if (isdigit(line[i])) {
			for (i; i < line.length(); i++) {
				if (isxdigit(line[i])) {
					temp += line[i];
				}
				else if(line[i] == 'H') {
					temp += line[i];
					break;
				}
				else {
					i--;
					break;
				}
			}
			test_number(temp);
		}
		else {
			if (line[i] == ',') {
				command.flag = false;
			}
			else{
				if (command.flag) {
					command.F += line[i];
				}
				else {
					command.S += line[i];
				}
			}
		}
	}
}
int main() {
	bool tab = true;
	string line;
	ifstream file("test.asm");
	if (entry_2) {
		::file.open("test.lst");
	}
	while (!file.eof()) {
		getline(file, line);
		for (int i = 0; i < line.length(); i++) {
			if (isspace(line[i])) {}
			else {
				tab = false;
				break;
			}
		}
		analize(line);
		if (!tab) {
			control();
		}
		clear();
		tab = true;
		if (entry_2) {
			if (IF >= 0) {
				::cout << line << endl;
				::file << line << endl;
			}
		}
	}
	if (entry_2) {
		file.close();
	}
	if (!entry_2) {
		create_hash_table("AL", "11", "000", "000");
		create_hash_table("CL", "11", "001", "001");
		create_hash_table("DL", "11", "010", "010");
		create_hash_table("BL", "11", "011", "011");
		create_hash_table("AH", "11", "100", "100");
		create_hash_table("CH", "11", "101", "101");
		create_hash_table("DH", "11", "110", "110");
		create_hash_table("BH", "11", "111", "111");
		create_hash_table("EAX", "11", "000", "000");
		create_hash_table("ECX", "11", "001", "001");
		create_hash_table("EDX", "11", "010", "010");
		create_hash_table("EBX", "11", "011", "011");
		create_hash_table("ESI", "11", "110", "110");
		create_hash_table("EDI", "11", "111", "111");
		create_hash_table("EBP", "11", "101", "101");
		create_hash_table("[][]", "00", "100", "000");
		create_hash_table("disp32", "00", "101", "000");
		command.offset = 0;
		entry_2 = true;
		main();
	}
}