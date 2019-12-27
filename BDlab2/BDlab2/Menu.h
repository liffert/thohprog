#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include "Header.h"

//windows setup
#ifdef _WIN32
    #pragma warning (disable: 4996)
    #define Console_getChar() getch()
	#include <Windows.h>
	#include <conio.h>
	static HANDLE hConsole;
	static HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    static void gotoxy(int X, int Y)
    {
	    COORD coord = { X, Y };
	    SetConsoleCursorPosition(hStdOut, coord);
    }
    #define Console_setCursorPosition(Y, X) gotoxy(X, Y)
	#define Console_clear() system("cls")
	//Cin elimination error macro. Clear cin buff if the user entered incorrect data
	#define CIN_ELIMINATION_ERROR(exit) {if(CIN_FUNC() && exit){ std::cout << "CIN ERROR - return\n" << system("pause");}}
//linux setup
#elif defined __linux__
    #include "progbase/console.h"
	//Cin elimination error macro. Clear cin buff if the user entered incorrect data
	#define CIN_ELIMINATION_ERROR(exit) {if(CIN_FUNC() && exit){ std::cout << "CIN ERROR - return\n" << Console_getChar(); return;}}
#endif
static bool CIN_FUNC(){ 
    if(std::cin.fail()){ 
        std::cin.clear(); 
#ifdef _WIN32
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(),'\n');
#elif defined __linux__
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#endif
        return true;
    }
    return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////

void print(PGresult* res);


class Menu {

public:

    Menu();
    void set_func(void (*func)(void), std::string name);//add function and paragraph name to menu
    int start();//start menu
    void set_last_text(std::string name);//setup last paragraph. Default "Exit" and func exit(true). if changed, the function changes to return;
    void clear();//clear menu setting for this object
    void set_headline(std::string head);//set menu headline
	void set_ask();
    ~Menu();
private:
#define EXITSTATUS 0
    struct map{
        void (*func)(void);
        std::string name;
    };
    std::vector<map> func_map;//paragraphes database
    int count = 0;
    std::string Headline = "";
    std::string last = "Exit";
	bool ask_state = false;

	struct size {
		int x = 170;
		int y = 30;
	}; struct size Size;

    void draw_menu(int selection);//menu display function
};