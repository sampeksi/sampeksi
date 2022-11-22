#include "mainwindow.hh"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBoxN->setRange(0, MAX_N_POINTS);
    ui->spinBoxG->setRange(0, MAX_G_POINTS);
    ui->spinBoxP->setRange(0, MAX_P_POINTS);
    ui->spinBoxE->setRange(0, 5);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_countPushButton_clicked()
{
    unsigned int N = ui->spinBoxN->value();
    unsigned int G = ui->spinBoxG->value();
    unsigned int P = ui->spinBoxP->value();
    unsigned int E = ui->spinBoxE->value();

    unsigned int grade = count_final_grade(N, G, P, E);
    QString moi;

    ui->textBrowser->setText("Total grade: ");
    ui->textBrowser->append(QString::number(grade));
}

