/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *selepuerto;
    QLabel *label;
    QPushButton *botonpuerto;
    QPushButton *botoninicio;
    QPushButton *botonpara;
    QLabel *label_2;
    QCustomPlot *customPlot;
    QLineEdit *cajaVelocidad;
    QPushButton *botonVelocidad;
    QLabel *recepetor;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *cajaVolt;
    QLabel *label_5;
    QPushButton *botonvoltaje;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        selepuerto = new QComboBox(centralwidget);
        selepuerto->setObjectName(QString::fromUtf8("selepuerto"));
        selepuerto->setGeometry(QRect(70, 10, 75, 24));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 55, 16));
        botonpuerto = new QPushButton(centralwidget);
        botonpuerto->setObjectName(QString::fromUtf8("botonpuerto"));
        botonpuerto->setGeometry(QRect(150, 10, 80, 25));
        botoninicio = new QPushButton(centralwidget);
        botoninicio->setObjectName(QString::fromUtf8("botoninicio"));
        botoninicio->setGeometry(QRect(230, 10, 80, 25));
        botonpara = new QPushButton(centralwidget);
        botonpara->setObjectName(QString::fromUtf8("botonpara"));
        botonpara->setGeometry(QRect(310, 10, 80, 25));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 40, 55, 16));
        customPlot = new QCustomPlot(centralwidget);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setGeometry(QRect(30, 120, 591, 431));
        cajaVelocidad = new QLineEdit(centralwidget);
        cajaVelocidad->setObjectName(QString::fromUtf8("cajaVelocidad"));
        cajaVelocidad->setGeometry(QRect(80, 40, 113, 24));
        botonVelocidad = new QPushButton(centralwidget);
        botonVelocidad->setObjectName(QString::fromUtf8("botonVelocidad"));
        botonVelocidad->setGeometry(QRect(200, 40, 80, 25));
        recepetor = new QLabel(centralwidget);
        recepetor->setObjectName(QString::fromUtf8("recepetor"));
        recepetor->setGeometry(QRect(670, 120, 61, 21));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(280, 40, 211, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(630, 120, 55, 16));
        cajaVolt = new QLineEdit(centralwidget);
        cajaVolt->setObjectName(QString::fromUtf8("cajaVolt"));
        cajaVolt->setGeometry(QRect(80, 70, 111, 24));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 70, 55, 16));
        botonvoltaje = new QPushButton(centralwidget);
        botonvoltaje->setObjectName(QString::fromUtf8("botonvoltaje"));
        botonvoltaje->setGeometry(QRect(200, 70, 80, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "Puertos", nullptr));
        botonpuerto->setText(QApplication::translate("MainWindow", "Abrir", nullptr));
        botoninicio->setText(QApplication::translate("MainWindow", "Iniciar", nullptr));
        botonpara->setText(QApplication::translate("MainWindow", "Detener", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Velocidad", nullptr));
        botonVelocidad->setText(QApplication::translate("MainWindow", "Mandar", nullptr));
        recepetor->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Ingrese un valor entre -629 y 629", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "mm/s", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Voltaje", nullptr));
        botonvoltaje->setText(QApplication::translate("MainWindow", "Mandar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
