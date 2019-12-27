#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QMessageBox>
#include "check_delete.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_timer()));
    database.get_all_results(ALL);
    set_output(ALL);
    database.find_best();
    set_best(database.get_best(), false);
    database.set_puzzle("3x3 Cube");
    set__PS();
}

MainWindow::~MainWindow() {
    delete ui;
}

QString MainWindow::microseconds_to_QString(int microseconds) {
    if (microseconds == 0){
        return "NONE";
    }
    int min;
    int sec;
    int mil;
    int h;
    sec = microseconds/1000;
    min = sec/60;
    h = min/60;
    min = min - h*60;
    sec = sec - min*60;
    mil = microseconds - sec*1000 - min*60000;
    QTime te;
    te.setHMS(h, min, sec, mil);
    QString str = te.toString("hh::mm:ss.zzz");
    return str;
}

void MainWindow::set_best(const int time, bool flag) {
    ui->Best_result->setText("Best: " + microseconds_to_QString(time) + "\n\nAVG 5: " + microseconds_to_QString(database.get_5_avg()) + "\n\nAVG12: " + microseconds_to_QString(database.get_12_avg()) + "\n\nAVG100: " 
                             + microseconds_to_QString(database.get_100()) + "\n\nSession mean: " + microseconds_to_QString(database.get_sesion_mean()) + "\n\nIN SESSION: " 
                             + QString::number(database.get_count_of_results()) + " solves");
    if(!flag){return;}
    ui->label->setText(microseconds_to_QString(time) + "\nNEW BEST");
}

void MainWindow::set_output(const QString &temp) {
    ui->Output->setText(temp);
}

void MainWindow::set__PS() {
    ui->StatusBar->setText("Session: " + QString::number(database.get_session()) + " Puzzle: " + database.get_puzzle());
}

void MainWindow::change_session(int session) {
    ui->label->setText("Press SPACE to start");
    database.change_session(session);
    ALL = "Results:\n";
    database.get_all_results(ALL);
    set_output(ALL);
    database.find_best();
    set_best(database.get_best(), false);
    set__PS();
}

bool MainWindow::update_status() {
    ready_to_start = !ready_to_start;
    return  ready_to_start;
}

void MainWindow::update_timer() {
    int temp = time.elapsed();
    ui->label->setText(microseconds_to_QString(temp));
}
void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if(event->isAutoRepeat()){
        return;
    }
    if(event->key() == Qt::Key_Space){
        if(update_status()){
           time.setHMS(0,0,0,0);
           timer->start(1);
           time.start();
        }
        else{
            int curr = time.elapsed();
            timer->stop();
            QString str = microseconds_to_QString(curr);
            ui->label->setText(str);
            bool flag = database.add_new_time(str, curr, ALL);
            set_best(database.get_best(), flag);
            set_output(ALL);
        }
    }
    else if(event->key() == Qt::Key_Delete){
        on_Delete_clicked();
    }
    qDebug() << "Press\n";
}

void MainWindow::on_actionSession_one_triggered() {
    change_session(1);
}

void MainWindow::on_actionSession_two_triggered() {
    change_session(2);
}

void MainWindow::on_actionSession_three_triggered() {
   change_session(3);
}

void MainWindow::on_actionSession_4_triggered() {
   change_session(4);
}

void MainWindow::on_actionSession_5_triggered() {
  change_session(5);
}

void MainWindow::on_action2x2_triggered() {
    database.set_puzzle("2x2 Cube");
    set__PS();
}

void MainWindow::on_Delete_clicked() {
    Check_delete temp;
    temp.set_text(1);
    if(temp.exec()){
        ui->label->setText("Press SPACE to start");
        database.delete_last_result(ALL);
        set_output(ALL);
        set_best(database.get_best(), false);
    }
    setFocus();
}
void MainWindow::on_DeleteSession_clicked() {
    Check_delete temp;
    temp.set_text(2);
    if(temp.exec()){
        ui->label->setText("Press SPACE to start");
        while(database.delete_last_result(ALL)){};
        //database.delete_files(database.get_session());
        set_output(ALL);
        set_best(database.get_best(), false);
    }
    setFocus();
}

void MainWindow::on_DeleteALL_clicked() {
    Check_delete temp;
    temp.set_text(3);
    if(temp.exec()){
        ui->label->setText("Press SPACE to start");
        int temp = database.get_session();
        for(int i = 1; i < 6; i++){
            change_session(i);
            while(database.delete_last_result(ALL)){}
        }
        //database.delete_files();
        change_session(temp);
    }
    setFocus();
}

void MainWindow::on_action3x3_triggered() {
    database.set_puzzle("3x3 Cube");
    set__PS();
}

void MainWindow::on_action4x4_triggered() {
    database.set_puzzle("4x4 Cube");
    set__PS();
}

void MainWindow::on_action5x5_triggered() {
    database.set_puzzle("5x5 Cube");
    set__PS();
}

void MainWindow::on_action6x6_triggered() {
    database.set_puzzle("6x6 Cube");
    set__PS();
}

void MainWindow::on_action7x7_triggered() {
    database.set_puzzle("7x7 Cube");
    set__PS();
}


void MainWindow::on_actionMegaminx_triggered() {
    database.set_puzzle("Megaminx");
    set__PS();
}

void MainWindow::on_actionPiraminx_triggered() {
    database.set_puzzle("Piraminx");
    set__PS();
}

void MainWindow::on_actionSkew_triggered() {
    database.set_puzzle("Skewb");
    set__PS();
}

void MainWindow::on_actionSquare_1_triggered() {
    database.set_puzzle("Square-1");
    set__PS();
}

void MainWindow::on_actionAnother_one_triggered() {
    database.set_puzzle("Another_one");
    set__PS();
}
