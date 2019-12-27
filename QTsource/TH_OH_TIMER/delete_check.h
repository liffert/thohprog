#ifndef DELETE_CHECK_H
#define DELETE_CHECK_H

#include <QDialog>

namespace Ui {
class Delete_check;
}

class Delete_check : public QDialog
{
    Q_OBJECT
    
public:
    explicit Delete_check(QWidget *parent = nullptr);
    ~Delete_check();
    
private:
    Ui::Delete_check *ui;
};

#endif // DELETE_CHECK_H
