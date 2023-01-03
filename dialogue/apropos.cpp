#include <qversionnumber.h>
#include "apropos.h"
#include "ui_apropos.h"

APropos::APropos(QWidget *parent) : QDialog(parent)
{
    extern QVersionNumber   *pversionMSA;
    extern QString          *pCHRdateversionMSA;
    QString  phrversion     = "version QT : " + QString(QT_VERSION_STR);
    QString  phrversionmsa  = "version : " + pversionMSA->toString() + " du " + *pCHRdateversionMSA;
    ui = new Ui::APropos;
    ui->setupUi(this);
    ui->phrversionQT->setText(phrversion);
    ui->phrversionMSA->setText(phrversionmsa);
    ui->zoneimage->setPixmap(QPixmap(":/icone/apropos.png"));
}

APropos::~APropos()
{
    delete ui;
}
