#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QTime>
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString microseconds_to_QString(int microseconds);
   
private:
    Ui::MainWindow *ui;
    QTimer *timer = new QTimer(this);
    QTime time;
    DataBase database;
    QString ALL = "Results:\n";
    void set_best(const int time, bool flag = true);    
    void set_output(const QString &temp);
    void set__PS();
    void change_session(int session);
private slots:
    bool update_status();
    void update_timer();

    void on_actionSession_one_triggered();
    
    void on_actionSession_two_triggered();
    
    void on_actionSession_three_triggered();
    
    void on_actionSession_4_triggered();
    
    void on_actionSession_5_triggered();
    
    void on_action2x2_triggered();
    
    void on_Delete_clicked();
    
    void on_DeleteSession_clicked();
    
    void on_DeleteALL_clicked();
    
    void on_action3x3_triggered();
    
    void on_action4x4_triggered();
    
    void on_action5x5_triggered();
    
    void on_action6x6_triggered();
    
    void on_action7x7_triggered();
    
    void on_actionMegaminx_triggered();
    
    void on_actionPiraminx_triggered();
    
    void on_actionSkew_triggered();
    
    void on_actionSquare_1_triggered();
    
    void on_actionAnother_one_triggered();
    
protected:
    bool ready_to_start = false;
    virtual void keyReleaseEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
