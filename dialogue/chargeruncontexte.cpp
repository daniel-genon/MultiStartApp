#include "chargeruncontexte.h"

ChargerUnContexte::ChargerUnContexte(QWidget *parent) : CreerUnContexte(parent)
{
    setWindowTitle("Charger un contexte");
}

void ChargerUnContexte::IniLabel()
{
    ui->Lst_contexte->setEnabled(true);
    ui->Lst_contexte->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
    ui->Lst_contexte->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->label_z1->hide();
    ui->L_phrz1->hide();
    ui->label_2->setEnabled(false);
    ui->L_dateEdit->setEnabled(false);
    AfficherContexte();
}

void ChargerUnContexte::on_buttonBox_accepted()
{
    if((projetenentree.compare(pfichier->fichiercontexte.penrg->projet.nom)==0)
            &&
       (contexteenentree.compare(pfichier->fichiercontexte.penrg->nom)==0)
      )
        reject();
    else
        accept();
}

void ChargerUnContexte::on_Lst_contexte_clicked(const QModelIndex &)
{
    AfficherContexte();
}

void ChargerUnContexte::on_Lst_contexte_doubleClicked(const QModelIndex &)
{
    AfficherContexte();
    accept();
}

bool ChargerUnContexte::ListerContexte()
{
    if(CreerUnContexte::ListerContexte())
    {
        ui->Lst_contexte->setCurrentRow(0);
        if(projetenentree.compare(pfichier->fichiercontexte.penrg->projet.nom)==0)
        {
            QList<QListWidgetItem*> valeur = ui->Lst_contexte->findItems(contexteenentree, Qt::MatchExactly);
            if(!valeur.isEmpty())
//                valeur.first()->setFlags(Qt::NoItemFlags);
                valeur.first()->setHidden(true);
        }
        AfficherContexte();
        return true;
    }
    return false;
}

void ChargerUnContexte::AfficherContexte()
{
    QListWidgetItem *ptoto = ui->Lst_contexte->currentItem();
    pfichier->LireContexte(ptoto->text());
    ui->L_phrz2->setText(pfichier->fichiercontexte.penrg->commentcontxt);
    ui->L_dateEdit->setDate( QDate(pfichier->fichiercontexte.penrg->dmodifcontexte.a,
                                   pfichier->fichiercontexte.penrg->dmodifcontexte.m,
                                   pfichier->fichiercontexte.penrg->dmodifcontexte.j));
}
