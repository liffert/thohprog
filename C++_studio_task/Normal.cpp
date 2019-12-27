#include "Normal.h"
#include "Menu.h"
#include "fstream"
#include <sstream>
#include <math.h>
#include <cctype>
#include <map>
#include "nlohmann/json.hpp"

void N_start(){
    N_create_menu();
}
inline void N_create_menu(){
    Menu N_menu;
    N_menu.set_func(&balance, "Balance");
    N_menu.set_func(&drib, "DRIB");
    N_menu.set_func(&martix_mult, "Matrix multiplication");
    N_menu.set_func(&Realloc_test, "Realloc");
    N_menu.set_func(&List, "List");
    N_menu.set_func(&zig_zag, "Zig_zag");
    N_menu.set_func(&kor, "Koren cube");
    N_menu.set_func(&strings, "String manipulation");
    N_menu.set_func(&Array_rand, "Array rand, swap min");
    N_menu.set_func(&test_map, "Test map");
    N_menu.set_func(&search_in_array, "Search in array %2");
    N_menu.set_func(&schedule, "Schedule");
    N_menu.set_func(&_time, "Time");
    N_menu.set_func(&employee, "Employee");
    N_menu.set_func(&two_to_one, "Two to one");
    N_menu.set_func(&strrow, "Str row");
    N_menu.set_func(&letter, "Letter");
    N_menu.set_func(&nalog, "Nalog");
    N_menu.set_func(&question, "Question");
    N_menu.set_func(&lettersc, "Lettersc");
    N_menu.set_func(&param, "Func with param");
    N_menu.set_func(&raz_matrix, "Raz matrix");
    N_menu.set_func(&compet, "Compepition result");
    N_menu.set_func(&max_len, "Max len in line");
    N_menu.set_func(&min_len, "Min len in line");
    /*N_menu.set_func();
    N_menu.set_func();
    N_menu.set_func();
    N_menu.set_func();
    N_menu.set_func();
    N_menu.set_func();
    N_menu.set_func();
    N_menu.set_func();
    N_menu.set_func();
    N_menu.set_func();
    N_menu.set_func();
    N_menu.set_func();
    N_menu.set_func();
    N_menu.set_func();*/

    N_menu.set_headline("Normal");
    N_menu.set_last_text("Back");
    N_menu.start();
}
void balance(){
    std::string path;
    int straight = 0;
    int reverse = 0;
    char test;

    std::cout << "Input file name or path: ";
    std::getline(std::cin >> std::ws, path);
    std::ifstream file(path);
    if(!file.is_open()){
        std::cout << "File exist\n";
        return;
    }
    while(!file.eof()){
        test = file.get();
        if(test == '{'){
            straight++;
        }
        else if(test == '}'){
            reverse++;
        }
        test = '1';
    }
    if(straight == reverse){
        std::cout << "Balance\n";
    }
    else{
        std::cout << "Not balance\n";
    }
    Console_getChar();
}
inline void drib(){
    int N;

    double result = 2;
    std::cout << "Input count: ";
    std::cin >> N;
    CIN_ELIMINATION_ERROR(true)
    if(N == 0){
        result = 0;
    }
    for(int i = 1; i < N; i++){
        result = 1+1/result;
    }
    std::cout << "result =  " << result;
    Console_getChar();
}
void martix_mult(){
    struct func{
        static void stat(){
            int row = 300;
            int column = 300;
            int matrix[300][300];
            int vec[300];
            int resultV[300];
            int result = 0;

            std::cout << "Input row: ";
            std::cin >> row;
            CIN_ELIMINATION_ERROR(true)
            std::cout << "Input column: ";
            std::cin >> column;
            CIN_ELIMINATION_ERROR(true)
            std::cout << "Input matrix:\n";
            for(int i = 0; i < row; i++){
                for(int j = 0; j < column; j++){
                    printf("Matrix[%d][%d] = ", i, j);
                    std::cin >> matrix[i][j];
                    CIN_ELIMINATION_ERROR(true)
                }
            }
            std::cout << "Input vector:\n";
            for(int i = 0; i < column; i++){
                printf("Vector[%d] = ", i);
                std::cin >> vec[i];
                CIN_ELIMINATION_ERROR(true)
            }
            for(int i = 0; i < row; i++){
                for(int j = 0; j < column; j++){
                    result = result + (matrix[i][j] * vec[j]);
                }
                resultV[i] = result;
                result = 0;
            }
            std::cout << "Result:\n";
            for(int i = 0; i < row; i++){
                std::cout << resultV[i] << std::endl;
            }
            Console_getChar();
        };
        static void dynamic_one(){
            int row;
            int column;
            int **matrix;
            int *vec;
            int *resultV;
            int result = 0;

            std::cout << "Input row: ";
            std::cin >> row;
            CIN_ELIMINATION_ERROR(true)
            std::cout << "Input column: ";
            std::cin >> column;
            CIN_ELIMINATION_ERROR(true)
            std::cout << "Input matrix:\n";

            matrix = new int*[row];
            for(int i = 0; i < row; i++){
                matrix[i] = new int[column];
            }
            resultV = new int[row];
            vec = new int[column];

            for(int i = 0; i < row; i++){
                for(int j = 0; j < column; j++){
                    printf("Matrix[%d][%d] = ", i, j);
                    std::cin >> matrix[i][j];
                    CIN_ELIMINATION_ERROR(true)
                }
            }
            std::cout << "Input vector:\n";
            for(int i = 0; i < column; i++){
                printf("Vector[%d] = ", i);
                std::cin >> vec[i];
                CIN_ELIMINATION_ERROR(true)
            }
            for(int i = 0; i < row; i++){
                for(int j = 0; j < column; j++){
                    result = result + (matrix[i][j] * vec[j]);
                }
                resultV[i] = result;
                result = 0;
            }
            std::cout << "Result:\n";
            for(int i = 0; i < row; i++){
                std::cout << resultV[i] << std::endl;
            }

            for(int i = 0; i < row; i++){
                delete[] matrix[i];
            }
            delete []matrix;
            delete []vec;
            delete []resultV;
            Console_getChar();
        };
        static void dynamic_two(){
            int row;
            int column;
            int **matrix;
            int *vec;
            int *resultV;
            int result = 0;

            std::cout << "Input row: ";
            std::cin >> row;
            CIN_ELIMINATION_ERROR(true)
            std::cout << "Input column: ";
            std::cin >> column;
            CIN_ELIMINATION_ERROR(true)
            std::cout << "Input matrix:\n";

            matrix = new int*[row];
            for(int i = 0; i < row; i++){
                matrix[i] = new int[column];
            }
            resultV = new int[row];
            vec = new int[column];

            for(int i = 0; i < row; i++){
                for(int j = 0; j < column; j++){
                    printf("Matrix[%d][%d] = ", i, j);
                    std::cin >> *((*(matrix + i)) + j);
                    CIN_ELIMINATION_ERROR(true)
                }
            }
            std::cout << "Input vector:\n";
            for(int i = 0; i < column; i++){
                printf("Vector[%d] = ", i);
                std::cin >> *(vec + i);
                CIN_ELIMINATION_ERROR(true)
            }
            for(int i = 0; i < row; i++){
                for(int j = 0; j < column; j++){
                    result = result + (*((*(matrix + i) + j)) * *(vec + j));
                }
                *(resultV + i) = result;
                result = 0;
            }
            std::cout << "Result:\n";
            for(int i = 0; i < row; i++){
                std::cout << *(resultV + i) << std::endl;
            }
            for(int i = 0; i < row; i++){
                delete[] matrix[i];
            }
            delete []matrix;
            delete []vec;
            delete []resultV;
            Console_getChar();
        };
    };
    struct func temp;
    Menu Matrix_menu;
    Matrix_menu.set_func(temp.stat, "Static");
    Matrix_menu.set_func(temp.dynamic_one, "Dynamic first");
    Matrix_menu.set_func(temp.dynamic_two, "Dynamic second");
    Matrix_menu.set_headline("Matrix");
    Matrix_menu.set_last_text("Back");
    Matrix_menu.start();
}
inline void Realloc_test(){
    struct func{
        void print_array(const int *Array, int size){
            for(int  i = 0; i < size; i++){
                std::cout << Array[i] << "  ";
            }
            std::cout << std::endl;
        };
    };
    int *Array = (int*)malloc(sizeof(int));
    int num;
    int size = 0;
    struct func temp;
    while(1){
        std::cout << "Input num: ";
        std::cin >> num;
        CIN_ELIMINATION_ERROR(true)
        if(num >= 0){
            size++;
            Array = (int*)realloc(Array, size*sizeof(int));
            Array[size - 1] = num;
            temp.print_array(Array, size);
        }
        else{
            temp.print_array(Array, size);
            break;
        }
    }
    Console_getChar();
    free(Array);
}
void List(){
    class List{
        public:
        List(){
            Head = NULL;
            current = Head;
        }
        List(int data, std::string name){
            Head = new struct element;
            Head->pointer = NULL;
            Head->age = data;
            Head->name = name;
            current = Head;
        }
        ~List(){
            struct element *temp = Head;
            while(temp != NULL){
                temp = temp->pointer;
                delete Head;
                Head = temp;
            }
        }
        void add(int data, std::string name){
            if(Head == NULL){
                Head = new struct element;
                Head->pointer = NULL;
                Head->age = data;
                Head->name = name;
                current = Head;
            }
            else{
                struct element *temp = new struct element;
                temp->age = data;
                temp->name = name;
                temp->pointer = NULL;
                current->pointer = temp;
                current = current->pointer;
            }
        }
        void read(){
            struct element *temp = Head;
            while(temp != NULL){
                printf("\nName: %s\nAge: %d\n\n", temp->name.c_str(), temp->age);
                temp = temp->pointer;
            }
        }
        private:
        struct element{
            int age;
            std::string name;
            struct element *pointer;
        };
        struct element *Head;
        struct element *current;
    };

    int choose = 1;
    List list;
    std::string name;
    int age;
    while(choose != 0){
        std::cout << "Input 0 to exit or 1 to write new data: ";
        std::cin >> choose;
        CIN_ELIMINATION_ERROR(true)
        if(choose == 1){
            std::cout << "Input name: ";
            std::getline(std::cin >> std::ws, name);
            std::cout << "Input age: ";
            std::cin >> age;
            CIN_ELIMINATION_ERROR(true)

            list.add(age, name);
            list.read();
        }
    }
    Console_getChar();
}
void zig_zag(){
    int num = 0;
    int N;
    std::cout << "Input N: ";
    std::cin >> N;
    CIN_ELIMINATION_ERROR(true)
    int **Array = new int*[N];
    for(int i = 0; i < N; i++){
        Array[i] = new int[N];
    }

    int x = 0;
    int y = 0;
    Array[y][x] = num;
    num++;
    y++;

    for(int i = 0; i < N - 1; i++) {
        while(x < N - 1 && y > 0){
            Array[y][x] = num;
            num++;
            x++;
            y--;
        }
        Array[y][x] = num;
        num++;
        x++;
        if(x > N - 1){
            x--;
            y++;
        }
        while(x > 0 && y < N - 1){
            Array[y][x] = num;
            num++;
            x--;
            y++;
        }
        Array[y][x] = num;
        num++;
        y++;
        if(y > N - 1){
            y--;
            x++;
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            std::cout << Array[i][j] << " ";
        }
        std::cout << std::endl;
    }
    for(int i = 0; i < N; i++){
        delete[] Array[i];
    }
    Console_getChar();
}
void kor(){
    double y;
    double y1 = 0;
    double x;
    std::cout << "Input x: ";
    std::cin >> x;
    CIN_ELIMINATION_ERROR(true)

    y = x;

    double wh = pow(10.0, -5.0);

    while(1){
        y1 = 0.5*(y + 3*x / (2 * y*y + x/y));
        if(fabs(y1 - y) <    wh){
            break;
        }
        y = y1;
    }
    std::cout << "Result: " << y;
    Console_getChar();
}
void strings(){
    class String_manipulation{


        public:
        String_manipulation(){}
        ~String_manipulation(){}
        bool set_new_line(const std::string line){
            Line = line;
            if(Line.length() > 255){
                return false;
            }
            return true;
        }

        void ToUpper(){
            for(int i = 0; i < Line.length(); i++){
                Line[i] = std::toupper(Line[i]);
            }
        }
        void ToLower(){
            for(int i = 0; i < Line.length(); i++){
                Line[i] = std::tolower(Line[i]);
            }
        }
        void first_to_upper(){
            ToLower();
            bool up = false;
            for(int i = 0; i < Line.length(); i++){
                if(!up && !isspace(Line[i]) && isalpha(Line[i])){
                    up = true;
                    Line[i] = std::toupper(Line[i]);
                }
                if(isspace(Line[i])){
                    up = false;
                }
            }
        }
        void first_to_lower(){
            ToUpper();
            bool low = false;
            for(int i = 0; i < Line.length(); i++){
                if(!low && !isspace(Line[i]) && isalpha(Line[i])){
                    low = true;
                    Line[i] = std::tolower(Line[i]);
                }
                if(isspace(Line[i])){
                    low = false;
                }
            }
        }
        void first_symbol_to_upper(){
            ToLower();
            Line[0] = std::toupper(Line[0]);
        }
        std::string get_line(){
            return Line;
        }
        private:

        std::string Line;

    };

    std::string line;
    std::cout << "Input line: ";
    std::getline(std::cin >> std::ws, line);
    String_manipulation temp;
    bool test = temp.set_new_line(line);
    if(!test){
        std::cout << "Line largest then 255 symbols" << std::endl;
        Console_getChar();
        return;
    }
    char choose = 0;
    std::string Text = {"To Upper - 1\nTo Lower - 2\nFirst to upper - 3\nFirst to lower - 4\nFirst symbol to upper - 5\nExit - f\n"};

    while(1){
        switch(choose){
            case '1':{
                temp.ToUpper();
                std::cout << temp.get_line() << std::endl << Text << std::endl;
                break;
            }
            case '2':{
                temp.ToLower();
                std::cout << temp.get_line() << std::endl << Text << std::endl;
                break;
            }
            case '3':{
                temp.first_to_upper();
                std::cout << temp.get_line() << std::endl << Text << std::endl;
                break;
            }
            case '4':{
                temp.first_to_lower();
                std::cout << temp.get_line() << std::endl << Text << std::endl;
                break;
            }
            case '5':{
                temp.first_symbol_to_upper();
                std::cout << temp.get_line() << std::endl << Text << std::endl;
                break;
            }
            case 'f':{
                Console_getChar();
                return;
            }
            default:{
                temp.first_symbol_to_upper();
                std::cout << temp.get_line() << std::endl << Text << std::endl;
                break;
            }
        }
        std::cin >> choose;
        CIN_ELIMINATION_ERROR(true)
    }
}
void Array_rand(){
    double Array[10][10];
    double a;
    double b;
    int min;
    int str;
    double swap_buffer;

    std::cout << "Input a: ";
    std::cin >> a;
    CIN_ELIMINATION_ERROR(true)
    std::cout << "Input b: ";
    std::cin >> b;
    CIN_ELIMINATION_ERROR(true)


    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            Array[i][j] = (static_cast<double>(rand()) / RAND_MAX) * (b - a) + a;
        }
    }
    std::cout << "Array:\n";
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            std::cout << Array[i][j] << " ";
        }
        std::cout << std::endl;
    }

    min = Array[0][0];
    str = 0;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(min > Array[i][j]){
                min = Array[i][j];
                str = i;
            }
        }
    }

    for(int i = 0; i < 10; i++){
        swap_buffer = Array[0][i];
        Array[0][i] = Array[str][i];
        Array[str][i] = swap_buffer;
    }
    std::cout << "Swap:\n";
     for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            std::cout << Array[i][j] << " ";
        }
        std::cout << std::endl;
    }
    Console_getChar();
}
void test_map(){
    std::string line;
    std::map <char, int> Line_map;

    std::cout << "Input line: ";
    std::getline(std::cin >> std::ws, line);

    for(int i = 0; i < line.length(); i++){
        Line_map[line[i]]++;
    }

    for(auto pointer = Line_map.begin(); pointer != Line_map.end(); pointer++){
        std::cout << pointer->first << "\t" << pointer-> second << std::endl;
    }
    Console_getChar();
}
void search_in_array(){
    int size;
    std::cout << "Input array size: ";
    std::cin >> size;
    CIN_ELIMINATION_ERROR(true)

    int *Array = new int[size];
    std::cout << "Array: ";
    for(int i = 0; i < size; i++){
        Array[i] = rand()%100;
        std::cout << Array[i] << " ";
    }
    std::cout << "\nResult: ";
    for(int i = 0; i < size; i++){
        if(Array[i] % 2 != 0){
            std::cout << Array[i] << " ";
        }
    }
    Console_getChar();
}
void schedule(){
    class Schedule{
    /////Private DATA///
    private:
    int curr_id = 0;
    std::vector <int> deleted_id;
    struct Data{
        std::string name;
        std::string last_name;
        double time;
        std::string position;
        double salary_per_hour;
        int id;
        double salary;
    };

    std::vector <Data> Data_vector;
    /////////////////////////////

    public:
    Schedule(){}
    ~Schedule(){}

    bool check_iter(std::vector<struct Data>::iterator iter){
        if(iter == Data_vector.end()){
            return false;
        }
        return true;
    }

    void add_new_worker(){
        struct Data temp;
        std::cout << "Input first name: ";
        std::getline(std::cin >> std::ws, temp.name);
        std::cout << "Input last name: ";
        std::getline(std::cin >> std::ws, temp.last_name);
        std::cout << "Input position: ";
        std::getline(std::cin >> std::ws, temp.position);
        std::cout << "Input work time: ";
        std::cin >> temp.time;
        CIN_ELIMINATION_ERROR(true)
        std::cout << "Input salary per hour: ";
        std::cin >>  temp.salary_per_hour;
        CIN_ELIMINATION_ERROR(true)
        if(deleted_id.empty()){
            temp.id = curr_id;
            curr_id++;
        }
        else{
            temp.id = *deleted_id.begin();
            deleted_id.erase(deleted_id.begin());
        }

        temp.salary = temp.time * temp.salary_per_hour;
        Data_vector.push_back(temp);

    }
    void Edit(){
        std::vector<Data>::iterator iter;
        int choose;

        show();
        std::cout << "Input id for edit: ";
        std::cin >> choose;
        CIN_ELIMINATION_ERROR(true)
        iter = find(choose);
        if(iter == Data_vector.end()){
            std::cout << "Incorrect id\n";
            return;
        }
        show(iter);
        std::cout << "Edit name?(1 to edit or 0 to continue)\n";
        std::cin >> choose;
        CIN_ELIMINATION_ERROR(true)
        if(choose == 1){
            std::cout << "Input first name: ";
            std::getline(std::cin >> std::ws, iter->name);
            std::cout << "Input last name: ";
            std::getline(std::cin >> std::ws, iter->last_name);
        }
        std::cout << "Edit position?(1 to edit or 0 to continue)\n";
        std::cin >> choose;
        CIN_ELIMINATION_ERROR(true)
        if(choose == 1){
            std::cout << "Input position: ";
            std::getline(std::cin >> std::ws, iter->position);
        }
        std::cout << "Edit salary per hour?(1 to edit or 0 to continue)\n";
        std::cin >> choose;
        CIN_ELIMINATION_ERROR(true)
        if(choose == 1){
            std::cout << "Input salary per hour: ";
            std::cin >> iter->salary_per_hour;
            CIN_ELIMINATION_ERROR(true)
            iter->salary = iter->salary_per_hour * iter->time;
        }
        std::cout << "Edit time?(1 to edit or 0 to continue)\n";
        std::cin >> choose;
        CIN_ELIMINATION_ERROR(true)
        if(choose == 1){
            std::cout << "Input time: ";
            std::cin >> iter->time;
            CIN_ELIMINATION_ERROR(true)
            iter->salary = iter->salary_per_hour * iter->time;
        }
    }

    void show(){
        for(auto iter = Data_vector.begin(); iter != Data_vector.end(); iter++){
           printf("\nName: %s\nLast name: %s\nTime: %fHours\nPosition: %s\nSalary per hour: %f$\nId: %d\nSalary: %f$\n",
           iter->name.c_str(), iter->last_name.c_str(), iter->time, iter->position.c_str(),
           iter->salary_per_hour, iter->id, iter->salary);
        }
    }
    void show(std::vector<struct Data>::iterator iter){
        printf("\nName: %s\nLast name: %s\nTime: %f Hours\nPosition: %s\nSalary per hour: %f$\nId: %d\nSalary: %f$\n",
           iter->name.c_str(), iter->last_name.c_str(), iter->time, iter->position.c_str(),
           iter->salary_per_hour, iter->id, iter->salary);
    }
    std::vector<struct Data>::iterator find(int id){
        std::vector<Data>::iterator iter;
        for(iter = Data_vector.begin(); iter != Data_vector.end(); iter++){
            if(iter->id == id){
                return iter;
            }
        }
        return iter;
    }
    void Delete(){
        show();
        int id;
        std::cout << "Input id for delete: ";
        std::cin >> id;
        CIN_ELIMINATION_ERROR(true)
        auto iter = find(id);
        if(iter == Data_vector.end()){
            std::cout << "Incorrect id\n";
            return;
        }
        Data_vector.erase(iter);
        deleted_id.push_back(id);
    }
    void read_from_file(){
        std::ifstream file("data.txt", std::ios::binary);
        while(!file.eof()){
            struct Data temp;
            std::string buff;
            std::getline(file, temp.name);
            std::getline(file, temp.last_name);
            std::getline(file, temp.position);
            std::getline(file, buff);
            temp.id = atoi(buff.c_str());
            std::getline(file, buff);
            temp.salary_per_hour = atof(buff.c_str());
            std::getline(file, buff);
            temp.salary = atof(buff.c_str());
            std::getline(file, buff);
            temp.time = atof(buff.c_str());
            Data_vector.push_back(temp);
        }
        Data_vector.erase(Data_vector.end() - 1);
        file.close();
    }
    void save_to_file(){
        std::ofstream file("data.txt", std::ios::binary);
        for(auto iter = Data_vector.begin(); iter != Data_vector.end(); iter++){
            file << iter->name << "\n";
            file << iter->last_name << "\n";
            file << iter->position << "\n";
            file << iter->id << "\n";
            file << iter->salary_per_hour << "\n";
            file << iter->salary << "\n";
            file << iter->time << "\n";
        }
        file.close();
    }

    void bubble_sort(){
        struct Data temp;
        for(int i = 0; i < Data_vector.size() - 1; i++){
            for(int j = 0; j < Data_vector.size() - 1 - i; j++){
                if(Data_vector[j].id < Data_vector[j + 1].id){
                    temp = Data_vector[j];
                    Data_vector[j] = Data_vector[j + 1];
                    Data_vector[j + 1] = temp;
                }
            }
        }
    }
    void shell_sort(){
        int j;
        struct Data temp;
        for(int step = Data_vector.size()/2; step > 0; step = step/2){
            for(int i =  step; i < Data_vector.size(); i++){
                temp = Data_vector[i];
                for(j = i; j >= step; j = j - step){
                    if(temp.id < Data_vector[j - step].id){
                        Data_vector[j] = Data_vector[j - step];
                    }
                    else{
                        break;
                    }
                }
                Data_vector[j] = temp;
            }
        }
    }

    void quick_sort(int left, int right){
        int i = left;
        int j = right;

        struct Data temp;

        int pivot = Data_vector[(left + right) / 2].id;

        while(i <= j){
            while(Data_vector[i].id < pivot){
                i++;
            }
            while(Data_vector[j].id > pivot){
                j--;
            }
            if(i <= j){
                temp = Data_vector[i];
                Data_vector[i] = Data_vector[j];
                Data_vector[j] = temp;
                i++;
                j--;
            }
        }
        if(left < j){
            quick_sort(left, j);
        }
        if(i < right){
            quick_sort(i, right);
        }

    }
    void quick_sort_sel(){
        quick_sort(0, Data_vector.size() - 1);
    }
    };



    Schedule temp;
    char choose;

    while(1){
        Console_clear();
        Console_clear();
        std::cout << "N - new worker\nE - edit data\nF - fild worker\n"
                  << "D - delete data\nS - save to file\nR - load from file\n"
                  << "V - Show all workers\nC - sort data\nQ - quit\nInput: ";
        std::cin >> choose;
        CIN_ELIMINATION_ERROR(false)
        if(choose == 'n' || choose == 'N'){
            temp.add_new_worker();
            Console_getChar();
        }
        else if(choose == 'e' || choose == 'E'){
            temp.Edit();
            Console_getChar();
        }
        else if(choose == 'f' || choose == 'F'){
            std::cout << "Input id: ";
            int id;
            std::cin >> id;
            CIN_ELIMINATION_ERROR(true)
            auto iter = temp.find(id);
            if(temp.check_iter(iter)){
                temp.show(iter);
            }
            Console_getChar();
        }
        else if(choose == 'd' || choose == 'D'){
            temp.Delete();
            Console_getChar();
        }
        else if(choose == 's' || choose == 'S'){
            temp.save_to_file();
        }
        else if(choose == 'r' || choose == 'R'){
            temp.read_from_file();
        }
        else if(choose == 'v' || choose == 'V'){
            temp.show();
            Console_getChar();
        }
        else if(choose == 'c' || choose == 'C'){
            int choose;
            std::cout << "1 - bubble\n2-shell\n3-quick\n";
            std::cin >> choose;
            CIN_ELIMINATION_ERROR(true)

            switch(choose){
                case 1:{
                    temp.bubble_sort();
                    break;
                }
                case 2:{
                    temp.shell_sort();
                    break;
                }
                case 3:{
                    temp.quick_sort_sel();
                    break;
                }
                default:{
                    std::cout << "Back\n";
                    break;
                }
            }
        }
        else if(choose == 'q' || choose == 'Q'){
            return;
        }
        else {
            std::cout << "Error\nInput: ";
        }
    }
}
void _time(){
    struct time{
        void input(){
            std::cout << "Hour: ";
            std::cin >> hour;
            CIN_ELIMINATION_ERROR(true)
            std::cout << "Min: ";
            std::cin >> min;
            CIN_ELIMINATION_ERROR(true)
            std::cout << "Sec: ";
            std::cin >> sec;
            CIN_ELIMINATION_ERROR(true)
        }
        void func(){
            result = sec + hour*3600 + min*60;
        }
        bool cmp(int second){
            if(result >= second){
                return true;
            }
            else{
                return false;
            }
        }
        void to_time(){
            hour = result/3600;
            min = result/60 - hour*60;
            sec = result - min*60 - hour*3600;
        }
        void print(){
            printf("Time: %d:%d.%d", hour, min, sec);
        }
        int hour;
        int min;
        int sec;

        int result;
    };

    struct time temp;
    int interval;

    temp.input();
    temp.func();

    std::cout << "timer in sec: ";
    std::cin >> interval;
    CIN_ELIMINATION_ERROR(true)

    if(temp.cmp(interval)){
        temp.result = temp.result - interval;
        temp.to_time();
        temp.print();
        std::cout << std::endl;
    }
    else{
        std::cout << "Time end\n";
    }

    std::cout << "New time: \n";
    temp.input();
    struct time second;
    std::cout << "Second time:\n";
    second.input();
    temp.func();
    second.func();

    std::cout << "Time: " << abs(temp.result - second.result) << std::endl;


    Console_getChar();

}
void employee(){
    class Employee{
        private:
        std::string lname;
        int stage;
        double hsalary;
        double time;

        double salary;
        double premy;
        std::string defaultFileName = "Data.txt";

        using json = nlohmann::json;


        void calculate_salary(){
            salary = hsalary*time;
        }
        void calculate_premy(){
            if(stage >= 1 || stage <= 3){
                premy = (salary/100)*5;
            }
            else if(stage > 3 || stage <= 5){
                premy = (salary/100)*8;
            }
            else if(stage > 5){
                premy = (salary/100)*15;
            }
            else {
                premy = 0;
            }
        }
        void set_json_file(json &temp){
            temp["lname"] = lname;
            temp["hsalary"] = hsalary;
            temp["stage"] = stage;
            temp["time"] = time;
            temp["salary"] = salary;
            temp["premy"] = premy;
        }
        void set_data_from_json_file(json const &temp){
            lname = temp["lname"];
            hsalary = temp["hsalary"];
            stage = temp["stage"];
            time = temp["time"];
            salary = temp["salary"];
            premy = temp["premy"];
        }
        public:

        Employee(){}
        Employee(std::ifstream &file){}
        Employee(std::string _name, int _stage, double _hsalary, double _time){
            lname = _name;
            stage = _stage;
            hsalary = _hsalary;
            time = _time;
            calculate_salary();
            calculate_premy();
        }
        ~Employee(){}

        void set_data(){
            std::cout << "Input last name: ";
            std::getline(std::cin >> std::ws, lname);
            std::cout << "Input experience: ";
            std::cin >> stage;
            CIN_ELIMINATION_ERROR(true)
            std::cout << "Input salary per hour: ";
            std::cin >> hsalary;
            CIN_ELIMINATION_ERROR(true)
            std::cout << "Input time: ";
            std::cin >> time;
            CIN_ELIMINATION_ERROR(true)
            calculate_salary();
            calculate_premy();
        }

        void print(){
            json temp;
            set_json_file(temp);
            std::cout << temp.dump(4) << std::endl;
        }
        void save_to_file(){
            json temp;
            set_json_file(temp);
            std::ofstream file(defaultFileName);
            file << temp.dump(4);
            file.close();
        }
        void get_data_from_file(){
            json temp;
            std::ifstream file(defaultFileName);
            std::stringstream buff;
            if(file.is_open()){
                buff << file.rdbuf();
                temp = json::parse(buff.str());
                set_data_from_json_file(temp);
                file.close();
            }
            else{
                std::cout << "Error file is not open\n";
            }
        }
        void get_data_from_file(std::ifstream &file){

            if(!file.is_open()){
                std::cout << "Error your file is not open.. open default save file\n";
                get_data_from_file();
            }
            else{
                json temp;
                std::stringstream buff;
                buff << file.rdbuf();
                temp = json::parse(buff.str());
                set_data_from_json_file(temp);
            }
        }

    };

    Employee temp("Jhon", 3, 1000, 2344);
    temp.print();
    temp.save_to_file();

    temp.set_data();
    temp.print();
    temp.get_data_from_file();
    temp.print();

    Console_getChar();
}
void two_to_one(){
    int **mat;
    int *vec;
    int n;
    int m;
    int k = 0;

    std::cout << "Input N: ";
    std::cin >> n;
    CIN_ELIMINATION_ERROR(true)
    std::cout << "Input M: ";
    std::cin >> m;
    CIN_ELIMINATION_ERROR(true)

    mat = new int*[n];
    for(int i = 0; i < n; i++){
        mat[i] = new int[m];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            mat[i][j] = rand()%100;
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
    vec = new int[n*m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            vec[k] = mat[i][j];
            k++;
        }
    }

    for(int i = 0; i < n; i++){
        delete[] mat[i];
    }
    delete []mat;

    std::cout << std::endl;

    for(int i = 0; i < n*m; i++){
        std::cout << vec[i] << " ";
    }
    delete []vec;
    Console_getChar();
}
void strrow(){
    int **mat;
    int n;
    int I = 0;
    int J = 0;
    int buff;

    std::cout << "Input n: ";
    std::cin >> n;

    mat = new int*[n];
    for(int i = 0; i < n; i++){
        mat[i] = new int[n];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            mat[i][j] = rand()%10;
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(abs(mat[i][j]) > abs(mat[I][J])){
                I = i;
                J = j;
            }
        }
    }

    for(int i = 0; i < n; i++){
        buff = mat[n - 1][i];
        mat[n - 1][i] = mat[I][i];
        mat[I][i] = buff;
    }
    for(int i = 0; i < n; i++){
        buff = mat[i][0];
        mat[i][0] = mat[i][J];
        mat[i][J] = buff;
    }
    std::cout << std::endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
    Console_getChar();
}
void letter(){
    const char glas[] = "AEIOUYaeiouy";
    const char sogl[] = "BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz";
    std::string line;
    std::cout << "Input line: ";
    std::getline(std::cin >> std::ws, line);

    for(int i = 0; i < line.length(); i++){
        if(std::strchr(sogl, line[i]) != NULL){
            std::cout << glas[rand()%12];
        }
        else if(std::strchr(glas, line[i]) != NULL){
            std::cout << static_cast<int>(line[i]);
        }
    }

    Console_getChar();
}
void nalog(){
    double salary;
    double nalog;
    std::cout << "Input your salary: ";
    std::cin >> salary;
    CIN_ELIMINATION_ERROR(true)

    nalog = (salary/100) *18;
    std::cout << "Nalog: " << nalog;
    Console_getChar();
}
void question(){
    std::string name;
    int choose;
    std::cout << "Year of birth of Nikolai Vasilyevich Gogol - 1809?(1 - yes, 0 - no)";
    std::cin >> choose;
    CIN_ELIMINATION_ERROR(true)
    while(choose != 1){
        std::cout << "Think num end 09\n";
        std::cin >> choose;
    }
    std::cout << "Input your name: ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "You win, " << name << std::endl << "Congrats, " << name << std::endl;
    Console_getChar(); 
}
void lettersc(){
    class let{
    private:
        int result = 1;
        std::string data;
        std::string menu = "1 - Enter string\n2 - process the data\n3 - see result\n0 - exit\n";
        void Input(){
            std::cout << "Input string: ";
            std::getline(std::cin >> std::ws, data);
        }
        void Find(){
            int buff = 1;
            
            for(int i = 0; i < data.length() - 1; i++){
                if(data[i] == data[i + 1]){
                    buff++;
                }
                else{
                    if(buff > result){
                        result = buff;
                    }
                    buff = 1;
                }
            }
        }
        void print(){
            std::cout << "Result: " << result << std::endl;
        }
        void let_menu(){
            int choose = 1;
            while(choose != 0){
                std::cout << menu;
                std::cin >> choose;
                CIN_ELIMINATION_ERROR(false);
                switch (choose) {
                case 1: {
                    Input();
                    break;
                }
                case 2: {
                    Find();
                    break;
                }
                case 3: {
                    print();
                    break;
                }
                default: break;
                }
            }
        }
    public:
        let(){
            let_menu();
        }
        ~let(){}

    };
    let temp;
}
void param(){
    struct func{
        void Func(int d, int &k){
            std::string num;
            num = std::to_string(k);
            num = num + std::to_string(d);
            k = atoi(num.c_str());
        };
    };
    int k;
    int d;
    func temp;
    std::cout << "Input k: ";
    std::cin >> k;
    CIN_ELIMINATION_ERROR(true)
    std::cout << "Input d: ";
    std::cin >> d;
    CIN_ELIMINATION_ERROR(true)
    temp.Func(d, k);
    std::cout << "k: " << k << std::endl;
    std::cout << "Input d: ";
    std::cin >> d;
    CIN_ELIMINATION_ERROR(true)
    temp.Func(d, k);
    std::cout << "k: " << k << std::endl;
    Console_getChar();
}
void raz_matrix(){
    std::cout << "Coming soon\n";
}
void compet(){
    double Array[5][3];
    std::vector<std::pair<double, double>> best;
    double best_result = 0;
    best.push_back(std::make_pair(0, 0));
    
    auto iter = best.begin();
    std::cout << "Input results:\n";

    for(int i = 0; i < 5; i++){
        std::cout << "Copetitor " << i + 1 << ": ";
        std::cin >> Array[i][0];
        CIN_ELIMINATION_ERROR(false); 
        std::cin >> Array[i][1];
        CIN_ELIMINATION_ERROR(false);
        std::cin >> Array[i][2];
        CIN_ELIMINATION_ERROR(false);
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 3; j++){
            if(best_result < Array[i][j]){
                iter->first = i;
                iter->second = j;
                best_result = Array[i][j];
            }
        }
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 3; j++){
            if(best_result == Array[i][j]){
                bool flag = false;
                for(iter = best.begin(); iter != best.end(); iter++){
                    if(iter->first == i && iter->second == j){
                        flag = true;
                    }
                }
                if(!flag){
                    best.push_back(std::make_pair(i, j));
                }
            }
        }
    }
    for(iter = best.begin(); iter != best.end(); iter++){
        std::cout << "Competitor " << iter->first << " Result: " << iter->second << std::endl;    
    }
    Console_getChar();
}
void max_len(){
    struct Cmp{
        static bool line_cmp(const std::string &a, const std::string &b){    
            if(a.length() > b.length()){
                return true;
            }
        return false;
        }
    };
    std::vector<std::string> line;
    std::string t;
    std::string str;
    std::cout << "Input string: ";
    std::getline(std::cin >> std::ws, str);
    for(int i = 0; i < str.length(); i++){
        if(!isspace(str[i])){
            t = t + str[i];
        }
        else{
            if(!t.empty()){
                line.push_back(t);
                t.clear();
            }
        }
    }
    if(!t.empty()){
        line.push_back(t);
    }

    Cmp temp;
    std::sort(line.begin(), line.end(), temp.line_cmp);
    for(auto iter = line.begin(); iter != line.end(); iter++){
        std::cout << *iter << std::endl;
    }
    std::cout << "\n\n";
    std::cout << *line.begin();
    Console_getChar();
}
void min_len(){
    struct Cmp{
        static bool line_cmp(const std::string &a, const std::string &b){    
            if(a.length() < b.length()){
                return true;
            }
        return false;
        }
    };
    std::vector<std::string> line;
    std::string t;
    std::string str;
    std::cout << "Input string: ";
    std::getline(std::cin >> std::ws, str);
    for(int i = 0; i < str.length(); i++){
        if(!isspace(str[i])){
            t = t + str[i];
        }
        else{
            if(!t.empty()){
                line.push_back(t);
                t.clear();
            }
        }
    }
    if(!t.empty()){
        line.push_back(t);
    }

    Cmp temp;
    std::sort(line.begin(), line.end(), temp.line_cmp);
    for(auto iter = line.begin(); iter != line.end(); iter++){
        std::cout << *iter << std::endl;
    }
    std::cout << "\n\n";
    std::cout << *line.begin();
    Console_getChar();
}
