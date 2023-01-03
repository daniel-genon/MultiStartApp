#include "creeruncontexte.h"
#include "../dialogue/messagemsa.h"

CreerUnContexte::CreerUnContexte(QWidget *parent) : QDialog(parent)
{
    ui = new Ui::BoiteContexte;
    ui->setupUi(this);
    setWindowTitle("Créer un contexte");
}

CreerUnContexte::~CreerUnContexte()
{
    delete ui;
}

void CreerUnContexte::IniLabel()
{
    ui->L_phrz1->setText("nouveaucontexte");
    ui->L_phrz2->setText("contexte de démarrage des applications");
    ui->L_dateEdit->setDate(QDate::currentDate());
}

void CreerUnContexte::IniBoite( FBlocProjetMApp *valeur )
{
    pfichier            = valeur;
    projetenentree      = pfichier->fichiercontexte.penrg->projet.nom;
    contexteenentree    = pfichier->fichiercontexte.penrg->nom;
    ui->L_dateProjet->setEnabled(false);
    ListerProjet();
    IniLabel();
}

void CreerUnContexte::on_buttonBox_accepted()
{
    QList<QListWidgetItem*> test = ui->Lst_contexte->findItems(ui->L_phrz1->text(),Qt::MatchExactly);
    if(test.isEmpty())
        accept();
    else
    {
        MessageMSA *msg = new MessageMSA(this);
        if(msg->QuestionMSA("Création d'un contexte",tr("Ce contexte existe.\n","Écraser l'existant ?")))
        {
            if(msg->QuestionSuppression("Souhaitez-vous vraiment détruire le contexte existant ?"))
                accept();
            else
                reject();
        }
    }
 }

void CreerUnContexte::Collationner()
{
    pfichier->fichiercontexte.penrg->nom = ui->L_phrz1->text();
    pfichier->fichiercontexte.penrg->commentcontxt = ui->L_phrz2->text();
    QDate tmpdate = ui->L_dateEdit->date();
    tmpdate.getDate(&pfichier->fichiercontexte.penrg->dcreation.a,
                    &pfichier->fichiercontexte.penrg->dcreation.m,
                    &pfichier->fichiercontexte.penrg->dcreation.j);
    pfichier->fichiercontexte.penrg->dmodifcontexte = pfichier->fichiercontexte.penrg->dcreation;
}

void CreerUnContexte::on_Lst_projet_clicked(const QModelIndex &)
{
    QListWidgetItem *ptoto = ui->Lst_projet->currentItem();
    if(pfichier->LireProjet(ptoto->text(), true))
        ListerContexte();
    else
        ui->Lst_projet->setCurrentRow(0);
    AfficherProjet();
}

void CreerUnContexte::on_Lst_contexte_clicked(const QModelIndex &){}

void CreerUnContexte::on_Lst_contexte_doubleClicked(const QModelIndex &){}

void CreerUnContexte::ListerProjet()
{
    QStringList lstTMP;
    pfichier->Lister( lstTMP );
    if(!lstTMP.isEmpty())
    {
        int position = lstTMP.indexOf(projetenentree);
        if(position!=-1)
            pfichier->LireProjet(projetenentree,true);
        else
        {
            position = 0;
            pfichier->LireProjet(lstTMP.first(),true);// lecture premier enrg
        }
        ui->Lst_projet->addItems(lstTMP);
        ui->Lst_projet->setCurrentRow(position);
        AfficherProjet();
        ListerContexte();
    }
}

bool CreerUnContexte::ListerContexte()
{
    ui->Lst_contexte->clear();
    QStringList lstTMP;
    if(pfichier->ListerContexte( lstTMP ))
        ui->Lst_contexte->addItems(lstTMP);
    return !lstTMP.isEmpty();
}

void CreerUnContexte::on_buttonBox_rejected()
{
    reject();
}

void CreerUnContexte::AfficherProjet()
{
    ui->L_comprojet->setText(QString((QChar *)&pfichier->enrgB.commentaire));
    ui->L_dateProjet->setDate(QDate(pfichier->enrgB.dcrea.a,
                                    pfichier->enrgB.dcrea.m,
                                    pfichier->enrgB.dcrea.j));
}
