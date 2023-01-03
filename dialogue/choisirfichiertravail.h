#ifndef CHOISIRFICHIERTRAVAIL_H
#define CHOISIRFICHIERTRAVAIL_H

#include <QDialog>
#include "../enrg/enrgfichier.h"
#include "../gerersession.h"

namespace Ui {
class ChoisirFichierTravail;
}

class ChoisirFichierTravail : public QDialog
{
    Q_OBJECT

public:

    explicit ChoisirFichierTravail(QWidget *parent = 0);
    ~ChoisirFichierTravail();

    void IniBoite( GererSession *psession );
    EnrgFichier Valeur() ;
    QString NomCopie() const ;
    bool FichierCopier();
    void FichierStd();
    bool OKStd();

private slots:

    void on_Btn_parcourir_clicked();

    void on_Btn_parcourir_fichier_clicked();

    void on_Btn_copier_clicked();

    void on_Btn_FACZone_clicked();

    void on_checkBox_stateChanged(int arg1);

private:

    Ui::ChoisirFichierTravail *ui;

    EnrgFichier valfic;
    GererSession *ptsession;
};

#endif // CHOISIRFICHIERTRAVAIL_H
