#include <vector>
#include "CTranslate.h"
#include <fstream>
#include <string>

void fill(std::vector<CTranslate> &obj) {
	std::ifstream file("word.csv");
	std::string line;
	std::getline(file, line);
	
	char eng_word[50];
	char ita_word[50];
	int count_s = 0;
	int k = 0;
	for(int i = 0; i < line.length(); i++) {
		if (line[i] != ';') {
			if (count_s == 0) {
				eng_word[k] = line[i];
				k++;
			}
			else {
				ita_word[k] = line[i];
				k++;
			}
		}
		else {
			if (count_s == 1) {
				ita_word[k] = '\0';
			}
			else {
				eng_word[k] = '\0';
			}
			count_s++;
			k = 0;
		}
		if (count_s > 1) {
			CTranslate test;
			test.MakePair(eng_word, ita_word);
			obj.push_back(test);
			count_s = 0;
		}
	}
}

void ListAll(const std::vector<CTranslate> &obj) {
	for (int i = 0; i < obj.size(); i++) {
		obj[i].Print();
	}
}

void DelByEng(std::vector<CTranslate> &obj, const char *en) {
	if (en == NULL) {
		return;
	}
	std::vector<CTranslate>::iterator i = obj.begin();
	while(i < obj.end()) {
		if (strcmp((*i).GetEng(), en) == 0) {
			i = obj.erase(i);
		}
		else {
			i++;
		}
	}
}

void DelByIta(std::vector<CTranslate> &obj, const char *it) {
	if (it == NULL) {
		return;
	}
	std::vector<CTranslate>::iterator i = obj.begin();
	while (i < obj.end()) {
		if (strcmp((*i).GetIta(), it) == 0) {
			i = obj.erase(i);
		}
		else {
			i++;
		}
	}
}

void SortByEng(std::vector<CTranslate> &obj) {
	CTranslate buff;
	for (int k = 0; k < obj.size() - 1; k++) {
		for (int i = 0; i < obj.size() - k - 1; i++) {
			if (!(obj[i] < obj[i + 1])) {
				buff = obj[i + 1];
				obj[i + 1] = obj[i];
				obj[i] = buff;
			}
		}
	}
}

void SortByIta(std::vector<CTranslate> &obj) {
	CTranslate buff;
	for (int k = 0; k < obj.size() - 1; k++) {
		for (int i = 0; i < obj.size() - k - 1; i++) {
			if (!obj[i].cmpIta_s(obj[i + 1])) {
				buff = obj[i + 1];
				obj[i + 1] = obj[i];
				obj[i] = buff;
			}
		}
	}
}

void TranslateEng(const std::vector<CTranslate> &obj, const char *en) {
	if (en == NULL) {
		return;
	}
	std::cout << "English: " << en << std::endl << "Italian: ";
	for (int i = 0; i < obj.size(); i++) {
		if ((strcmp(obj[i].GetEng(), en) == 0)) {
			if (obj[i].GetIta() != NULL) {
				std::cout << obj[i].GetIta() << " ";
			}
		}
	}
	std::cout << std::endl;
}

void TranslateIta(const std::vector<CTranslate> &obj, const char *it) {
	if (it == NULL) {
		return;
	}
	std::cout << "Italian: " << it << std::endl << "English: ";
	for (int i = 0; i < obj.size(); i++) {
		if ((strcmp(obj[i].GetIta(), it) == 0)) {
			if (obj[i].GetEng() != NULL) {
				std::cout << obj[i].GetEng() << " ";
			}
		}
	}
	std::cout << std::endl;
}

int main() {
	
	//test fill and list
	std::vector<CTranslate> Translate_vector;
	fill(Translate_vector);
	ListAll(Translate_vector);
	//test DelByEng
	DelByEng(Translate_vector, "lazy");
	std::cout <<std::endl << "DelByENG lazy" << std::endl;
	ListAll(Translate_vector);
	//test DelByIta
	std::cout <<std::endl << "DelByIta pronto" << std::endl;
	DelByIta(Translate_vector, "pronto");
	ListAll(Translate_vector);
	//test sortByEng
	std::cout << std::endl << "SotrByENG" << std::endl;
	SortByEng(Translate_vector);
	ListAll(Translate_vector);
	//test sortByIta
	std::cout << std::endl << "SotrByIta" << std::endl;
	SortByIta(Translate_vector);
	ListAll(Translate_vector);
	//test TranslateEng
	std::cout << std::endl << "TranslateEng" << std::endl;
	TranslateEng(Translate_vector, "jump");
	//test TranslateIta
	std::cout << std::endl << "TranslateIta" << std::endl;
	TranslateIta(Translate_vector, "trasalire");
	system("pause");
}