#include "check_delete.h"
#include "ui_check_delete.h"
#include <QPushButton>

void Check_delete::set_text(int Type) {
    switch (Type) {
    case 1:
        ui->label_2->setText("Delete result?");
        break;
    case 2:
        ui->label_2->setText("Delete session results?");
        break;
    case 3:
        ui->label_2->setText("Delete ALL result?");
        break;
    }
}

Check_delete::Check_delete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Check_delete)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Yes");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("No");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setStyleSheet("border: 1px solid black;border-radius: 10px;color: #ffffff;background-color: #8B0000;height: 50px;width: 100px");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setStyleSheet("border: 1px solid black;border-radius: 10px;color: #ffffff;background-color: #8B0000;height: 50px;width: 100px");
}

Check_delete::~Check_delete()
{
    delete ui;
}

bool Check_delete::return_reply(bool reply) {
    return reply;
}

void Check_delete::on_buttonBox_accepted() {
    
}
