#include "Easy.h"
#include "Menu.h"
#include "math.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#ifdef __linux__
#include <unistd.h>
#endif

void E_start(){
    E_create_menu();
}

void E_create_menu(){
    Menu E_menu;
    E_menu.set_headline("Easy");
    E_menu.set_func(&Al_sum, "Algebraic sum");
    E_menu.set_func(&Al_sum_pow_i, "Algebraic sum 1^k + 2^k + 3^k + … + N^k");
    E_menu.set_func(&Big_and_small, "Big and Small");
    E_menu.set_func(&angle, "Angle");
    E_menu.set_func(&step, "POW");
    E_menu.set_func(&week_day, "Week day");
    E_menu.set_func(&vec_len, "Vector lenth");
    E_menu.set_func(&Func_without_pow, "Func without pow");
    E_menu.set_func(&sum_big_then, "Sum big then");
    E_menu.set_func(&func2, "FUNC 2");
    E_menu.set_func(&MY_RAND, "Rand");
    E_menu.set_func(&koord, "Koord");
    E_menu.set_func(&equ_digits, "Equ digits");
    E_menu.set_func(&str_count, "Str count");
    E_menu.set_func(&Brick, "Brick and hole");
    E_menu.set_func(&rhombus, "Rhombus");
    E_menu.set_func(&str_k, "Str K");
    E_menu.set_func(&Hex, "To hex");
    E_menu.set_func(&Palindrom, "It is Palindrom?");
    E_menu.set_func(&ctg_func, "Ctg func");
    E_menu.set_func(&test, "Test");
    E_menu.set_func(&slid_matrix, "Matrix");
    E_menu.set_func(&avarage, "Avarage");
    E_menu.set_func(&sin_func, "SIN_FUNC");
    E_menu.set_func(&per5, "Sum of %5");
    E_menu.set_func(&kvad_table, "kvad_table");
    E_menu.set_func(&mult_num, "Multiplication num");
    E_menu.set_func(&Intersection_points, "Intersection points");
    E_menu.set_func(&integer, "It is integer?");
    E_menu.set_func(&use_do_while_sorry_GOD, "Use do while sorry GOD");
    E_menu.set_func(&fuck_editors, "Sum of %5 FUCK EDITORS");
    E_menu.set_func(&triangles, "Triangles");
    E_menu.set_last_text("Back");
    E_menu.start();
}

