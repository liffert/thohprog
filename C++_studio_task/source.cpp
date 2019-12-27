#include "Menu.h"
#include "beginner.h"
#include "Easy.h"
#include "Normal.h"

int main(){

    Menu Main_menu;
    Main_menu.set_headline("Main menu");
    Main_menu.set_func(&B_start, "Beginner");
    Main_menu.set_func(&E_start, "Easy");
    Main_menu.set_func(&N_start, "Normal");
    Main_menu.start();
    
    return 0;
}