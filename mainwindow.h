#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "vue.h"
#include "dialogue/apropos.h"
#include "gerersession.h"
#include "configurationobjet.h"
#include "fichierconfiguration.h"
#include "fichiertravail.h"
#include "ancrage.h"
#include "demarreobjet.h"
#include "dialogue/messagemsa.h"

QT_FORWARD_DECLARE_CLASS(QGraphicsScene)

class MainWindow : public QWidget
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void LancerContexteEnCours();
    void StopperTout();
    void AProposDe();
    void ChoisirContexte();
    void NouveauProjet();
    void NouveauContexte();
    void Sauvegarder();
    void SupprimerObjet();
    void NettoyerTout();
    void Configuration();
    void Quit();

    void LierDesObjets();
    void FichierDeConfiguration();
    void FichierDeTravail();
    void CentrerSchema();

    void AjouterLogiciel( int cas );

protected:

private:

    bool                passortir;
//    bool encoursdesuppression;
    QString             phrtmp;
    QPointF             poselemdefaut;
    QGraphicsItem       *dernieritemcree;
    Ancrage             *psymboleancre;
    CadreZoneGraphique  *pview;
    GererSession        session;
    ConfigurationObjet  CfgMTStartApp;// ancien cfgdemarreMAO
    DemarreObjet        demarreur;
    MessageMSA          *messagemsa;


    void RechargerSession();
    void EnregistrerContexte();
    bool ChargerContexte();
    void ChangerContexte( const QString valeur );
    bool AjouterElement( Logiciel *plogiciel );
    void NettoyerLaScene( bool okquestion=true );
    void AjouterLogiciel( EnrgObjetCtx *penrgCtx );
    void AjouterFichierTravail( Logiciel *plogi, EnrgObjetCtx *pvaleur );
    void AjouterFichierTravail( Logiciel *plogi, const EnrgFichier &valeur );
    void AjouterFichierCfg( Logiciel *plogi, EnrgObjetCtx *pvaleur );
    void AjouterFichierCfg( Logiciel *plogi, const EnrgFichier &valeur );
    void AjouterConnexion( QGraphicsItem *psource, QGraphicsItem *pcible );
    void AjouterFichier( Logiciel *plogi, Fichier *pfic );
    void SupprimerUnObjet( QGraphicsItem *pobjet );
    void SupprimerConnexionsDe( GraphObjetActif *pobjactif );
    void SupprimerFichiersDe( Logiciel *plogi );
    void SupprimerFichierCFG( FichierConfiguration *ptrfic , bool retirerscene );
    void SupprimerFichierTRV( FichierTravail *ptrfic , bool retirerscene );
    void TuerProcess();

    Element *LogicielSelectionne();


// routine et données du menu/affichage

    QGraphicsScene *pscene;

    QToolButton *quitter, *configuration, *nouvproj, *nouvcont, *sauvegarder, *choisir, *nettoyer, *supprimer;
    QToolButton *btapropos,* lancer, *eradiquer, *lierobjet, *ficcfg, *fictrv;
    QToolButton *centrervue;

    QList<QToolButton *> lstbtnlogiciel;
    QList<QVBoxLayout *> lstcollogiciel;

    QSignalMapper *triagelogiciel;

    QSplitter *h1Splitter;
    QSplitter *vSplitter;

    QVBoxLayout *layoutcentre;
    QGridLayout *layoutdroite;
    QGridLayout *layoutgauche;
    QGridLayout *topLayout;



    void CreerLeMenu();
    void TitreDeLaFenetre();
    void ConfigurationFenetre();
    void CreerUnBouton(QToolButton *qbt, const QString &icone, const QString &msg, int tailleicone=20, bool okappli=false );
    void BarreBoutonLogiciel();


    QBoxLayout *BarreBoutonFin();
    QBoxLayout *BarreBoutonGestion();
    QBoxLayout *BarreBoutonHaut();
    QBoxLayout *BarreBoutonGHaut();

};

#endif // MAINWINDOW_H
