#ifndef CHARGERUNCONTEXTE_H
#define CHARGERUNCONTEXTE_H

#include "creeruncontexte.h"

namespace Ui {
class ChargerrUnContexte;
}

class ChargerUnContexte : public CreerUnContexte
{
    Q_OBJECT

public:
    ChargerUnContexte(QWidget *parent = 0);

public slots:
    virtual void on_buttonBox_accepted();
    virtual void on_Lst_contexte_clicked(const QModelIndex &);
    virtual void on_Lst_contexte_doubleClicked(const QModelIndex &);

protected:
    virtual bool ListerContexte();
    virtual void IniLabel();

private:
    void AfficherContexte();
};

#endif // CHARGERUNCONTEXTE_H
