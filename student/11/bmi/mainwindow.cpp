#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_countButton_clicked()
{
    QString w = ui->weightLineEdit->text();
    QString h = ui->heightLineEdit->text();

    double weigth = w.toDouble();
    double height = h.toDouble();

    if (h == "" or height == 0) {
        ui->infoTextBrowser->setText("Cannot count.");
        ui->resultLabel->setText("");
    } else {
    double bmi = weigth / ((height / 100)*(height /100));

    QString result = QString::number(bmi, 'f', 4);
    ui->resultLabel->setText(result);

    if (bmi < 18.5) {
        ui->infoTextBrowser->setText("You are underweight.");
    } else if (bmi > 25) {
        ui->infoTextBrowser->setText("You are overweight.");
    } else {
        ui->infoTextBrowser->setText("Your weight is normal.");
    }
    }
}

