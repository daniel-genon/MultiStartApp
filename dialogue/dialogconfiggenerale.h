#ifndef DIALOGCONFIGGENERALE_H
#define DIALOGCONFIGGENERALE_H

#include <QDialog>
#include "../bloc/fblocconfig.h"
#include "../dialogue/messagemsa.h"
#include "../enrg/enrgconnexion.h"
#include "../enrg/enrgvariablemsa.h"
#include <QAbstractButton>

namespace Ui {
class DialogConfigGenerale;
}

class DialogConfigGenerale : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConfigGenerale(QWidget *parent = nullptr);
    ~DialogConfigGenerale();

    void IniBoite( FBlocConfig *pvaleur, LstVarMSA *lvarmsa = nullptr );

    private slots:

        void on_btcoulfondgraph_clicked();
        void on_btcoulfondmenu_clicked();
        void on_btcoulfondelmgraph_clicked();
        void on_btcoulbandelmgraph_clicked();
        void on_btcoulpolelmgraph_clicked();
        void on_btcoulfondficli_clicked();
        void on_btcoulbandficli_clicked();
        void on_btcoulpolficli_clicked();
        void on_btcoulpolgen_clicked();

        void on_LST_Configuration_clicked(const QModelIndex &index);
        void on_LST_Logiciel_clicked(const QModelIndex &index);
        void on_LST_FicCFGLog_clicked(const QModelIndex &index);

        void on_buttonBox_clicked(QAbstractButton *);
        void on_BTN_nouvelle_clicked();
        void on_BTN_charger_clicked();
        void on_BTN_ajoutlog_clicked();

        void on_tabWidget_currentChanged(int index);
        void on_btcoulfondancre_clicked();
        void on_btcoulpolancre_clicked();



        void on_BTN_supprlog_clicked();

        void on_BTN_ajoutprio_clicked();

        void on_BTN_suppprio_clicked();

        void on_LST_Priorite_clicked(const QModelIndex &index);

        void on_btcoulconnexion_0_clicked();

        void on_btcoulconnexion_1_clicked();

        void on_btcoulconnexion_2_clicked();

        void on_s_proc_clicked();

        void on_s_icon_clicked();

        void on_s_ch_proc_clicked();

        void on_s_cfg_clicked();

        void on_s_trv_clicked();

        void on_Insere_Variable_clicked();

        void on_Info_Variable_clicked();

private:

    Ui::DialogConfigGenerale *ui;
    FBlocConfig     *pfichier;
    MessageMSA      *msgmsa;
    LstVarMSA      *plvarmsa;


    EnrgConfig      econfig;
    EnrgConnexion   econnex;

    LstEnrgLogiciel lstlogiciel;
    LstEnrgGrLog    lstgraph;
    LstEnrgGrFic    lstficlie;

    int indgraph;
    int indlogic;
    int indficli;
    int indconfg;
    int indpagew;

    QPushButton *ptrboutontraite;
    QColor       couleurboite;

    EnrgPolice  poltmp;

    void InitialiserValeur();
    bool SauvegardeOK();
    bool ValeursModifiees();
    void CouleurBouton(int cas);
    bool BoiteACouleur();
    void IniCouleur( int cas );
    void ColoriserBouton();
    void ColoriserBouton( int i );
    void AfficherValeur();
    void CollationnerValeur();
    void TransfererValeur();
    void AfficherConfigConnexion();
    void AfficherLogiciel();
    void AfficherGraphFicLie();
    void AfficherGraphique();
    bool Initialiser_Variable_MSA();
    void GererZoneVariable_MSA();

    void CollationnerValeurs();

    void CollationnerConfig();
    void CollationnerConnexion();
    void CollationnerPriorite();
    void CollationnerLogiciel();
    void CollationnerGraphFicLie();

    bool ConfigGeneralModifiee();
    bool ConnexionModifiee();
    bool PrioriteModifiee();
    bool FiclieModifie();
    bool LogicielModifie();

    QString CouleurBouton( const QPushButton *bouton ) const;

};

#endif // DIALOGCONFIGGENERALE_H
