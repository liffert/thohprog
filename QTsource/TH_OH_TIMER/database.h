#ifndef DATABASE_H
#define DATABASE_H
#include <QMainWindow>
#include <vector>
#include <fstream>
#include <string>

class DataBase {
public:
    DataBase();
    ~DataBase();
    bool add_new_time(const QString time, const int curr, QString &temp);
    int get_best();
    void get_all_results(QString &temp);
    bool delete_last_result(QString &temp);
    void find_best();
    void change_session(int temp);
    long double get_12_avg();
    long double get_5_avg();
    long double get_sesion_mean();
    long double get_100();
    int get_count_of_results();
    int get_session();
    QString get_puzzle();
    void set_puzzle(QString temp);
    void delete_files();
    void delete_files(int session);
private:
    void set_session(int Session);
    std::vector <QString> data;
    std::vector <unsigned long int> int_data;
    void push_on_file();
    void get_int_data();
    QString output;
    int best_result = 0;
    int session = 1;
    std::string get_session_filename();
    void check_files();
    QString puzzle;
};

#endif // DATABASE_H
