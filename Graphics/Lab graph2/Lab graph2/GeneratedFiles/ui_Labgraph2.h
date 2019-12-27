/********************************************************************************
** Form generated from reading UI file 'Labgraph2.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LABGRAPH2_H
#define UI_LABGRAPH2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Labgraph2Class
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *scaleM;
    QPushButton *RotateL;
    QPushButton *RotateR;
    QPushButton *ScaleP;
    QVBoxLayout *verticalLayout;
    QLabel *label;

    void setupUi(QMainWindow *Labgraph2Class)
    {
        if (Labgraph2Class->objectName().isEmpty())
            Labgraph2Class->setObjectName(QString::fromUtf8("Labgraph2Class"));
        Labgraph2Class->resize(600, 400);
        centralWidget = new QWidget(Labgraph2Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scaleM = new QPushButton(centralWidget);
        scaleM->setObjectName(QString::fromUtf8("scaleM"));

        gridLayout->addWidget(scaleM, 2, 1, 1, 1);

        RotateL = new QPushButton(centralWidget);
        RotateL->setObjectName(QString::fromUtf8("RotateL"));

        gridLayout->addWidget(RotateL, 2, 0, 1, 1);

        RotateR = new QPushButton(centralWidget);
        RotateR->setObjectName(QString::fromUtf8("RotateR"));

        gridLayout->addWidget(RotateR, 2, 2, 1, 1);

        ScaleP = new QPushButton(centralWidget);
        ScaleP->setObjectName(QString::fromUtf8("ScaleP"));

        gridLayout->addWidget(ScaleP, 1, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        Labgraph2Class->setCentralWidget(centralWidget);

        retranslateUi(Labgraph2Class);

        QMetaObject::connectSlotsByName(Labgraph2Class);
    } // setupUi

    void retranslateUi(QMainWindow *Labgraph2Class)
    {
        Labgraph2Class->setWindowTitle(QCoreApplication::translate("Labgraph2Class", "Labgraph2", nullptr));
        scaleM->setText(QCoreApplication::translate("Labgraph2Class", "Scale -", nullptr));
        RotateL->setText(QCoreApplication::translate("Labgraph2Class", "Rotate -", nullptr));
        RotateR->setText(QCoreApplication::translate("Labgraph2Class", "Rotate +", nullptr));
        ScaleP->setText(QCoreApplication::translate("Labgraph2Class", "Scale+", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Labgraph2Class: public Ui_Labgraph2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABGRAPH2_H
