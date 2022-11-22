#include "eka.hh"
#include "ui_eka.h"

EKa::EKa(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EKa)
{
    ui->setupUi(this);
}

EKa::~EKa()
{
    delete ui;
}

