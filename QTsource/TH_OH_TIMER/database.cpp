#include "database.h"
#include <cstdio>

DataBase::DataBase() {
    check_files();
}

DataBase::~DataBase() {
    push_on_file();
}

bool DataBase::add_new_time(QString time, int curr, QString &temp) {
    data.push_back(time);
    int_data.push_back(curr);
    temp = temp + time + "\n";
    if(best_result == 0){
        best_result = curr;
        return true;
    }
    else if(best_result > curr){
        best_result = curr;
        return true;
    }
    return false;
}

int DataBase::get_best() {
    return best_result;
}

void DataBase::get_all_results(QString &temp) {
    std::ifstream dat(get_session_filename());
    std::string line;
    while(!dat.eof()){
        std::getline(dat, line);
        temp = temp + QString::fromStdString(line) + "\n";
        data.push_back(QString::fromStdString(line));
    }
    dat.close();
    temp.resize(temp.length() - 1);
    auto i = data.end();
    i--;
    data.erase(i);
    get_int_data();
}

bool DataBase::delete_last_result(QString &temp) {
    if(int_data.size() == 0){
        return false;
    }
    auto i = data.end();
    i--;
    int len = i->length();
    data.erase(i);
    temp.resize(temp.length() - len - 1);
    auto p = int_data.end();
    p--;
    int_data.erase(p);
    find_best();
    if(int_data.size() == 0){
        return false;
    }
    else{
        return true;
    }
}

void DataBase::find_best() {
    long long best = int_data[0];
    for(unsigned long long i = 0; i < int_data.size(); i++){
        if(int_data[i] < best){
            best = int_data[i];
        }
    }
    if(int_data.size() == 0){
        best = 0;
    }
    best_result = (int)best;
}

void DataBase::change_session(int temp) {
    push_on_file();
    int_data.clear();
    data.clear();
    session = temp;
}

long double DataBase::get_12_avg() {
    if(int_data.size() < 12){
        return 0;
    }
    unsigned long int max = int_data[0];
    unsigned long int min = int_data[0];
    unsigned long int num = 0;
    for(unsigned long long i = int_data.size() - 12; i < int_data.size(); i++){
        if(max < int_data[i]){
            max = int_data[i];
        }
        if(min > int_data[i]){
            min = int_data[i];
        }
        num = num + int_data[i];
    }
    num = num - min - max;
    long double time = (long double)num/(long double)10;
    return time;
}

long double DataBase::get_5_avg() {
     if(int_data.size() < 5){
        return 0;
    }
    unsigned long int max = int_data[0];
    unsigned long int min = int_data[0];
    unsigned long int num = 0;
    for(unsigned long long i = int_data.size() - 5; i < int_data.size(); i++){
        if(max < int_data[i]){
            max = int_data[i];
        }
        if(min > int_data[i]){
            min = int_data[i];
        }
        num = num + int_data[i];
    }
    num = num - min - max;
    long double time = (long double)num/(long double)3;
    return time;
}

long double DataBase::get_sesion_mean() {
    long double num = 0;
    for(unsigned long long i = 0; i < int_data.size(); i++){
        num = num + int_data[i];
    }
    num = num/(long double)int_data.size();
    return num;
}

long double DataBase::get_100() {
    if(int_data.size() < 100){
        return 0;
    }
    
}

int DataBase::get_count_of_results() {
    return int_data.size();
}

int DataBase::get_session() {
    return session;
}

QString DataBase::get_puzzle() {
    return puzzle;
}

void DataBase::set_puzzle(QString temp) {
    puzzle = temp;
}

void DataBase::delete_files() {
    change_session(1);
    std::string str;
    str = get_session_filename();
    remove(str.c_str());
    str = "int_" + str;
    remove(str.c_str());
    change_session(2);
    str = get_session_filename();
    remove(str.c_str());
    str = "int_" + str;
    remove(str.c_str());
    change_session(3);
    str = get_session_filename();
    remove(str.c_str());
    str = "int_" + str;
    remove(str.c_str());
    change_session(4);
    str = get_session_filename();
    remove(str.c_str());
    str = "int_" + str;
    remove(str.c_str());
    change_session(5);
    str = get_session_filename();
    remove(str.c_str());
    str = "int_" + str;
    remove(str.c_str());
    check_files();
}

void DataBase::delete_files(int session) {
    std::string str;
    std::ofstream file;
    str = get_session_filename();
    remove(str.c_str());
    file.open(str, std::ofstream::app);
    file.close();
    str = "int_" + str;
    remove(str.c_str());
    file.open(str, std::ofstream::app);
    file.close();
}

void DataBase::set_session(int Session) {
    session = Session;
}

void DataBase::push_on_file() {
    std::string str = "int_"+ get_session_filename();
    std::ofstream dat(get_session_filename());
    for(unsigned long long i = 0; i < data.size(); i++){
        dat << data[i].QString::toStdString() << "\n";
    }
    dat.close();
    
    dat.open(str);
    for(unsigned long long i = 0; i < int_data.size(); i++){
        dat << int_data[i] << "\n";
    }
    dat.close();
}

void DataBase::get_int_data() {
    std::string str = "int_"+ get_session_filename();
    std::ifstream dat(str);
    std::string line;
    while(!dat.eof()){
        std::getline(dat, line);
        int_data.push_back(atoi(line.c_str()));
    }
    dat.close();
    auto i = int_data.end();
    i--;
    int_data.erase(i);
}

std::string DataBase::get_session_filename() {
    std::string filenames[] = {"session1.dat", "session2.dat", "session3.dat", "session4.dat", "session5.dat"};
    return filenames[session - 1]; 
}

void DataBase::check_files() {
    set_session(1);
    std::string str;
    std::ofstream file;
    str = get_session_filename();
    file.open(str, std::ofstream::app);
    file.close();
    str = "int_" + str;
    file.open(str, std::ofstream::app);
    file.close();
    session++;
    str = get_session_filename();
    file.open(str, std::ofstream::app);
    file.close();
    str = "int_" + str;
    file.open(str, std::ofstream::app);
    file.close();
    session++;
    str = get_session_filename();
    file.open(str, std::ofstream::app);
    file.close();
    str = "int_" + str;
    file.open(str, std::ofstream::app);
    file.close();
    session++;
    str = get_session_filename();
    file.open(str, std::ofstream::app);
    file.close();
    str = "int_" + str;
    file.open(str, std::ofstream::app);
    file.close();
    session++;
    str = get_session_filename();
    file.open(str, std::ofstream::app);
    file.close();
    str = "int_" + str;
    file.open(str, std::ofstream::app);
    file.close();
    session = 1;
}
