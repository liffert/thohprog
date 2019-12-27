#ifndef CHECK_DELETE_H
#define CHECK_DELETE_H

#include <QDialog>

namespace Ui {
class Check_delete;
}

class Check_delete : public QDialog
{
    Q_OBJECT
    
public:
    void set_text(int Type);
    explicit Check_delete(QWidget *parent = nullptr);
    ~Check_delete();
    
private slots:
    void on_buttonBox_accepted();
    
private:
    Ui::Check_delete *ui;
    bool return_reply(bool reply);
};

#endif // CHECK_DELETE_H
