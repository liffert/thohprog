#pragma once
#include <iostream>

class CFile {
public:
	/*
	methods
	*/
	friend std::ostream& operator<<(std::ostream& stream, CFile& obj) {
		stream << "Name: " << obj._filename << " " << "Date: " << obj._creation_date << " " << " Size: " << obj._size << std::endl;
		return stream;
	}
	CFile();
	CFile(const std::string);
	CFile(const CFile& file);
	void set_field(const std::string, int);
	char* get_filename();
	char* get_date();
	int get_size();
	bool before_date(const std::string date);
	void rename(const std::string name);
	bool operator==(const CFile& file);
private:
	char* _filename;
	char* _creation_date;
	int _size;
};