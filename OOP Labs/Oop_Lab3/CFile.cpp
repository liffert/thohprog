#include "CFile.h"
#pragma warning (disable: 4996)

CFile::CFile() {
	_size = 0;
	_filename = NULL;
	_creation_date = NULL;
}

CFile::CFile(const std::string line) {
	std::string word;
	int counter = 0;
	for (int i = 0; i < line.length(); i++) {
		if (line[i] == ';') {
			set_field(word, counter);
			counter++;
			word.clear();
			continue;
		}
		word = word + line[i];
	}
	set_field(word, counter);
	word.clear();
}

CFile::CFile(const CFile& file) {
	_size = file._size;
	_filename = new char[strlen(file._filename)];
	strcpy(_filename, file._filename);
	_creation_date = new char[strlen(file._creation_date)];
	strcpy(_creation_date, file._creation_date);
}

void CFile::set_field(const std::string word, int counter) {
	switch (counter) {
	case 0: {
		_filename = new char[word.length()];
		for (int i = 0; i < word.length(); i++) {
			_filename[i] = word[i];
		}
		_filename[word.length()] = '\0';
		break;
	}
	case 1: {
		_creation_date = new char[word.length()];
		for (int i = 0; i < word.length(); i++) {
			_creation_date[i] = word[i];
		}
		_creation_date[word.length()] = '\0';
		break;
	}
	case 2: {
		_size = atoi(word.c_str());
	}
	}
}

char* CFile::get_filename() {
	return _filename;
}

char* CFile::get_date() {
	return _creation_date;
}

int CFile::get_size() {
	return _size;
}

bool CFile::before_date(std::string date) {
	int day_this;
	int day_str;
	int month_this;
	int month_str;
	int year_this;
	int year_str;
	int counter = 0;
	std::string word;
	int i = 0;
	while (_creation_date[i] != '\0') {
		if (_creation_date[i] != '.') {
			word = word + _creation_date[i];
			i++;
		}
		else {
			switch (counter) {
			case 0: {
				day_this = atoi(word.c_str());
				word.clear();
				break;
			}
			case 1: {
				month_this = atoi(word.c_str());
				word.clear();
				break;
			}
			}
			counter++;
			i++;
		}
	}
	year_this = atoi(word.c_str());
	word.clear();
	counter = 0;
	for (int i = 0; i < date.length(); i++) {
		if (date[i] != '.') {
			word = word + date[i];
		}
		else {
			switch (counter) {
			case 0: {
				day_str = atoi(word.c_str());
				word.clear();
				break;
			}
			case 1: {
				month_str = atoi(word.c_str());
				word.clear();
				break;
			}
			}
			counter++;
		}
	}
	year_str = atoi(word.c_str());
	word.clear();
	if (year_this <= year_str) {
		if (year_this < year_str) {
			return true;
		}
		if (month_this <= month_str) {
			if (month_this < month_str) {
				return true;
			}
			if (day_this <= day_this) {
				if (day_this < day_str) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void CFile::rename(const std::string name) {
	_filename = NULL;
	_filename = new char[name.length()];
	strcpy(_filename, name.c_str());
}

bool CFile::operator==(const CFile& file) {
	if (_size == file._size && !strcmp(_filename, file._filename) && !strcmp(_creation_date, file._creation_date)) {
		return true;
	}
	return false;
}