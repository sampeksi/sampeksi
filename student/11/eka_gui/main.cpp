#include "eka.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EKa w;
    w.show();
    return a.exec();
}
