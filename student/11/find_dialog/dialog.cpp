#include "dialog.hh"
#include "ui_dialog.h"

using namespace std;

Dialog::Dialog(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_findPushButton_clicked()
{
    QString searched_file = ui->fileLineEdit->text();
    QString key = ui->keyLineEdit->text();

    QString file(searched_file);
    QFile file_name(file);

    if (!QFileInfo::exists(file)) {
        ui->textBrowser->setText("File not found");
    } else {
        file_name.open(QIODevice::ReadWrite);
        if (ui->matchCheckBox->isChecked()) {
            if (key == "") {
                ui->textBrowser->setText("File found");
            } else {
                QTextStream text(&file_name);
                while (!text.atEnd()) {
                    QString line = text.readLine();
                    if (line.contains(key, Qt::CaseSensitive)) {
                        ui->textBrowser->setText("Word found");
                    } else {
                        ui->textBrowser->setText("Word not found");
                    }
                }
            }
        } else {
            if (key == "") {
                ui->textBrowser->setText("File found");
            } else {
                QTextStream text(&file_name);
                while (!text.atEnd()) {
                    QString line = text.readLine();
                    if (line.contains(key, Qt::CaseInsensitive)) {
                        ui->textBrowser->setText("Word found");
                    } else {
                        ui->textBrowser->setText("Word not found");
                    }
                }
            }
        }
    }

}
