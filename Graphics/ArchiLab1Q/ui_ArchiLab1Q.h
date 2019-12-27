/********************************************************************************
** Form generated from reading UI file 'ArchiLab1Q.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARCHILAB1Q_H
#define UI_ARCHILAB1Q_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ArchiLab1QClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *ArchiLab1QClass)
    {
        if (ArchiLab1QClass->objectName().isEmpty())
            ArchiLab1QClass->setObjectName(QString::fromUtf8("ArchiLab1QClass"));
        ArchiLab1QClass->resize(600, 400);
        centralWidget = new QWidget(ArchiLab1QClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ArchiLab1QClass->setCentralWidget(centralWidget);

        retranslateUi(ArchiLab1QClass);

        QMetaObject::connectSlotsByName(ArchiLab1QClass);
    } // setupUi

    void retranslateUi(QMainWindow *ArchiLab1QClass)
    {
        ArchiLab1QClass->setWindowTitle(QCoreApplication::translate("ArchiLab1QClass", "ArchiLab1Q", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ArchiLab1QClass: public Ui_ArchiLab1QClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARCHILAB1Q_H
