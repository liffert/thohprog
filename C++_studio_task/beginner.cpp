#include "beginner.h"
#include "Menu.h"
#include "ctype.h"
#include <string>

//menu creation
void B_start(){
    B_create_menu();
}
inline void B_create_menu (){
    Menu B_menu;
    B_menu.set_headline("Beginner");
    B_menu.set_func(&num_to_digits, "Num to digits");
    B_menu.set_func(&math_sentense, "Math sentense");
    B_menu.set_func(&to_up, "To upper case");
    B_menu.set_func(&metre_to_km, "Metre to km");
    B_menu.set_func(&print, "Print");
    B_menu.set_func(&print_house, "Print house");
    B_menu.set_func(&print_triangle, "Print triangle");   
    B_menu.set_func(&print_ramka, "Print ramka");    
    B_menu.set_func(&compare, "Compare"); 
    B_menu.set_func(&if_increase, "If increase");    
    B_menu.set_last_text("Back");
    B_menu.start();
}
////////////////////////////////////////////////////

/////////////////task one///////////////////////////////////
inline void num_to_digits(){
    
    std::cout << "Enter a five-digit number if the number is less than five characters, that is, the missing digits are 0" 
    << std::endl << "Input number: ";
    int num = 0;
    std::cin >> num;
	CIN_ELIMINATION_ERROR(true)
    int step = 10000;
    for(int i = 0; i < 5; i++){
        std::cout << i + 1 << " digit: " << num/step%10 << std::endl;
        step = step/10;
    }
    Console_getChar();
}
///////////////////////////////////////////////////////////////////
/////////////////task two///////////////////////////////////
inline void math_sentense(){
    
    double a;
    double b;
    double f;
    std::cout << "Input digit a, b and f: \na = ";
    std::cin >> a;
	CIN_ELIMINATION_ERROR(true)
    std::cout << "b = ";
    std::cin >> b;
	CIN_ELIMINATION_ERROR(true)
    std::cout << "f = ";
    std::cin >> f;
	CIN_ELIMINATION_ERROR(true)
    std::cout << "Calculated by the formula: (a + b - f / a) + f * a * a - (a + b)\n";
    double x = (a + b - f / a) + f * a * a - (a + b);
    std::cout << x;
    Console_getChar();
}
/////////////////////////////////////////////////
/////////////////task three///////////////////////////////////
inline void to_up(){
    
    char letter;
    std::cout << "Input letter: ";
    std::cin >> letter;
	CIN_ELIMINATION_ERROR(false)
    std::cout << "In upper case: " << (char)toupper(letter);
    Console_getChar();
}
////////////////////////////////////////////////////
/////////////////task four///////////////////////////////////
inline void metre_to_km(){
    
    double len;
    std::cout << "Input count of metre: ";
    std::cin >> len;
	CIN_ELIMINATION_ERROR(true)
    std::cout << len << " metres == " << len/1000 << " km" << std::endl;
    Console_getChar();
}
////////////////////////////////////////////////////
/////////////////task five//////////////////////////////////
inline void print(){
    
    std::cout << "I know integer to char thi is like:" << std::endl 
    << "std::cout << (char)192, but prorgramm on linux\n";
    Console_getChar();
}
////////////////////////////////////////////////////
/////////////////task six///////////////////////////////////
inline void print_house(){
    std::cout << "House:\n\t     /\\\n\t    /  \\\n\t   /    \\\n\t  /------\\\n\t / |    | \\\n\t   |    |  \n\t   |    |  \n\t   |    |  \n\t   |    |  \n\t   |____|  ";
    Console_getChar();
}
///////////////////////////////////////////////////
/////////////////task seven///////////////////////////////////
inline void print_triangle(){
    
    int N;
    std::cout << "Input count of str: ";
    std::cin >> N;
	CIN_ELIMINATION_ERROR(true)
    for(int i = 1; i <= N; i++){
        for(int j = 0; j < i; j++){
            std::cout << "*";
        }
        std::cout << std::endl;
    }
    Console_getChar();
}
///////////////////////////////////////////////////
/////////////////task eight//////////////////////////////////
inline void print_ramka(){
    
    std::string Ramka[3] = {" Laboratorna robota 1 ", " Created by: ", " "};
    std::string temp;
    int count = 0;
    std::cout << "Input Group: ";
    std::getline(std::cin >> std::ws, temp);
    Ramka[1] = Ramka[1] + temp;
    std::cout << "Input Last name: ";
    std::getline(std::cin >> std::ws, temp);
    Ramka[2] = Ramka[2] + temp + " ";
    std::cout << "Input name: ";
    std::getline(std::cin >> std::ws, temp);
    Ramka[2] = Ramka[2] + temp + " ";
    std::cout << "Input Father name: ";
    std::getline(std::cin >> std::ws, temp);
    Ramka[2] = Ramka[2] + temp + " ";
    for(int i = 0; i < 3; i++){
        if(count < Ramka[i].length()){
            count = Ramka[i].length();
        }
    }
    count++;
    std::cout << std::endl;

    for(int i = 0; i < 5; i++){
        if(i > 0 && i < 4){
            std::cout << "*" << Ramka[i - 1];
            for(int j = Ramka[i - 1].length(); j < count - 1; j++){
                std::cout << " ";         
            }
        }
        else{
            for(int j = 0; j < count; j++){
                std::cout << "*";
            }
        }
        std::cout << "*\n";
    }

    Console_getChar();
}
////////////////////////////////////////////////////
/////////////////task nine///////////////////////////////////
inline void compare(){
    
    int num1;
    int num2;
    std::cout << "Input num 1: ";
    std::cin >> num1;
    std::cout << "Input num 2: ";
    std::cin >> num2;

    if(num1 > num2){
        std::cout << "Bigger\n";
    }
    else if(num1 == num2){
        std::cout << "Equivalent\n";
    }
    else{
        std::cout << "Smaller\n";
    }
    Console_getChar();
}
////////////////////////////////////////////////////
/////////////////task ten///////////////////////////////////
void if_increase(){
    
    int nums[3];
    std::cout << "Input num 1: ";
    std::cin >> nums[0];
	CIN_ELIMINATION_ERROR(true)
    std::cout << "Input num 2: ";
    std::cin >> nums[1];
	CIN_ELIMINATION_ERROR(true)
    std::cout << "Input num 3: ";
    std::cin >> nums[2];
	CIN_ELIMINATION_ERROR(true)
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(nums[i] == nums[j] && i != j){
                for(int k = 0; k < 3; k++){
                    nums[k] = nums[k] + 5;
                    std::cout << nums[k] << std::endl;
                }
                Console_getChar();
                
                return;
            }
        }
    }
    std::cout << "Equvivalents exept\n";
    Console_getChar();
}
////////////////////////////////////////////////////////////////////