#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::timer_function);

    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::green);
    ui->lcdNumberSec->setAutoFillBackground(true);
    ui->lcdNumberSec->setPalette(pal);

    pal.setColor(QPalette::Window, Qt::blue);
    ui->lcdNumberMin->setAutoFillBackground(true);
    ui->lcdNumberMin->setPalette(pal);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    if (!is_running) {
        is_running = true;
        timer_function();
    }
}


void MainWindow::on_stopButton_clicked()
{
    is_running = false;
}


void MainWindow::on_resetButton_clicked()
{
    is_running = false;
    value_ = 0;
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
}

void MainWindow::timer_function()
{
    if (is_running) {
        if (value_ == 60) {
            mins_ += 1;
            value_ = 0;
            ui->lcdNumberSec->display(value_);
            ui->lcdNumberMin->display(mins_);
        } else {
            ui->lcdNumberSec->display(value_);
        }
        value_ += 1;
        timer->start(1000);
    }
}

