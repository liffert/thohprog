#pragma once
#include <iostream>

class CTranslate {
public:
	//default constructor
	CTranslate();
	//copy constructor
	CTranslate(const CTranslate &);
	//destructor
	~CTranslate();
	//overloaded assignment
	CTranslate & operator=(const CTranslate &);
	bool operator<(const CTranslate &);
	void MakePair(char *, char *);
	void Print()const;
	char *GetEng()const;
	char *GetIta()const;

	bool cmpIta_s(const CTranslate &);

private:
	char *eng;//English word
	char *ita;//Italian word
};