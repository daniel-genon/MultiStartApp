#ifndef CREERUNCONTEXTE_H
#define CREERUNCONTEXTE_H

#include <QDialog>
#include "../bloc/fblocprojetmapp.h"
#include "ui_boitecontexte.h"

namespace Ui {
class CreerUnContexte;
}

class CreerUnContexte : public QDialog
{
    Q_OBJECT
public:
    CreerUnContexte(QWidget *parent = 0);
    ~CreerUnContexte();

    virtual void IniBoite( FBlocProjetMApp *valeur );
            void Collationner();

public slots:
    virtual void on_buttonBox_accepted();
    virtual void on_buttonBox_rejected();
    virtual void on_Lst_projet_clicked(const QModelIndex &);
    virtual void on_Lst_contexte_clicked(const QModelIndex &);
    virtual void on_Lst_contexte_doubleClicked(const QModelIndex &);

protected:
    QString             projetenentree, contexteenentree;
    FBlocProjetMApp     *pfichier;
    Ui::BoiteContexte   *ui;

    virtual void IniLabel();
    virtual bool ListerContexte();
    void ListerProjet();

private:
    void AfficherProjet();

};

#endif // CREERUNCONTEXTE_H
