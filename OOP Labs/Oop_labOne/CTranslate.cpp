#include "CTranslate.h"
#include <string.h>
#pragma warning(disable: 4996)

CTranslate::CTranslate() {
	eng = NULL;
	ita = NULL;
}


CTranslate::~CTranslate() {
}

CTranslate::CTranslate(const CTranslate &obj) {
	this->MakePair(obj.eng, obj.ita);
}

void CTranslate::Print()const {
	if (eng == NULL) {
		std::cout << "English is empty\t";
	}
	else {
		std::cout << "English: " << eng << "\t";
	}
	if (ita == NULL) {
		std::cout << "Italian is empty" << std::endl;
	}
	else {
		std::cout << "Italian: " << ita << std::endl;
	}
}

char* CTranslate::GetEng()const {
	return eng;
}

char* CTranslate::GetIta()const {
	return ita;
}

void CTranslate::MakePair(char *EN, char *IT) {
	if (strlen(EN) > 0) {
		eng = new char[strlen(EN)];
		strcpy(eng, EN);
	}
	if (strlen(IT) > 0) {
		ita = new char[strlen(IT)];
		strcpy(ita, IT);
	}
}

CTranslate & CTranslate::operator=(const CTranslate &obj) {
	if (this != &obj) {
		this->MakePair(obj.eng, obj.ita);
		return *this;
	}
	
	return *this;
}

bool CTranslate::operator<(const CTranslate &obj) {
	int size = 0;
	int size_this = strlen(eng);
	int size_obj = strlen(obj.eng);
	if (size_this < size_obj) {
		size = size_this;
	}
	else {
		size = size_obj;
	}

	for (int i = 0; i < size; i++) {
		if (eng[i] < obj.eng[i]) {
			return true;
		}
		else if (eng[i] > obj.eng[i]) {
			return false;
		}
		else {
			continue;
		}
	}

	if (size_this == size_obj) {
		return false;
	}

	if (size == size_this) {
		return true;
	}
	else {
		return false;
	}
}

bool CTranslate::cmpIta_s(const CTranslate &obj) {
	int size = 0;
	int size_this = strlen(ita);
	int size_obj = strlen(obj.ita);
	if (size_this < size_obj) {
		size = size_this;
	}
	else {
		size = size_obj;
	}

	for (int i = 0; i < size; i++) {
		if (ita[i] < obj.ita[i]) {
			return true;
		}
		else if (ita[i] > obj.ita[i]) {
			return false;
		}
		else {
			continue;
		}
	}

	if (size_this == size_obj) {
		return false;
	}

	if (size == size_this) {
		return true;
	}
	else {
		return false;
	}
}