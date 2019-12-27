#include "delete_check.h"
#include "ui_delete_check.h"

Delete_check::Delete_check(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Delete_check)
{
    ui->setupUi(this);
}

Delete_check::~Delete_check()
{
    delete ui;
}
