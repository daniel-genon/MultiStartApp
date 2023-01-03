#include "infovariablemsa.h"
#include "ui_infovariablemsa.h"

InfoVariableMSA::InfoVariableMSA(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoVariableMSA)
{
    ui->setupUi(this);
}
void InfoVariableMSA::IniBoite( ptrenrgvariableMSA pvaleur )
{
    if(pvaleur)
    {
        ui->Vchemin->setText(pvaleur->Valeur());
        ui->Vcode->setText(pvaleur->Code_Abrege());
        ui->Vdefinition->setText(pvaleur->Definition());
    }
}
InfoVariableMSA::~InfoVariableMSA()
{
    delete ui;
}
void InfoVariableMSA::on_fermerboite_clicked(){accept();}

