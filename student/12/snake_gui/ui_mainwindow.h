/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QSlider *horizontalSliderHeight;
    QLabel *playgroundSize;
    QLabel *labelHeight;
    QLabel *labelWidth;
    QSlider *horizontalSliderWidth;
    QSpinBox *spinBoxSeed;
    QLabel *labelSeed;
    QLCDNumber *lcdNumberTime;
    QLabel *labelTime;
    QLabel *label_6;
    QLCDNumber *lcdNumberScore;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonPause;
    QPushButton *pushButtonReset;
    QPushButton *pushButtonClose;
    QLabel *labelGameEnd;
    QLineEdit *lineEditGameTag;
    QLabel *labelGameTag;
    QLabel *labelLeaderboard;
    QLabel *labelFirst;
    QLabel *labelSecond;
    QLabel *labelThird;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 256, 192));
        horizontalSliderHeight = new QSlider(centralwidget);
        horizontalSliderHeight->setObjectName(QString::fromUtf8("horizontalSliderHeight"));
        horizontalSliderHeight->setGeometry(QRect(560, 40, 160, 16));
        horizontalSliderHeight->setOrientation(Qt::Horizontal);
        playgroundSize = new QLabel(centralwidget);
        playgroundSize->setObjectName(QString::fromUtf8("playgroundSize"));
        playgroundSize->setGeometry(QRect(470, 10, 171, 20));
        labelHeight = new QLabel(centralwidget);
        labelHeight->setObjectName(QString::fromUtf8("labelHeight"));
        labelHeight->setGeometry(QRect(470, 40, 63, 20));
        labelWidth = new QLabel(centralwidget);
        labelWidth->setObjectName(QString::fromUtf8("labelWidth"));
        labelWidth->setGeometry(QRect(470, 70, 63, 20));
        horizontalSliderWidth = new QSlider(centralwidget);
        horizontalSliderWidth->setObjectName(QString::fromUtf8("horizontalSliderWidth"));
        horizontalSliderWidth->setGeometry(QRect(560, 70, 160, 16));
        horizontalSliderWidth->setOrientation(Qt::Horizontal);
        spinBoxSeed = new QSpinBox(centralwidget);
        spinBoxSeed->setObjectName(QString::fromUtf8("spinBoxSeed"));
        spinBoxSeed->setGeometry(QRect(730, 120, 45, 29));
        labelSeed = new QLabel(centralwidget);
        labelSeed->setObjectName(QString::fromUtf8("labelSeed"));
        labelSeed->setGeometry(QRect(600, 120, 121, 20));
        lcdNumberTime = new QLCDNumber(centralwidget);
        lcdNumberTime->setObjectName(QString::fromUtf8("lcdNumberTime"));
        lcdNumberTime->setGeometry(QRect(690, 160, 64, 23));
        labelTime = new QLabel(centralwidget);
        labelTime->setObjectName(QString::fromUtf8("labelTime"));
        labelTime->setGeometry(QRect(600, 160, 63, 20));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(600, 200, 63, 20));
        lcdNumberScore = new QLCDNumber(centralwidget);
        lcdNumberScore->setObjectName(QString::fromUtf8("lcdNumberScore"));
        lcdNumberScore->setGeometry(QRect(690, 200, 64, 23));
        pushButtonStart = new QPushButton(centralwidget);
        pushButtonStart->setObjectName(QString::fromUtf8("pushButtonStart"));
        pushButtonStart->setGeometry(QRect(460, 120, 84, 28));
        pushButtonPause = new QPushButton(centralwidget);
        pushButtonPause->setObjectName(QString::fromUtf8("pushButtonPause"));
        pushButtonPause->setGeometry(QRect(600, 240, 84, 28));
        pushButtonReset = new QPushButton(centralwidget);
        pushButtonReset->setObjectName(QString::fromUtf8("pushButtonReset"));
        pushButtonReset->setGeometry(QRect(700, 240, 84, 28));
        pushButtonClose = new QPushButton(centralwidget);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(710, 0, 84, 28));
        labelGameEnd = new QLabel(centralwidget);
        labelGameEnd->setObjectName(QString::fromUtf8("labelGameEnd"));
        labelGameEnd->setGeometry(QRect(120, 90, 251, 111));
        lineEditGameTag = new QLineEdit(centralwidget);
        lineEditGameTag->setObjectName(QString::fromUtf8("lineEditGameTag"));
        lineEditGameTag->setGeometry(QRect(460, 200, 113, 28));
        labelGameTag = new QLabel(centralwidget);
        labelGameTag->setObjectName(QString::fromUtf8("labelGameTag"));
        labelGameTag->setGeometry(QRect(460, 170, 63, 20));
        labelLeaderboard = new QLabel(centralwidget);
        labelLeaderboard->setObjectName(QString::fromUtf8("labelLeaderboard"));
        labelLeaderboard->setGeometry(QRect(460, 250, 91, 20));
        labelFirst = new QLabel(centralwidget);
        labelFirst->setObjectName(QString::fromUtf8("labelFirst"));
        labelFirst->setGeometry(QRect(460, 280, 63, 20));
        labelSecond = new QLabel(centralwidget);
        labelSecond->setObjectName(QString::fromUtf8("labelSecond"));
        labelSecond->setGeometry(QRect(460, 310, 63, 20));
        labelThird = new QLabel(centralwidget);
        labelThird->setObjectName(QString::fromUtf8("labelThird"));
        labelThird->setGeometry(QRect(460, 340, 63, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(pushButtonClose, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        playgroundSize->setText(QCoreApplication::translate("MainWindow", "Choose playground size", nullptr));
        labelHeight->setText(QCoreApplication::translate("MainWindow", "Height", nullptr));
        labelWidth->setText(QCoreApplication::translate("MainWindow", "Width", nullptr));
        labelSeed->setText(QCoreApplication::translate("MainWindow", "Enter seed value:", nullptr));
        labelTime->setText(QCoreApplication::translate("MainWindow", "Playtime:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Score:", nullptr));
        pushButtonStart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        pushButtonPause->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        pushButtonReset->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        labelGameEnd->setText(QString());
        labelGameTag->setText(QCoreApplication::translate("MainWindow", "Gametag", nullptr));
        labelLeaderboard->setText(QCoreApplication::translate("MainWindow", "Leaberboard:", nullptr));
        labelFirst->setText(QString());
        labelSecond->setText(QString());
        labelThird->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
