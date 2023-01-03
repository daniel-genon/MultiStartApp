#ifndef CREERUNPROJET_H
#define CREERUNPROJET_H

#include <QDialog>
#include "../bloc/fblocprojetmapp.h"

namespace Ui {
class CreerUnProjet;
}

class CreerUnProjet : public QDialog
{
    Q_OBJECT

public:
    explicit CreerUnProjet(QWidget *parent = 0);
    ~CreerUnProjet();

    void IniBoite( QStringList *pvaleur, EnrgSessionProjet *pvalenrg );
    void Collationner();

private slots:

    void on_buttonBox_accepted();


private:

    Ui::CreerUnProjet *ui;

    QStringList *plstprojetexistant;

    EnrgSessionProjet Enrtmp;
    EnrgSessionProjet *penrgretour;

};

#endif // CREERUNPROJET_H
