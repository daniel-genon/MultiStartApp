#ifndef APROPOS_H
#define APROPOS_H

#include <QDialog>

namespace Ui {
class APropos;
}

class APropos : public QDialog
{
    Q_OBJECT

public:
    explicit APropos(QWidget *parent = 0);
    ~APropos();

private:
    Ui::APropos *ui;
};

#endif // APROPOS_H
