#include <iostream>
#include "Iterator.h"
#include "CFile.h"
#include "List.h"

List<CFile> files;
List<CFile> deleted_files;

void del(const std::string line) {
	List<CFile>::iterator it = files.begin();
	for (it; it != files.end(); it++) {
		if (!strcmp((*it).data.get_filename(), line.c_str())) {
			files.splice(it, deleted_files);
			break;
		}
	}
}
void res(const std::string line) {
	List<CFile>::iterator it = deleted_files.begin();
	for (it; it != deleted_files.end(); it++) {
		if (!strcmp((*it).data.get_filename(), line.c_str())) {
			deleted_files.splice(it, files);
			break;
		}
	}
}
void del_b_day(const std::string line) {
	List<CFile>::iterator it = files.begin();
	List<CFile>::iterator backup;
	while(it != files.end()){
		if ((*it).data.before_date(line)) {
			backup = (*it).next;
			files.splice(it, deleted_files);
			it = backup;
		}
		else {
			it++;
		}
	}
}
void renamee(const std::string name, const std::string new_name) {
	List<CFile>::iterator it = files.begin();
	for (it; it != files.end(); it++) {
		if (!strcmp((*it).data.get_filename(), name.c_str())) {
			(*it).data.rename(new_name);
		}
	}
}
void addFile(std::string line) {
	CFile file(line);
	files.push_front(file);
}
int main() {
	files.load("CFile.csv");
	std::cout << "Print list loaded from file\n";
	files.Print();
	std::cout << "\nAdd new file --  wo.cpp;13.07.2017;700\n";
	addFile("wo.cpp;13.07.2017;700");
	files.Print();
	std::cout << "\nRename file --  wander.cpp -- to -- Wander Frosty.cpp\n";
	renamee("wander.cpp", "Wander Frosty.cpp");
	files.Print();
	std::cout << "\nDelete file wo.cpp\n";
	del("wo.cpp");
	files.Print();
	std::cout << "\nRestor wo.cpp file\n";
	res("wo.cpp");
	files.Print();
	std::cout << "\nDelete before date -- 24.01.2017\n";
	del_b_day("24.01.2017");
	files.Print();
	std::cout << "\nClear\n";
	files.clear();
	files.Print();
}