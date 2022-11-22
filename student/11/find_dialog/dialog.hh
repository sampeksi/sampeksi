#ifndef DIALOG_HH
#define DIALOG_HH

#include <QMainWindow>
#include <QString>
#include <iostream>
#include <QFile>
#include <QCoreApplication>
#include <QtDebug>
#include <QTextStream>
#include <QFileInfo>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QMainWindow
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_findPushButton_clicked();



private:
    Ui::Dialog *ui;
};
#endif // DIALOG_HH
