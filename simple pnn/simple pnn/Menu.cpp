#include "Menu.h"

Menu::Menu(){}

Menu::~Menu(){};

void Menu::set_func(void (*func)(void), std::string name){
    struct map temp;
    temp.func = func;
    temp.name = name;
    func_map.push_back(temp);
}

int Menu::start(){
    //windows setup for control keys
#ifdef _WIN32

    const int Keys_first_up_down = 224;
    const int Keys_second_up = 72;
    const int Keys_second_down = 80;
	const int Keys_Enter = 13;
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);

    //linux setup for control keys
#elif defined __linux__

    const int Keys_first_up_down = 91;
    const int Keys_second_up = 65;
    const int Keys_second_down = 66;
    const int Keys_Enter = 10;
#endif

	Size.x = Size.x / 2;
	Size.y = Size.y / 2 - func_map.size() / 2 + 1;

    int selection = 0;
    //add last paragrahp
    struct map temp;
    temp.name = last;
    temp.func = nullptr;
    func_map.push_back(temp);
    //////////////////////////
    count = func_map.size();
    while(1){
        draw_menu(selection);//print menu
        int key = Console_getChar();//read key
        switch(key){
            case Keys_first_up_down: {//if key down or key up
                int key_next = Console_getChar();
                if(key_next == Keys_second_down){//if key down
                    if(selection < count - 1){
                        selection++;
                    }
                    else{
                        selection = 0;
                    }
                }
                else if(key_next == Keys_second_up){//if key up
                    if(selection > 0){
                        selection--;
                    }
                    else{
                        selection = count - 1;
                    }
                }
                break;
            }
            case Keys_Enter: {//if enter
                if(selection == count - 1){
                    if(last != "Exit"){
                        return EXITSTATUS;
                    }
                    else{
                        Console_clear();
                        exit(true);
                    }
                }
                else{
                    Console_clear();
                    func_map[selection].func();
					if (ask_state) { return selection + 1; }
                }
                break;
            }
        }
    }
}

void Menu::draw_menu (int selection){
    Console_clear();
    Console_setCursorPosition(Size.y - 2, Size.x + 3);//setup cursor to x = 33 y = 8
    std::cout << Headline;
    for(int i = 0; i < count; i++){
        Console_setCursorPosition(Size.y + i, Size.x);
        if(i == selection){
            printf("<%d.%s>", i + 1, func_map[i].name.c_str());
        }
        else{
            printf("%d.%s", i + 1, func_map[i].name.c_str());
        }
    }
}

void Menu::set_last_text(std::string name){
    last = name;
}
void Menu::clear(){
    last = "Exit";
    func_map.clear();
    count = 0;
}
void Menu::set_headline(std::string head){
    Headline = head;
}

void Menu::set_ask() {
	ask_state = true;
}