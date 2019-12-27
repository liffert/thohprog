/********************************************************************************
** Form generated from reading UI file 'Lab4g.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB4G_H
#define UI_LAB4G_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lab4gClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QGridLayout *gridLayout_2;
    QPushButton *tri;
    QPushButton *rect;
    QPushButton *Ksnow;
    QPushButton *Kline;
    QPushButton *pap;
    QPushButton *man;
    QVBoxLayout *verticalLayout;
    QPushButton *lvlup;
    QPushButton *lvldw;
    QPushButton *RtP;
    QPushButton *RtM;

    void setupUi(QMainWindow *Lab4gClass)
    {
        if (Lab4gClass->objectName().isEmpty())
            Lab4gClass->setObjectName(QString::fromUtf8("Lab4gClass"));
        Lab4gClass->resize(800, 800);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Lab4gClass->sizePolicy().hasHeightForWidth());
        Lab4gClass->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(Lab4gClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tri = new QPushButton(centralWidget);
        tri->setObjectName(QString::fromUtf8("tri"));

        gridLayout_2->addWidget(tri, 1, 0, 1, 1);

        rect = new QPushButton(centralWidget);
        rect->setObjectName(QString::fromUtf8("rect"));

        gridLayout_2->addWidget(rect, 1, 1, 1, 1);

        Ksnow = new QPushButton(centralWidget);
        Ksnow->setObjectName(QString::fromUtf8("Ksnow"));

        gridLayout_2->addWidget(Ksnow, 0, 1, 1, 1);

        Kline = new QPushButton(centralWidget);
        Kline->setObjectName(QString::fromUtf8("Kline"));

        gridLayout_2->addWidget(Kline, 0, 0, 1, 1);

        pap = new QPushButton(centralWidget);
        pap->setObjectName(QString::fromUtf8("pap"));

        gridLayout_2->addWidget(pap, 2, 0, 1, 1);

        man = new QPushButton(centralWidget);
        man->setObjectName(QString::fromUtf8("man"));

        gridLayout_2->addWidget(man, 2, 1, 1, 1);


        gridLayout->addLayout(gridLayout_2, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lvlup = new QPushButton(centralWidget);
        lvlup->setObjectName(QString::fromUtf8("lvlup"));

        verticalLayout->addWidget(lvlup);

        lvldw = new QPushButton(centralWidget);
        lvldw->setObjectName(QString::fromUtf8("lvldw"));

        verticalLayout->addWidget(lvldw);

        RtP = new QPushButton(centralWidget);
        RtP->setObjectName(QString::fromUtf8("RtP"));

        verticalLayout->addWidget(RtP);

        RtM = new QPushButton(centralWidget);
        RtM->setObjectName(QString::fromUtf8("RtM"));

        verticalLayout->addWidget(RtM);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        Lab4gClass->setCentralWidget(centralWidget);

        retranslateUi(Lab4gClass);

        QMetaObject::connectSlotsByName(Lab4gClass);
    } // setupUi

    void retranslateUi(QMainWindow *Lab4gClass)
    {
        Lab4gClass->setWindowTitle(QCoreApplication::translate("Lab4gClass", "Lab4g", nullptr));
        tri->setText(QCoreApplication::translate("Lab4gClass", "Triangle", nullptr));
        rect->setText(QCoreApplication::translate("Lab4gClass", "Rect", nullptr));
        Ksnow->setText(QCoreApplication::translate("Lab4gClass", "Create koh snow", nullptr));
        Kline->setText(QCoreApplication::translate("Lab4gClass", "Create koh line", nullptr));
        pap->setText(QCoreApplication::translate("Lab4gClass", "Paporot", nullptr));
        man->setText(QCoreApplication::translate("Lab4gClass", "Mandelbrod", nullptr));
        lvlup->setText(QCoreApplication::translate("Lab4gClass", "Level up", nullptr));
        lvldw->setText(QCoreApplication::translate("Lab4gClass", "Level down", nullptr));
        RtP->setText(QCoreApplication::translate("Lab4gClass", "Rotate +30", nullptr));
        RtM->setText(QCoreApplication::translate("Lab4gClass", "Rotate -30", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lab4gClass: public Ui_Lab4gClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB4G_H
