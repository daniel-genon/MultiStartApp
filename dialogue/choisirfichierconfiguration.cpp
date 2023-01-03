#include "choisirfichierconfiguration.h"
#include "ui_choisirfichierconfiguration.h"
#include <qfiledialog.h>

ChoisirFichierConfiguration::ChoisirFichierConfiguration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoisirFichierConfiguration)
{
    ui->setupUi(this);
}

ChoisirFichierConfiguration::~ChoisirFichierConfiguration(){    delete ui;}

void ChoisirFichierConfiguration::IniBoite( GererSession *psession )
{
    ptsession = psession;
    valfic.Chemin( psession->CheminContexte() );
    ui->label_chemin->setText(valfic.Chemin());
    valfic.Libelle("ficcfg");
    valfic.Extension("cfg");
    valfic.CreerUnNom();
    ui->label_fichier->setText(valfic.NomEtendu());
    ui->label_ficcopie->clear();
    ui->checkBox->setCheckState( Qt::Unchecked );
    ui->checkBox->hide();
}

void ChoisirFichierConfiguration::FichierStd()
{
    ui->checkBox->show();
    ui->checkBox->setCheckState( Qt::Unchecked );
}

EnrgFichier ChoisirFichierConfiguration::Valeur()
{
    QString phrtmp(ui->label_chemin->text());
    phrtmp.append("/");
    phrtmp.append(ui->label_fichier->text());
    valfic.EntrerConvertir( phrtmp );
    return valfic;
}

QString ChoisirFichierConfiguration::NomCopie() const { return ui->label_ficcopie->text();}
bool ChoisirFichierConfiguration::FichierCopier() { return !ui->label_ficcopie->text().isEmpty();}
bool ChoisirFichierConfiguration::OKStd() { return ui->checkBox->isChecked();}

void ChoisirFichierConfiguration::on_Btn_parcourir_clicked()
{
    QString nomtmp = QFileDialog::getExistingDirectory( this, "chemin du fichier", valfic.Chemin() );
    if(!nomtmp.isEmpty())
    {
        valfic.Chemin( nomtmp );
        ui->label_chemin->setText(nomtmp);
    }
}

void ChoisirFichierConfiguration::on_Btn_parcourir_fichier_clicked()
{
    QString nomtmp = QFileDialog::getOpenFileName( this, "chemin du fichier", valfic.Chemin(),"*.*");
    if(!nomtmp.isEmpty())
    {
        valfic.EntrerConvertir( nomtmp );
        ui->label_chemin->setText(valfic.Chemin());
        ui->label_fichier->setText(valfic.NomEtendu());
    }
}

void ChoisirFichierConfiguration::on_Btn_copier_clicked()
{
    QString nomtmp = QFileDialog::getOpenFileName( this, "fichier à copier", ptsession->CheminRacine(),"*.*");
    if(!nomtmp.isEmpty())
        ui->label_ficcopie->setText(nomtmp);
}


void ChoisirFichierConfiguration::on_Btn_FACZone_clicked()
{
    ui->label_ficcopie->clear();
}

void ChoisirFichierConfiguration::on_checkBox_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->Btn_copier->show();
        ui->label_ficcopie->show();
        ui->Btn_FACZone->show();
    }
    else
    {
        ui->Btn_copier->hide();
        ui->label_ficcopie->hide();
        ui->Btn_FACZone->hide();
    }
}
