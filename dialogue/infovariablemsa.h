#ifndef INFOVARIABLEMSA_H
#define INFOVARIABLEMSA_H

#include <QDialog>
#include "../enrg/enrgvariablemsa.h"

namespace Ui {
class InfoVariableMSA;
}

class InfoVariableMSA : public QDialog
{
    Q_OBJECT

public:
    explicit InfoVariableMSA(QWidget *parent = nullptr);
    ~InfoVariableMSA();
    void IniBoite( ptrenrgvariableMSA pvaleur );


private slots:
    void on_fermerboite_clicked();

private:
    Ui::InfoVariableMSA *ui;
};

#endif // INFOVARIABLEMSA_H
