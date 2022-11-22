#ifndef EKA_HH
#define EKA_HH

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class EKa; }
QT_END_NAMESPACE

class EKa : public QMainWindow
{
    Q_OBJECT

public:
    EKa(QWidget *parent = nullptr);
    ~EKa();

private:
    Ui::EKa *ui;
};
#endif // EKA_HH