inline void Al_sum(){
    struct X{
        double A;
        double B;
        double Z;
        double Bet;
        double X;
        double func(){
            X = pow(Z, 3) - B + (A*A/(sin(Bet)/cos(Bet)*sin(Bet)/cos(Bet)));
            return X;
        };
    };
    int N;
    double Y = 0;
    

    std::cout << "Input count of X: ";
    std::cin >> N;
    struct X *Array = new struct X[N];
    for(int i = 0; i < N; i++){
        std::cout << "Input A, B and Z for " << i + 1 << " X:" << std::endl;
        std::cout << "Input A: ";
        std::cin >> Array[i].A;
		CIN_ELIMINATION_ERROR(true)
        std::cout << "Input B: ";
        std::cin >> Array[i].B;
		CIN_ELIMINATION_ERROR(true)
        std::cout << "Input Z: ";
        std::cin >> Array[i].Z;
		CIN_ELIMINATION_ERROR(true)
        std::cout << "Input BET: ";
        std::cin >> Array[i].Bet;
		CIN_ELIMINATION_ERROR(true)
    }
    std::cout << "If X = Z^3 - B + A^2 / tg^2(BET) and Y = X1 + X2 + … + Xn" << std::endl;
    for(int i = 0; i < N; i++){
        Y = Y + Array[i].func();
    }
    std::cout << "Y = " << Y;
    delete []Array;
    Console_getChar();
}
inline void Al_sum_pow_i(){
    int k;
    int N;
    int result = 0;
    std::cout << "Input N: ";
    std::cin >> N;
	CIN_ELIMINATION_ERROR(true)
    std::cout << "Input step k: ";
    std::cin >> k;
	CIN_ELIMINATION_ERROR(true)
    for(int i = 1; i <= N; i++){
        result = result + pow(i, k);
    }
    std::cout << "If result = 1^k + 2^k + 3^k + … + N^k\nResult = " << result;
    Console_getChar();
}
inline void Big_and_small(){
    int num;
    std::cout << "Input num up to 99: ";
    std::cin >> num;
	CIN_ELIMINATION_ERROR(true)
    if(num > 99 || num < 0){
        std::cout << "Num govno";
    }
    else {
        int big;
        int Small;
        int buff;
        Small = num%10;
        big = (num - Small)/10;
        if(big < Small){
            buff = Small;
            Small = big;
            big = buff;
        }

        std::cout << "Big - " << big << std::endl;
        std::cout << "Small - " << Small << std::endl;
        Console_getChar();
    }
}
inline void angle(){
    double  Angle;
    double Speed;
    int Time;

    std::cout << "Input Speed and Time: \nSpeed: ";
    std::cin >> Speed;
	CIN_ELIMINATION_ERROR(true)
    std::cout << "Time: ";
    std::cin >> Time;
	CIN_ELIMINATION_ERROR(true)

    Angle = asin((9.8*Time)/(2*Speed)) * 90/asin(1.0);
    
    std::cout << "Angle = " << Angle;
    Console_getChar();
}
inline void step(){
    double num;
    int Step;
    std::cout << "Input number: ";
    std::cin >> num;
	CIN_ELIMINATION_ERROR(true)
    std::cout << "Input step: ";
    std::cin >> Step;
	CIN_ELIMINATION_ERROR(true)
    int buff = num;

    if(Step == 0){
        num = 1;
    }
    else{
        for(int i = 1; i < Step; i++){
            num = num*buff;
        }
    }

    std::cout << buff << "^" << Step << " = " << num;
    Console_getChar();
}
inline void week_day(){
    std::string week[] = {"Mondey", "Tuesday", "Wednesday", "Thursday", "Friday", "Suturday", "Sunday"};
    int N;
    for(int i = 0; i < 7; i++){
        std::cout << i + 1 << ". " << week[i] << std::endl;
    }
    
    std::cout << "Input number: ";
    std::cin >> N;
	CIN_ELIMINATION_ERROR(true)

    switch(N){
        case 1:{
            std::cout << week[0];
            break;
        }
        case 2:{
            std::cout << week[1];
            break;
        }
        case 3:{
            std::cout << week[2];
            break;
        }
        case 4:{
            std::cout << week[3];
            break;
        }
        case 5:{
            std::cout << week[4];
            break;
        }
        case 6:{
            std::cout << week[5];
            break;
        }
        case 7:{
            std::cout << week[6];
            break;
        }
    }
    Console_getChar();
}
inline void vec_len(){
    double X;
    double Y;
    double Z;
    std::cout << "Input X: ";
    std::cin >> X;
	CIN_ELIMINATION_ERROR(true)
    std::cout << "Input Y: ";
    std::cin >> Y;
	CIN_ELIMINATION_ERROR(true)
    std::cout << "Input Z: ";
    std::cin >> Z;
	CIN_ELIMINATION_ERROR(true)

    std::cout << "If beginning in (0.0.0), len = " << sqrt(X*X + Y*Y + Z*Z);
    Console_getChar();
}
inline void Func_without_pow(){
    struct Pow{
        int a;
        int b;
        bool minus = false;
        bool func(std::string num){
            std::string temp;
            for(int i = 0; i < num.length(); i++){
                if(num[i] == '.'){
                    for(int j = 0; j < i; j++){
                        temp = temp + num[j];
                    }
                    a = atoi(temp.c_str());
                    temp.clear();
                    for(int j = i + 1; j < num.length(); j++){
                        temp =  temp + num[j];
                    }
                    bool flag = false;
                    for(int i = 1; i < temp.length(); i++){
                        if(temp[i] != '0'){
                            flag = true;
                        }
                    }
                    if(flag){
                        b = atoi(temp.c_str());
                    }
                    else{
                        char C_num = temp[0];
                        temp.clear();
                        temp = temp + C_num;
                        b = atoi(temp.c_str());
                    }
                    temp.clear();
                    if(b == 0){
                        return false;
                    }
                    return true;
                }
            }
            return false;
        };
        double func(double num, double step){
            std::string s_num;
            s_num = std::to_string(step);
            if(num < 0){
                minus = true;
                num = -num;
            }
            if(func(s_num)){
                int buff = num;
                num = exp(a*log(num))*exp(((double)b/10)*log(buff));
                if(minus){
                    if(a % 2 != 0 || b % 2 != 0){
                        num = -num;
                    }
                    minus = false;
                }
                return num;
            }
            else{
                num = exp(step*log(num));
            }
            if(minus){
                if((int)step % 2 != 0){
                    num = -num;
                }
                minus = false;
            }
            return num;
        }
    };

    double Z = 0;
    struct Pow temp;
    
    for(double X = -1.1; X < 0.3; X = X + 0.2){
        std::cout << "X = " << X << std:: endl;
        for(int M = 1; M < 5; M++){
            Z = temp.func(X, M) * temp.func(sin(X*M), M);
            std::cout << "M = " << M << std::endl << "Z = " << Z << std::endl;
        }
        std::cout << std::endl;
    }
    Console_getChar();
}
inline void sum_big_then(){
    int N;
    double sum = 0;
    srand(time(0));
    std::cout << "Input length: ";
    std::cin >> N;
	CIN_ELIMINATION_ERROR(true)
    double *Array = new double[N];
    for(int i = 0; i < N; i++){
        Array[i] = static_cast <double>(rand()%10000)/static_cast<double>(72);
        std::cout << Array[i] << "\t";
    }
    for(int i = 0; i < N; i++){
        if(fabs(Array[i]) > 2.5){
            sum = sum + Array[i]*Array[i];
        }
    }
    std::cout << "\nSum = " << sum;
    delete[] Array;
    Console_getChar();
}
inline void func2(){
    double X;
    double Y;
    double result;

    std::cout << "Input X: ";
    std::cin >> X;
	CIN_ELIMINATION_ERROR(true)
    std::cout << "Input Y: ";
    std::cin >> Y;
	CIN_ELIMINATION_ERROR(true)

    X = X * 3.141592 / 180;
    Y = Y * 3.141592 / 180;

    result = pow((1 - tan(X)), (cos(X)/sin(X))) + cos(X - Y);
    std::cout << "Reuslt = " << result;

    Console_getChar();
}
inline void MY_RAND(){
    struct random {
        int M = 124;
        const int a = 21;
        const int inc = 111;
        int X = 4;
        void set_new_rand(int x){
            if(x > M){
                M = M + x;   
            }
            if(x < 0){
                x = - x;
            }
            X = x;
        }
        double func(){
            X = ((a * X) + inc) % M;
            return (X/(double)M);
        };

    };

    int N;

    std::cout << "Input count of numbers: ";
    std::cin >> N;
	CIN_ELIMINATION_ERROR(true)
    
    struct random temp;
    for(int i = 0; i < N; i++){
        std::cout << temp.func() << "\t"; 
    }

    temp.set_new_rand(25);
    std::cout << "\n\n\n";
    for(int i = 0; i < N; i++){
        std::cout << temp.func() << "\t"; 
    }
    Console_getChar();
}
void koord(){
    int x;
    int y;

    std::cout << "Input X: ";
    std::cin >> x;
	CIN_ELIMINATION_ERROR(true)
    std::cout << "Input Y: ";
    std::cin >> y;
	CIN_ELIMINATION_ERROR(true)

    if(x == 0 || y == 0){
        std::cout << "does not meet the conditions of the task, but...\n";
        if(x == 0 & y == 0){
            std::cout << "ON CENTER\n";
        }
        else if(x == 0){
            if(y > 0){
                std::cout << "on the axis separating II and I";
            }
            else {
                std::cout << "on the axis separating III and IV";
            }
        }
        else{
            if(x > 0){
                std::cout << "on the axis separating I and IV";
            }
            else {
                std::cout << "on the axis separating II and III";
            }
        }
        Console_getChar();
        return;
    }
    else{
        if(x > 0){
            if(y > 0){
                std::cout << "I ch";
                Console_getChar();
                return;
            }
            else {
                std::cout << "IV ch";
                Console_getChar();
                return;
            }
        }
        else{
             if(y > 0){
                std::cout << "II ch";
                Console_getChar();
                return;
            }
            else {
                std::cout << "III ch";
                Console_getChar();
                return;
            }
        }
    }
}  
void equ_digits(){
    int num;
    std::cout << "Inout num: ";
    std::cin >> num;
	CIN_ELIMINATION_ERROR(true)

    std::string snum;
    snum = std::to_string(num);

    for(int i = 0; i < snum.length(); i++){
        for(int j = 0; j < snum.length(); j++){
            if(i == j){
                continue;
            }
            if(snum[i] == snum[j]){
                std::cout << "Num have equvivalent digits" << std::endl;
                Console_getChar();
                return;
            }
        }
    }
    std::cout << "Num have not equvivalent digits" << std::endl;
    Console_getChar();
}
void str_count(){
    struct shift_and_cmp{
        void func_shift(char test[2]){
            test[0] = test[1];
        };
        bool func_cmp(const char text[3], const char text2[3]){
            for(int i = 0; i < 2; i++){
                if(text[i] == text2[i]){}
                else{
                    return false;
                }
            }
            return true;
        };
    };
    
    std::string text;
    char find[2];
    find[0] = 92;
    find[1] = 'n';
    char temp[2];
    int count = 1;


    std::cout << "Input text with \\n like new line and: ";
    std::getline(std::cin >> std::ws, text);

    if(text.empty()){
        std::cout << "text empty";
        Console_getChar();
        return;
    }
    for(int i = 0; i < 2; i++){
        temp[i] = text[i];
    }
    struct shift_and_cmp obj;
    for(int i = 2; i < text.length(); i++){
        if(obj.func_cmp(find, temp)){
            count++;
        }
        obj.func_shift(temp);
        temp[1] = text[i];
    }
    if(obj.func_cmp(find, temp)){
            count++;
    }

    std::cout << "Text have " << count << " lines\n";
    Console_getChar();

}
inline void Brick(){
    enum brick{
        Heigth,
        Width,
        Length
    };
    struct Hole{
        int Length;
        int Heigth;
    };
    struct Hole hole;
    int Brick[3];

    std::cout << "Input brick parametres\nLength: ";
    std::cin >> Brick[Length];
	CIN_ELIMINATION_ERROR(true)
    std::cout << "Heigth: ";
    std::cin >> Brick[Heigth];
	CIN_ELIMINATION_ERROR(true)
    std::cout << "Width: ";
    std::cin >> Brick[Width];
	CIN_ELIMINATION_ERROR(true)

    std::cout << "Input hole parametres:\nLength: ";
    std::cin >> hole.Length;
	CIN_ELIMINATION_ERROR(true)
    std::cout << "Heigth: ";
    std::cin >> hole.Heigth;
	CIN_ELIMINATION_ERROR(true)

    int i;
    for(i = 0; i < 3; i++){
        if(Brick[Length] <= hole.Length){
            if(Brick[Heigth] <= hole.Heigth){
                std::cout << "Will pass";
                break;
            }
            else if(Brick[Width] <= hole.Heigth){
                std::cout << "Will pass";
                break;
            }
        }
        int buff = Brick[0];
        Brick[0] = Brick[1];
        Brick[1] = Brick[2];
        Brick[2] = buff;
    }
    if(i == 3){
        std::cout << "Will not pass";
    }
    Console_getChar();
}
inline void rhombus(){
    class Rhombus{
        public:
        Rhombus(){
            bool flag = false;;
            std::cout << "Choose symb:\n" 
            << "Input 1 to : '*'\n"
            << "Input 2 to : '+'\n"
            << "Input 3 to : '#'\n";
            std::cout << "Input num 1-3: ";
            int Choose;
            std::cin >> Choose;
			CIN_ELIMINATION_ERROR(true)
            while(1){
                switch(Choose){
                    case 1:{
                        symb = '*';
                        flag = true;
                        break;
                    }
                    case 2:{
                        symb = '+';
                        flag = true;
                        break;
                    }
                    case 3:{
                        symb = '#';
                        flag = true;
                        break;
                    }
                    default:{
                        std::cout << "ERROR\nInput num 1-3: ";
                        std::cin >> Choose;
                    }
                }
                if(flag){
                    break;
                }
            }
            std::cout << "Input len & wid: ";
            std::cin >> len_wid;
        }
        ~Rhombus(){}
        void draw(){
            Console_clear();
            Console_setCursorPosition(0, 0);
            int y;
            if(len_wid%2 == 0){
                len_wid--;
            }
            int x = len_wid/2;
            int step = 1;
            Console_setCursorPosition(4, x);
            std::cout << symb;
            for(y = 5; y < len_wid/2 + 4; y++){
                x--;
                Console_setCursorPosition(y, x);
                std::cout << symb;
                Console_setCursorPosition(y, x + 2*step);  
                std::cout << symb;
                step++;        
            }
            step = step - 2;
            for(y; y < len_wid + 2; y++){
                x++;
                Console_setCursorPosition(y, x);
                std::cout << symb;
                Console_setCursorPosition(y, x + 2*step);  
                std::cout << symb;
                step--;
            }
        }
        private:
        int len_wid;
        char symb;
    };

    Rhombus temp;
    temp.draw();
    Console_getChar();
}
inline void str_k(){
    std::cout << "Input num: ";
    std::string num;
    int i;
    std::getline(std::cin >> std::ws, num);
    std::cout << "Input number from 0 to " << num.length() - 1 << ": ";
    std::cin >> i;
	CIN_ELIMINATION_ERROR(true)
    if(i >= num.length() || i < 0){
        std::cout << "Error\n";
    }
    else{
        std::cout << num[i];
    }
    Console_getChar();
}
void Hex(){
    class ToHex{
        public:
        ToHex(){}
        ~ToHex(){}
        std::string convertation(int num, bool flag = true){
            std::ostringstream word;
            word << std::hex << num;
            if (flag) {
                switch (word.str().length()) {
                case 1:
                    hex_num = "000" + word.str();
                    break;
                case 2:
                    hex_num = "00" + word.str();
                    break;
                case 3:
                    hex_num = "0" + word.str();
                    break;
                case 4:
                    hex_num = word.str();
                    break;
                default:
                    hex_num = word.str();
                }
            }
            else {
                if (word.str().length() == 1) {
                    hex_num = "0" + word.str();
                }
                else {
                    hex_num = word.str();
                }
            }
            return hex_num;
        }
        private:
        std::string hex_num;
    };
    int num;
    std::cout << "Input num: ";
    std::cin >> num;
	CIN_ELIMINATION_ERROR(true)
    ToHex temp;
    printf("%d to hex = %s", num, temp.convertation(num).c_str());
    Console_getChar();
}
void Palindrom(){
    std::string data;
    
    std::cout << "Input data: ";
    std::getline(std::cin >> std::ws, data);
    
    int k = data.length() - 1;
    for(int i = 0; i < data.length(); i++){
        if(data[i] != data[k]){
            std::cout << "Not palindrom\n";
            Console_getChar();
            return;
        }
        k--;
    }
    std::cout << "Palindrom\n";
    Console_getChar();
}
void ctg_func(){
    class ctg{
        public:
        ctg(){
            std::cout << "Input interval a and b: ";
            std::cout << "a: ";
            std::cin >> a;
			CIN_ELIMINATION_ERROR(true)
            std::cout << "b: ";
            std::cin >> b;
			CIN_ELIMINATION_ERROR(true)
            std::cout << "Input step: ";
            std::cin >> h;
			CIN_ELIMINATION_ERROR(true)
        }    
        ctg(int _a, int _b, int _h): a(_a), b(_b), h(_h){}
        void rewrite(int _a, int _b, int _h){
             a = _a;
             b = _b;
             h = _h;
        };
        std::string get_value(){
            std::string value;
            double num;
            for(int i = a; i <=b; i = i + h){
                num = pow(cos(log(i))/sin(log(i)), 2);
                if(isnan(num) || isinf(num)){
                    value = value + "does not exist(" + std::to_string(i) + ")" + " ";
                }
                else{
                value = value + std::to_string(num) + " ";
                }
            }
            return value;
        }

        private:

        double a;
        double b;
        double h;
    };

    ctg temp(-4, 4, 1);
    std::cout << "y = " << temp.get_value();
    Console_getChar();
}
void test(){
    std::cout << "1)How many cat lives?\nanswers:\n-> 5lives\n->7 lives\n->9 lives\n";
    int choose;
    int answer = 9;
    int points = 0;
    std::cout << "Your answer: ";
    std::cin >> choose;
	CIN_ELIMINATION_ERROR(true)
    if(choose == answer){
        points = points + 9;
    }
    std::cout << "2)How many centimeters in a meter?\nanswers:\n->10 centimeters\n-> 100 centimeters\n-> 1000 centimeters\n";
    std::cout << "Your answer: ";
    std::cin >> choose;
	CIN_ELIMINATION_ERROR(true)
    answer = 100;
    if(choose == answer){
        points = points + 9;
    }

    std::cout << "Your points: " << points;

    Console_getChar();
}
void slid_matrix(){
    int sum = 0;
    struct matrix{
        int **Matrix;
        int N;
        int M;
        void create(){
            Matrix = new int *[N];
            for(int i = 0; i < M; i++){
                Matrix[i] = new int [M];
            }
        }
        void fill(){
            srand(time(0));
            for(int i = 0; i < N; i++){
                for(int j = 0; j < M; j++){
                    Matrix[i][j] = rand()%100;
                }
            }
        }
        void out(){
            for(int i = 0; i < N; i++){
                for(int j = 0; j < M; j++){
                    std::cout << Matrix[i][j] << "\t";
                }
                std::cout << std::endl;
            }
        }
    };
    struct matrix Matrix;
    std::cout << "Input count of str and column: ";
    std::cin >> Matrix.N;
	CIN_ELIMINATION_ERROR(true)
    Matrix.M = Matrix.N;
    Matrix.create();
    Matrix.fill();
    Matrix.out();
    for(int i = 0; i < Matrix.N; i++){
        sum = sum + Matrix.Matrix[i][i];
    }

    std::cout << "Slid = " << sum;
    Console_getChar();
}
void avarage(){
    struct func{
        double avarage(double Array[], int N){
            double av_sum = 0; 
            for(int i = 0; i < N; i++){
                av_sum = av_sum + Array[i];
            }
            return av_sum/N;
        };
    };
    struct func temp;
    const int N = 10;
    double Array[N];
    for(int i = 0; i < N; i++){
        Array[i] = static_cast<double>(rand()%10000)/(double)72;
        std::cout << Array[i] << "\t";
    }
    std::cout << "\nAvarage = " << temp.avarage(Array, N);
    Console_getChar();
}
void sin_func(){
    struct func{
        double PI = 3.1415;
        double sin_(int n){
            double val = 0;
            for(int i = 1; i <= n; i++){
                val = val + sin(i *(PI/180));
            }

            return 1/val;
        };
    };
    struct func temp;
    double num = 0;
    int N;
    std::cout << "Input N: ";
    std::cin >> N;
	CIN_ELIMINATION_ERROR(true)
    for(int i = 1; i <= N; i++){
        num = num + temp.sin_(i);
    }
    std::cout << "Result " << num;
    Console_getChar();
}
void  per5(){
    int N;
    int sum = 0;
    std::cout << "Input count: ";
    std::cin >> N;
	CIN_ELIMINATION_ERROR(true)
    
    int i = 0;
    while(i <= N){
        if(i % 5 == 0){
            sum = sum + i;
        }

        i++;
    }

    std::cout << "Result = " << sum;
    Console_getChar();
}
void kvad_table(){
    std::cout << "Kvad table\nNum\t\t\tKvad of num\n";

    for(int i = 1; i <= 5; i++){
        std::cout << i << "\t\t\t" << i*i << std::endl;
    }

    Console_getChar();
}
void mult_num(){
    float num;
    std::cout << "Input num: ";
    std::cin >> num;
	CIN_ELIMINATION_ERROR(true)
    for(int i = 1; i <= 10; i++){
        printf("%d * %.3f = %.3f\n", i, num, static_cast<float>(num*i));
    }

    Console_getChar();
}
void Intersection_points(){
    int a;
    int b;
    int c;
    int d;
    int k;

    double x;
    double y;
    std::cout << "Input a, b, c, d, k:\na: ";
    std::cin >> a;
	CIN_ELIMINATION_ERROR(true)
    std::cout << "b: ";
    std::cin >> b;
	CIN_ELIMINATION_ERROR(true)
    std::cout << "c: ";
    std::cin >> c;
	CIN_ELIMINATION_ERROR(true)
    std::cout << "d: ";
    std::cin >> d;
	CIN_ELIMINATION_ERROR(true)
    std::cout << "k: ";
    std::cin >> k;
	CIN_ELIMINATION_ERROR(true)

    x = (c - k)/(d - 2*a - b);
    y = d*x + k;
    printf("Intersection points it[%.1lf, %.1lf]", x, y);
    Console_getChar();
}
void integer(){
    double num;
    std::cout << "Input num: ";
    std::cin >> num;
	CIN_ELIMINATION_ERROR(true)

    if(num == static_cast<int>(num)){
        std::cout << "It is integer";
    }
    else{
        std::cout << "It is not integer";
    }

    Console_getChar();
}
void use_do_while_sorry_GOD(){
    double num;
    std::cout << "Input nums: \n";
    do{
        std::cout << "Num: ";
        std::cin >> num;
		CIN_ELIMINATION_ERROR(true)
    }while(num != 1);

    Console_getChar();
}
void fuck_editors(){
    per5();
}
void triangles(){
    int N;
    std::cout << "Input number of triangles: ";
    std::cin >> N;
	CIN_ELIMINATION_ERROR(true)


    for(int i = 0; i < N; i++){
        for(int z = 1; z <= N; z++){
            for(int k = 0; k < N - i; k++){
                std::cout << " ";
            }
            for(float j = 0; j <= i; j = j + 0.5){
                std::cout << "*";
            }
            for(int k = 0; k < N - i; k++){
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    Console_getChar();
}