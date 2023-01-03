#include "creerunprojet.h"
#include "ui_creerunprojet.h"
#include "../dialogue/messagemsa.h"

CreerUnProjet::CreerUnProjet(QWidget *parent) : QDialog(parent), ui(new Ui::CreerUnProjet)
{
    ui->setupUi(this);
}

CreerUnProjet::~CreerUnProjet()
{
    delete ui;
}

void CreerUnProjet::IniBoite( QStringList *pvaleur, EnrgSessionProjet *pvalenrg )
{
    penrgretour = pvalenrg;
    Enrtmp      = *pvalenrg;

    plstprojetexistant = pvaleur;
    QString nomprovisoire("nouveauprojet%1");
    QString nomtest("nouveauprojet");
    QString nomcomment("projet de démarrage d'applications");
    int increment=0;
    while(plstprojetexistant->contains(nomtest,Qt::CaseInsensitive))
    {
        nomtest = QString(nomprovisoire).arg(increment++);
    }

    ui->L_nomprojet->setText(nomtest);
    ui->L_dateEdit->setDate(QDate::currentDate());
    ui->L_commentaire->setText(nomcomment);

}

void CreerUnProjet::Collationner()
{
    penrgretour->projet.commentaire = ui->L_commentaire->text();
    penrgretour->projet.nom = ui->L_nomprojet->text();
    QDate tmpdate = ui->L_dateEdit->date();
    tmpdate.getDate(&penrgretour->dcreation.a,&penrgretour->dcreation.m,&penrgretour->dcreation.j);
}

void CreerUnProjet::on_buttonBox_accepted()
{
    if(plstprojetexistant->contains( ui->L_nomprojet->text(), Qt::CaseInsensitive ))
    {
        MessageMSA *msg = new MessageMSA(this);
        if(msg->QuestionMSA("Création d'un projet",tr("ce projet existe.\n","Écraser l'existant ?")))
        {
            if(msg->QuestionSuppression("Souhaitez-vous vraiment détruire le projet existant ?"))
                accept();
            else
                reject();
        }
    }
    else
        accept();
}
