#include "mainwindow.h"
#include "dialogue/choisirfichiertravail.h"
#include "dialogue/choisirfichierconfiguration.h"

#define VERSIONQT QT_MAJOR_VERSION

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    psymboleancre   = nullptr;
    extern QString *pCHRacine;
    pCHRacine = session.ptrCheminRacine();
    passortir = false;
        poselemdefaut.setX(0);
        poselemdefaut.setY(0);

    messagemsa = new MessageMSA(this);

    if(!CfgMTStartApp.InitialiserConfiguration( session.ptrCheminRacine(), session.NomConfiguration() ))
    {
        session.ChangerConfiguration(CfgMTStartApp.ConfigurationEnCours());
    }
// création de la liste des variables utilisées par MSA pour la ligne option des lanceurs.
    CfgMTStartApp.lvarmsa.Ajouter(session.CheminRacine(),
                                  QString("Racine de l'environnement du logiciel"),
                                  QString("chm_racine")
                                 );
    CfgMTStartApp.lvarmsa.Ajouter(session.CheminProjet(),
                                  QString("chemin des projets"),
                                  QString("chm_projet")
                                 );
    CfgMTStartApp.lvarmsa.Ajouter(session.CheminContexte(),
                                  QString("chemin du contexte"),
                                  QString("chm_contexte")
                                 );
    CfgMTStartApp.lvarmsa.Ajouter(session.CheminStandard(),
                                  QString("chemin des fichiers standards"),
                                  QString("chm_standard")
                                 );
//*******
    CreerLeMenu();
    resize( 830, 600 );
    RechargerSession();
    demarreur.InitSession(&session,pscene);
    TitreDeLaFenetre();
}

MainWindow::~MainWindow()
{
/*
    if(psymboleancre!=NULL)
        delete psymboleancre;
    NettoyerConnexion();
*/
    if(!lstbtnlogiciel.isEmpty())
    {
        qDeleteAll(lstbtnlogiciel.begin(), lstbtnlogiciel.end());
        lstbtnlogiciel.clear();
    }
    if(!lstcollogiciel.isEmpty())
    {
        qDeleteAll(lstcollogiciel.begin(), lstcollogiciel.end());
        lstcollogiciel.clear();
    }
    delete triagelogiciel;
    delete layoutgauche;
    delete layoutcentre;
    delete layoutdroite;
    delete topLayout;
    delete pscene;
    if( messagemsa!=nullptr ) delete messagemsa;
}

void MainWindow::RechargerSession()
{
    if(!session.oksession())
    {
        if(session.ChargerPremierProjetEtContexte()!=0)
        {
            session.noerreur = 2;
            messagemsa->AlerteErreur(session.LibelleErreur());
            exit(0);
        }
    }
    ChargerContexte();
}

/*************************************
 zone des SLOTS
**************************************/

// barre à droite
void MainWindow::LancerContexteEnCours()
{
    bool okdemarrer=true;
    if(demarreur.DesProcessusSontDemarres())
    {
        switch(messagemsa->QuestionTroisReponse("Démarrage des logiciels",
                                               "Des logiciels ont déjà été démarrés.",
                                               "démarrer sans les stopper.",
                                               "abandonner le démarrage.",
                                               "les stopper avant démarrage."))
        { // 0:libbtn1, 1:libbtn2, 2:libbtn3
            case 1 : okdemarrer=false; break;
            case 2 : TuerProcess(); break;
        }
    }
    if(okdemarrer)
    {
        quitter->setIcon(QIcon(QPixmap(":/icone/quitter2.png")));
        passortir    = true;
        demarreur.DemarrerLaSession();
        passortir    = false;
        quitter->setIcon(QIcon(QPixmap(":/icone/quitter1.png")));
    }
}

void MainWindow::StopperTout()
{
    TuerProcess();
}

void MainWindow::AProposDe()
{
    APropos *dlg = new APropos;
    dlg->setModal(true);
    dlg->exec();
    delete dlg;
}

void MainWindow::ChoisirContexte()
{
    session.SauverEnrgProjet();
    quitter->setIcon(QIcon(QPixmap(":/icone/quitter2.png")));
    session.OuvrirUnContexte();
    ChangerContexte( "Charger un autre contexte" );
}

void MainWindow::NouveauProjet()
{
    session.SauverEnrgProjet();
    quitter->setIcon(QIcon(QPixmap(":/icone/quitter2.png")));
    session.CreerNouveauProjet();
    ChangerContexte( "création d'un nouveau projet" );
}

void MainWindow::NouveauContexte()
{
    session.SauverEnrgProjet();
    quitter->setIcon(QIcon(QPixmap(":/icone/quitter2.png")));
    session.CreerNouveauContexte();
    ChangerContexte( "création d'un nouveau contexte" );
}

void MainWindow::Sauvegarder()
{
    quitter->setIcon(QIcon(QPixmap(":/icone/quitter2.png")));
    sauvegarder->setIcon(QIcon(QPixmap(":/icone/sauvegarder2.png")));
    EnregistrerContexte();
    session.Enregistrer();
    messagemsa->SauvegardeDonnees();
    quitter->setIcon(QIcon(QPixmap(":/icone/quitter1.png")));
    sauvegarder->setIcon(QIcon(QPixmap(":/icone/sauvegarder1.png")));
}

void MainWindow::SupprimerObjet()
{
    passortir    = true;
    quitter->setIcon(QIcon(QPixmap(":/icone/quitter2.png")));
    supprimer->setIcon(QIcon(QPixmap(":/icone/supprimer2.png")));
    QGraphicsItem *pobjet;
    QList<QGraphicsItem *> tabitem = pscene->items();
    for(int i=0;i<tabitem.length();i++)
    {
        pobjet = tabitem.at(i);
        if(pobjet->isSelected())
        {
            Element *pelem = (Element *)pobjet;
            QString msgerreur("Etes-vous certain de supprimer <br> l'objet : ");

                msgerreur += pelem->NomElement();
                msgerreur += " ?";
            if( messagemsa->QuestionSuppression(msgerreur))
            {
                SupprimerUnObjet( pobjet );
            }
        }
    }
    quitter->setIcon(QIcon(QPixmap(":/icone/quitter1.png")));
    supprimer->setIcon(QIcon(QPixmap(":/icone/supprimer1.png")));
    passortir    = false;
}

void MainWindow::NettoyerTout()
{
    QList<QGraphicsItem *> tabitem = pscene->items();
    if(!tabitem.isEmpty())
    {
        if(messagemsa->QuestionSuppression("Souhaitez-vous vraiment tout supprimer ?"))
        {//supprimer l'objet
            passortir    = true;
            quitter->setIcon(QIcon(QPixmap(":/icone/quitter2.png")));
            supprimer->setIcon(QIcon(QPixmap(":/icone/supprimer2.png")));
            for(int i=0;i<tabitem.length();i++)
            {
                if(((Element *)tabitem.at(i))->GenreElement()==100)
                    SupprimerUnObjet( tabitem.at(i) );
            }
            quitter->setIcon(QIcon(QPixmap(":/icone/quitter1.png")));
            supprimer->setIcon(QIcon(QPixmap(":/icone/supprimer1.png")));
            passortir    = false;
        }
    }
}

void MainWindow::Configuration()
{
    if(CfgMTStartApp.GestionConfiguration())
    {
        // modifier l'affichage
    }
}

void MainWindow::Quit()
{
    if(!passortir)
    {
        quitter->setIcon(QIcon(QPixmap(":/icone/quitter2.png")));
        if(messagemsa->QuitterLogiciel())
        {
            EnregistrerContexte();
            session.Enregistrer();
            close();
        }
        quitter->setIcon(QIcon(QPixmap(":/icone/quitter1.png")));
    }
}

// barre dessus
void MainWindow::LierDesObjets()
{
    QGraphicsItem *pobjet;
    bool okselection=false;
    QList<QGraphicsItem *> tabitem = pscene->items();
    for(int i=0;i<tabitem.length();i++)
    {
        pobjet = tabitem.at(i);
        if(pobjet->isSelected())
        {
           okselection=true;
           break;
        }
    }
    if(okselection)
    {
            Element *pelem = (Element *)pobjet;
            switch(pelem->GenreElement())
            {
            case 200 :
                    messagemsa->AlerteMessage("L'objet est un fichier travail !");
                break;
            case 300 :
                    messagemsa->AlerteMessage("L'objet est un fichier configuration !");
                break;
            case 1000 :
                    messagemsa->AlerteMessage("L'objet est une ancre !");
                break;
            case 99999 :
                    messagemsa->AlerteMessage("Objet non ancrable !");
                break;

             default :{
                    Logiciel *plogique = (Logiciel *)pelem;
                        if(psymboleancre!=NULL)
                        {
                            psymboleancre->Nettoyerconnexion();
                            pscene->removeItem((QGraphicsItem *)psymboleancre);
                            delete psymboleancre;
                        }
                        psymboleancre = new Ancrage( pelem, &CfgMTStartApp );
                        pscene->addItem((QGraphicsItem *) psymboleancre);
                        plogique->EntrerUneAncre(psymboleancre,pelem,CfgMTStartApp.PointeurCo());
                        pscene->addItem( plogique->ValeurConnexion() );
                }
            }
    }
    else
        messagemsa->AlerteMessage("L'objet au départ de la liaison n'est pas sélectionné!");
}

void MainWindow::FichierDeConfiguration()
{
    Element *pelem = LogicielSelectionne();
    if(pelem==NULL)
        messagemsa->AlerteMessage("l'objet sélectionné n'est pas un logiciel !");
    else
    {
        Logiciel *plogiciel = (Logiciel *)pelem;
        if(plogiciel->PtrFicCfg()==NULL)
        {
            ChoisirFichierConfiguration dlg;
            dlg.setModal(true);
            dlg.IniBoite( &session );
            if(plogiciel->AUnStdCFG())
                dlg.FichierStd();
            if(dlg.exec()==QDialog::Accepted)
            {
                bool okcreer=true;
                bool oknouveau=true;
                if(QFile::exists( dlg.Valeur().NomComplet(true) ))
                {
                    if(dlg.FichierCopier())
                        phrtmp = "Remplacer par la copie";
                    else
                    {
                        if(dlg.OKStd())
                            phrtmp = "Remplacer par un fichier standard";
                        else
                            phrtmp = "Créer un fichier vide";
                    }
                    switch(messagemsa->QuestionGestionFichier(phrtmp))
                    {// /* 0:phrtmp, 1:utiliser existan, 2: ne rien faire */
                        case 0 : oknouveau=true; break;
                        case 1 : oknouveau=false; break;
                        default :  oknouveau=false; okcreer=false;
                    }
                    if(oknouveau)
                        QFile::remove(dlg.Valeur().NomComplet(true));
                }
                if(oknouveau)
                {
                    if(dlg.OKStd())
                    {
                        QString phtmp (session.CheminStandard());
                        phtmp.append( plogiciel->NomStdCFG() );
                        if(QFile::exists( phtmp ))
                            okcreer = QFile::copy( phtmp , dlg.Valeur().NomComplet(true) );
                        else
                        {
                            messagemsa->AlerteMessage("Il n'existe pas de fichier de configuration standard pour ce logiciel.</br>Un fichier vide est créer.");
                            ficbinbase fichiervide(dlg.Valeur().NomComplet(true));
                        }
                    }
                    else
                    {
                        if(dlg.FichierCopier())
                        {
                            if(QFile::exists( dlg.NomCopie()))
                                okcreer = QFile::copy( dlg.NomCopie(), dlg.Valeur().NomComplet(true) );
                            else
                            {
                                messagemsa->AlerteMessage("le fichier à copier n'existe pas.</br>Un fichier vide est créer.");
                                ficbinbase fichiervide(dlg.Valeur().NomComplet(true));
                            }
                        }
                        else
                            ficbinbase fichiervide(dlg.Valeur().NomComplet(true));
                    }
                }
                if(okcreer)
                    AjouterFichierCfg(plogiciel, dlg.Valeur());
                else
                    messagemsa->FichierNestPasCreer();
            }
        }
        else
           messagemsa->AlerteMessage("l'objet sélectionné possède un fichier de configuration");
    }
}

void MainWindow::FichierDeTravail()
{
    Element *pelem = LogicielSelectionne();
    if(pelem==NULL)
        messagemsa->AlerteMessage("l'objet sélectionné n'est pas un logiciel !");
    else
    {
        Logiciel *plogiciel = (Logiciel *)pelem;
        if(plogiciel->PtrFicTrv()==NULL)
        {
            ChoisirFichierTravail dlg;
            dlg.setModal(true);
            dlg.IniBoite( &session );
            if(plogiciel->AUnStdTRV())
                dlg.FichierStd();
            if(dlg.exec()==QDialog::Accepted)
            {
                bool okcreer=true;
                bool oknouveau=true;
                if(QFile::exists( dlg.Valeur().NomComplet(true) ))
                {
                    if(dlg.FichierCopier())
                        phrtmp = "Remplacer par la copie";
                    else
                    {
                        if(dlg.OKStd())
                            phrtmp = "Remplacer par un fichier standard";
                        else
                            phrtmp = "Créer un fichier vide";
                    }
                    switch(messagemsa->QuestionGestionFichier(phrtmp))
                    {// /* 0:phrtmp, 1:utiliser existan, 2: ne rien faire */
                        case 0 : oknouveau=true; break;
                        case 1 : oknouveau=false; break;
                        default :  oknouveau=false; okcreer=false;
                    }
                    if(oknouveau)
                        QFile::remove(dlg.Valeur().NomComplet(true));
                }
                if(oknouveau)
                {
                    if(dlg.OKStd())
                    {
                        QString phtmp (session.CheminStandard());
                        phtmp.append( plogiciel->NomStdTRV() );
                        if(QFile::exists( phtmp ))
                            okcreer = QFile::copy( phtmp , dlg.Valeur().NomComplet(true) );
                        else
                        {
                            messagemsa->AlerteMessage("Il n'existe pas de fichier de travail standard pour ce logiciel.</br>Un fichier vide est créer.");
                            ficbinbase fichiervide(dlg.Valeur().NomComplet(true));
                        }
                    }
                    else
                    {
                        if(dlg.FichierCopier())
                        {
                            if(QFile::exists( dlg.NomCopie()))
                                okcreer = QFile::copy( dlg.NomCopie(), dlg.Valeur().NomComplet(true) );
                            else
                            {
                                messagemsa->AlerteMessage("le fichier à copier n'existe pas.</br>Un fichier vide est créer.");
                                ficbinbase fichiervide(dlg.Valeur().NomComplet(true));
                            }
                        }
                        else
                            ficbinbase fichiervide(dlg.Valeur().NomComplet(true));
                    }
                }
                if(okcreer)
                    AjouterFichierTravail( plogiciel, dlg.Valeur() );
                else
                    messagemsa->FichierNestPasCreer();
            }
        }
        else
            messagemsa->AlerteMessage("l'objet sélectionné possède un fichier de travail");
    }
}

void MainWindow::CentrerSchema()
{
    QGraphicsScene *toto = pview->PtrZonePartieDeScene()->scene();
    QRectF tutu = toto->itemsBoundingRect();
    pscene->setSceneRect(tutu);
    pview->PtrZonePartieDeScene()->centerOn(tutu.center());
}

// menu icônes à gauche
void MainWindow::AjouterLogiciel( int cas)
{
    quint8 mnu = cas/100;
    quint8 rng = cas - mnu*100;
    ptrenrglogiciel valtmp = CfgMTStartApp.PointerLogiciel( mnu, rng );
    if(valtmp!=NULL)
    {
      Logiciel *pobjet = new Logiciel( &CfgMTStartApp, pscene );
        if(!pobjet->okvalide)
            delete pobjet;
        else
            if( !AjouterElement( pobjet ))
                delete pobjet;
    }
    else
        messagemsa->AlerteMessage("Il n'existe pas de logiciel pointé par ce menu" );
}

/*****************************************
zone des chargements de l'application
******************************************/

// dessiner les icônes représentant les logiciels dans le zone menu à gauche
void MainWindow::AjouterLogiciel(EnrgObjetCtx *penrgCtx )
{
    penrgCtx->PositionObjet( poselemdefaut );
    if(CfgMTStartApp.PointerLogiciel(penrgCtx->Nom()))
    {
        Logiciel *pobjet = new Logiciel( &CfgMTStartApp, pscene, penrgCtx->Priorite() );
          if(!pobjet->okvalide)
              delete pobjet;
          else
              if(AjouterElement( pobjet ))
              {
                  AjouterFichierCfg( pobjet, penrgCtx );
                  AjouterFichierTravail( pobjet, penrgCtx );
              }
              else
                  delete pobjet;
    }
}

/*****************************************
 Zone du dessin des objets représentants les éléments dans la zone graphique
******************************************/

// dessiner les objets logiciels
bool MainWindow::AjouterElement( Logiciel *plogiciel )
{
    QString msgerreur;
    if(plogiciel->VerifierExistenceSurScene())
    {
            msgerreur = "Ce ";
            msgerreur += plogiciel->libelle();
            msgerreur += " est déjà sur scène !";
        messagemsa->AlerteMessage(msgerreur);
        return false;
    }
    plogiciel->setPos(poselemdefaut);
    dernieritemcree = (QGraphicsItem *)plogiciel;
    pscene->addItem(dernieritemcree);
    return true;
}

// dessiner les objets fichier travail
void MainWindow::AjouterFichierTravail( Logiciel *plogi, EnrgObjetCtx *pvaleur )
{
    if(!pvaleur->NomTravail().isEmpty())
    {
        EnrgFichier valeur(pvaleur->NomTravail());
        pvaleur->PositionTravail(poselemdefaut);
        AjouterFichierTravail( plogi, valeur );
    }
}

// dessiner les objets fichier configuration
void MainWindow::AjouterFichierCfg( Logiciel *plogi, EnrgObjetCtx *pvaleur )
{
    if(!pvaleur->NomConfig().isEmpty())
    {
        EnrgFichier valeur(pvaleur->NomConfig());
        pvaleur->PositionConfig(poselemdefaut);
        AjouterFichierCfg( plogi, valeur );
    }
}

/*****************************************
 Zone des sous-programmes de délestage
*****************************************/

void MainWindow::AjouterFichierTravail( Logiciel *plogi, const EnrgFichier &valeur )
{
    CfgMTStartApp.PointeurCo()->encours=2;
    FichierTravail *pobjet = new FichierTravail( &CfgMTStartApp, valeur );
    AjouterFichier( plogi, (Fichier *)pobjet );
}

void MainWindow::AjouterFichierCfg( Logiciel *plogi, const EnrgFichier &valeur )
{
    CfgMTStartApp.PointeurCo()->encours=1;
    FichierConfiguration *pobjet = new FichierConfiguration( &CfgMTStartApp, valeur );
    AjouterFichier( plogi, (Fichier *)pobjet );
}

bool MainWindow::ChargerContexte()
{
    FBlocObjetContexte  ficobjetctx;

    NettoyerLaScene(false);
        ficobjetctx.EntrerContexte( session.NomDuContexte() );
        ficobjetctx.Initialiser(session.CheminProjet());

        if(!ficobjetctx.LireObjetContexte()) return false;

    QList<QGraphicsItem *> tabitem;
    int indexencours=0;
        while(ficobjetctx.LireElement(indexencours))
        {
            AjouterLogiciel(ficobjetctx.PtrEnrg());
            if(dernieritemcree!=NULL)
            {
                tabitem.append(dernieritemcree);
                dernieritemcree=NULL;
            }
            indexencours++;
        }
    indexencours=0;
        while(ficobjetctx.lireLiaison(indexencours))
        {

            if((ficobjetctx.PtrEnrg()->X()>-1)&&(ficobjetctx.PtrEnrg()->Y()>-1))
            {
                AjouterConnexion( tabitem.at(ficobjetctx.PtrEnrg()->X()), tabitem.at(ficobjetctx.PtrEnrg()->Y()) );
            }
            indexencours++;
        }
    poselemdefaut =  pscene->sceneRect().center();
    return true;
}

void MainWindow::ChangerContexte( const QString valeur )
{
    if(!session.oksession())
    {
        messagemsa->AlerteMessage( valeur, session.LibelleErreur() );
        session.RestaurerEnrgProjet();
    }
    else
    {
        if(session.okboite())
            session.RestaurerEnrgProjet();
        else
        {
            switch(messagemsa->QuestionTroisReponse( valeur, "Un contexte est en cours ?",
                                                     "Le sauvegarder",
                                                     "NE PAS le sauvegarder",
                                                     "Rester dans le contexte en cours"))
            {// 0:libbtn1, 1:libbtn2, 2:libbtn3
            case 0 ://0 sauver ancien et charger nouveau
                    session.ReserverEnrgProjet();
                    session.RestaurerEnrgProjet();
                    EnregistrerContexte();
                    session.RetablirEnrgProjet();
                [[fallthrough]];
            case 1 ://1 quitter ancien sans sauver et charger nouveau
                    TitreDeLaFenetre();
                    ChargerContexte();
                break;
            case 2 ://2 garder ancien
                    session.RestaurerEnrgProjet();
                break;
            }
        }
    }
    quitter->setIcon(QIcon(QPixmap(":/icone/quitter1.png")));
}

void MainWindow::EnregistrerContexte()
{
    FBlocObjetContexte  ficobjetctx;

    ficobjetctx.EntrerContexte( session.NomDuContexte() );
    ficobjetctx.Initialiser(session.CheminProjet());
    QList<Logiciel *> tabitemobjet;
    QList<Connexion *> tabitemliaison;

    QList<QGraphicsItem *> tabitem = pscene->items();
// traduire les événements
    Element         *pelem=0;
    Connexion       *objtmpcnx=0;
    Logiciel        *objtmplog=0;
    GraphObjetActif *objtmp=0;
    int         vlx, vly;

    for(int i=0;i<tabitem.length();i++)
    {
       pelem = (Element *)tabitem.at(i);
       switch(pelem->GenreElement())
       {
       case 100:{//logiciel
               objtmplog = (Logiciel *)pelem;
               objtmplog->CollationnerDescripteur( ficobjetctx.PtrEnrg() );
               tabitemobjet.append(objtmplog);
               ficobjetctx.AjouterObjet();

                }break;
       case 5000://connexion
           tabitemliaison.append((Connexion *)pelem);
       }
    }

//traduire les liaisons
    for(int i=0;i<tabitemliaison.length();i++)
    {
        objtmpcnx = tabitemliaison.at(i);
        ficobjetctx.PtrEnrg()->Raz();
        vlx = vly = -1;
        objtmp   = (GraphObjetActif*)objtmpcnx->ValeurSource();
        if(objtmp!=NULL)
            if(objtmp->GenreElement()==100)
                vlx = tabitemobjet.indexOf((Logiciel *)objtmp);
        objtmp   = (GraphObjetActif*)objtmpcnx->ValeurCible();
        if(objtmp!=NULL)
            if(objtmp->GenreElement()==100)
                vly = tabitemobjet.indexOf((Logiciel *)objtmp);

        ficobjetctx.PtrEnrg()->ValeurObjetConnexion( vlx, vly );

        ficobjetctx.AjouterLiaison();
    }
// stocker geometrie fenetre
//    QRect stock(geometry());
//    session.pFichierContexte()->EcrireDimFenetre(stock);
// écrire les événements
    ficobjetctx.EcrireObjetContexte();
}

void MainWindow::NettoyerLaScene( bool okquestion )
{
    QGraphicsItem *pobjet;
    QList<QGraphicsItem *> tabitem = pscene->items();
    if(!tabitem.isEmpty())
    {
        quitter->setIcon(QIcon(QPixmap(":/icone/quitter2.png")));
        bool nettoyer=true;
        if(okquestion)
            nettoyer = messagemsa->QuestionSuppression("Souhaitez-vous vraiment TOUT supprimer ?");
        if(nettoyer)
        {
           Element *pelem;
           for(int i=0;i<tabitem.length();i++)
           {
               pobjet = tabitem.at(i);
               pelem = (Element *)pobjet;
               pscene->removeItem(pobjet);
               if(pelem->GenreElement()==100)
                   delete (Logiciel *)pobjet;
           }
        }
        quitter->setIcon(QIcon(QPixmap(":/icone/quitter1.png")));
    }
}

Element *MainWindow::LogicielSelectionne()
{
    QGraphicsItem *pobjet;
    QList<QGraphicsItem *> tabitem = pscene->items();
    for(int i=0;i<tabitem.length();i++)
    {
        pobjet = tabitem.at(i);
        if(pobjet->isSelected())
        {
            Element *pelem = (Element *)pobjet;
            if(pelem->GenreElement()==100)
                return pelem;
        }
    }
    return NULL;
}

void MainWindow::AjouterConnexion( QGraphicsItem *psource, QGraphicsItem *pcible )
{
    CfgMTStartApp.PointeurCo()->encours=0;
    Logiciel *plsource   = (Logiciel *)psource;
    Logiciel *plcible     = (Logiciel *)pcible;
    if(plsource->CreerUneConnexionNouvelle( plsource, plcible ))
    {
        plcible->EntrerUneConnexion((Connexion *)plsource->ValeurConnexion());
        pscene->addItem(plsource->ValeurConnexion() );
    }
}

void MainWindow::AjouterFichier(Logiciel *plogi, Fichier *pfic )
{
    pfic->setPos(poselemdefaut);
    pscene->addItem((QGraphicsItem *)pfic);
    if(plogi->ConnecterFichier( pfic ))
    {
        pfic->EntrerUneConnexion((Connexion *)plogi->ValeurConnexion());
        pscene->addItem( plogi->ValeurConnexion() );
    }
}

void MainWindow::SupprimerUnObjet( QGraphicsItem *pobjet   )
{
    Element *pelem = (Element *)pobjet;
    pscene->removeItem(pobjet);
    switch(pelem->GenreElement())
    {
    case    100:{
            Logiciel *plogi= (Logiciel *)pelem;
            SupprimerFichiersDe( plogi );
            SupprimerConnexionsDe( plogi );
            delete plogi;
        }break;
    case    200:
        SupprimerFichierCFG( (FichierConfiguration *)pelem, false );
        break;
    case    300:
        SupprimerFichierTRV( (FichierTravail *)pelem, false );
        break;
    default :
        messagemsa->ObjetInconnu();
    }
}

void MainWindow::SupprimerConnexionsDe( GraphObjetActif *pobjactif   )
{
    GraphObjetActif  *pobjconnecte = NULL;
    Connexion *pconex  = pobjactif->DerniereConnexionDeLaListe();
    while(pconex!=NULL)
    {
        pobjconnecte = (GraphObjetActif *)pconex->ValeurAutreConnecter(pobjactif);
        pscene->removeItem((QGraphicsItem *)pconex);// supprimer le graphique
        pobjconnecte->Deconnecter(pconex,false);// supprimer lien dans un des objets liés
        pobjactif->Deconnecter(pconex,true);// supprimer lien et liberer pointeur
        pconex  = pobjactif->DerniereConnexionDeLaListe();
    }
//    return (Element *)pconex;
}

void MainWindow::SupprimerFichiersDe( Logiciel *plogi  )
{
    SupprimerFichierCFG( plogi->PtrFicCfg(), true );
    SupprimerFichierTRV( plogi->PtrFicTrv(), true );
}

void MainWindow::SupprimerFichierCFG( FichierConfiguration *ptrfic, bool retirerscene )
{
    if(ptrfic!=NULL)
    {
        SupprimerConnexionsDe((GraphObjetActif *)ptrfic );
        if( retirerscene ) pscene->removeItem((QGraphicsItem *)ptrfic);
        delete ptrfic;
    }
}

void MainWindow::SupprimerFichierTRV( FichierTravail *ptrfic, bool retirerscene )
{
    if(ptrfic!=NULL)
    {
        SupprimerConnexionsDe((GraphObjetActif *)ptrfic );
        if( retirerscene ) pscene->removeItem((QGraphicsItem *)ptrfic);
        delete ptrfic;
    }
}

void MainWindow::TuerProcess()
{
    if(!demarreur.DesProcessusSontDemarres())
        messagemsa->PasDeLogicielsDemarres();
    else
    {
        if(messagemsa->ArretDesLogiciels())
        {
            demarreur.ArreterLesProcessus();
        }
    }
}

/*******************************************
 Zone des Initialisation affichage et menus
********************************************/

void MainWindow::ConfigurationFenetre()
{
    QColor valfond;
    valfond.setNamedColor(CfgMTStartApp.PointeurGe()->CouleurMenu());

    QPalette fond;
    fond.setColor(QPalette::Active,QPalette::Window,valfond);
    fond.setColor(QPalette::Inactive,QPalette::Window,valfond);
    QWidget::setPalette(fond);
}

void MainWindow::TitreDeLaFenetre()
{
    phrtmp.clear();
    phrtmp.append("Démarreur multi application - session : ");
    phrtmp.append(session.NomDuProjet().toUpper());
    phrtmp.append("  contexte : ");
    phrtmp.append(session.NomDuContexte().toUpper());
    setWindowTitle(phrtmp);
//#if QT_VERSION >= QT_VERSION_CHECK(6, 4, 0)

//#endif

}

void MainWindow::CreerLeMenu()
{
    pscene = new QGraphicsScene;

    ConfigurationFenetre();

    h1Splitter = new QSplitter;
    vSplitter  = new QSplitter;

    vSplitter->setOrientation(Qt::Vertical);
    vSplitter->addWidget(h1Splitter);

    pview = new CadreZoneGraphique("scene");
    pview->PtrZonePartieDeScene()->setScene(pscene);
    h1Splitter->addWidget(pview);

    layoutcentre = new QVBoxLayout;
    layoutcentre->addLayout(BarreBoutonGHaut(),0);
    layoutcentre->addWidget(vSplitter);

    BarreBoutonLogiciel();

    layoutdroite = new QGridLayout;
    layoutdroite->addLayout(BarreBoutonHaut(),1,0);
    layoutdroite->addLayout(BarreBoutonGestion(),2,0);
    layoutdroite->addLayout(BarreBoutonFin(),4,0);

    topLayout = new QGridLayout;
    topLayout->addLayout(layoutgauche, 0, 0);
    topLayout->addLayout(layoutcentre, 0, 1);
    topLayout->addLayout(layoutdroite, 0, 2);

    setLayout(topLayout);

}

void MainWindow::CreerUnBouton( QToolButton *qbt,
                                const QString &icone,
                                const QString &msg,
                                int tailleicone,
                                bool okappli )
{
    QString ptmp(icone);
    if(ptmp.isEmpty())
    {
        if(okappli)
            ptmp = ":/icone/multistartapp.png";
        else
            ptmp = ":/icone/demarre.png";
    }
    else
    {
        if(ptmp.operator [](0)!=':')
        {
//            ptmp = session.CheminRacine();
//            ptmp.append(icone);
            QFile fichiertest;
            fichiertest.setFileName( ptmp );
            if(!fichiertest.exists())
                ptmp = ":/icone/multistartapp.png";
        }
    }
    qbt->setIcon(QIcon(QPixmap(ptmp)));
    qbt->setIconSize(QSize(tailleicone,tailleicone));
    qbt->setToolTip(msg);
}

QBoxLayout* MainWindow::BarreBoutonHaut()
{
    QVBoxLayout *barrevert = new QVBoxLayout;
    int htico = CfgMTStartApp.HtrIcoGes();
    lancer = new QToolButton;
        CreerUnBouton( lancer,":/icone/demarre.png","démarrer le dernier contexte (ou celui qui est chargé)",htico);
           barrevert->addWidget(lancer);
    eradiquer = new QToolButton;
        CreerUnBouton( eradiquer,":/icone/tuerprocess.png","arrêter tous les process lancés par ce contexte",htico);
           barrevert->addWidget(eradiquer);
    btapropos = new QToolButton;
        CreerUnBouton( btapropos,":/icone/apropos.png","à propos de ce que c'est !",htico);
            barrevert->addWidget(btapropos);

    connect(btapropos, SIGNAL(clicked()), this, SLOT(AProposDe()));
    connect(lancer, SIGNAL(clicked()), this, SLOT(LancerContexteEnCours()));
    connect(eradiquer, SIGNAL(clicked()), this, SLOT(StopperTout()));
    return barrevert;
}

QBoxLayout* MainWindow::BarreBoutonGestion()
{
    QVBoxLayout *barrevert = new QVBoxLayout;
    int htico = CfgMTStartApp.HtrIcoGes();
    choisir = new QToolButton;
        CreerUnBouton( choisir,":/icone/choisir.png","choisir un contexte pour modifier ou démarrer",htico);
           barrevert->addWidget(choisir);
    nouvproj = new QToolButton;
        CreerUnBouton( nouvproj,":/icone/nouvproj.png","créer un nouveau projet",htico);
            barrevert->addWidget(nouvproj);
    nouvcont = new QToolButton;
        CreerUnBouton( nouvcont,":/icone/nouvcont.png","créer un nouveau contexte de démarrage dans un projet et le configurer",htico);
            barrevert->addWidget(nouvcont);
    sauvegarder = new QToolButton;
        CreerUnBouton( sauvegarder,":/icone/sauvegarder1.png","sauver la configuration du contexte en cours",htico);
            barrevert->addWidget(sauvegarder);
    supprimer = new QToolButton;
        CreerUnBouton( supprimer,":/icone/supprimer1.png","supprimer l'objet sélectionné",htico);
            barrevert->addWidget(supprimer);
    nettoyer = new QToolButton;
        CreerUnBouton( nettoyer,":/icone/poubelle.png","supprimer tous les objets de la scène",htico);
            barrevert->addWidget(nettoyer);



    connect(nouvproj, SIGNAL(clicked()), this, SLOT(NouveauProjet()));
    connect(choisir, SIGNAL(clicked()), this, SLOT(ChoisirContexte()));
    connect(sauvegarder, SIGNAL(clicked()), this, SLOT(Sauvegarder()));
    connect(nouvcont, SIGNAL(clicked()), this, SLOT(NouveauContexte()));
    connect(supprimer, SIGNAL(clicked()), this, SLOT(SupprimerObjet()));
    connect(nettoyer, SIGNAL(clicked()), this, SLOT(NettoyerTout()));

    return barrevert;
}

QBoxLayout* MainWindow::BarreBoutonFin()
{
    QVBoxLayout *barrevert = new QVBoxLayout;

    int htico = CfgMTStartApp.HtrIcoGes();

    configuration = new QToolButton;
        CreerUnBouton( configuration,":/icone/configuration.png","configurer multistartapp",htico);
            barrevert->addWidget(configuration);
    quitter = new QToolButton;
        CreerUnBouton( quitter,":/icone/quitter1.png","tirer le rideau",htico);
            barrevert->addWidget(quitter);

    connect(configuration, SIGNAL(clicked()), this, SLOT(Configuration()));
    connect(quitter, SIGNAL(clicked()), this, SLOT(Quit()));
    return barrevert;
}

QBoxLayout* MainWindow::BarreBoutonGHaut()
{
    QHBoxLayout *barrehorz = new QHBoxLayout;
    int htico = CfgMTStartApp.HtrIcoDessous();

    lierobjet = new QToolButton;
        CreerUnBouton( lierobjet,":/icone/liaison.png","lier deux objets",htico);
            barrehorz->addWidget(lierobjet);
    ficcfg = new QToolButton;
        CreerUnBouton( ficcfg,":/icone/ficcfg.png","lier un fichier configuration au logiciel",htico);
            barrehorz->addWidget(ficcfg);
    fictrv = new QToolButton;
        CreerUnBouton( fictrv,":/icone/fictrv.png","lier un fichier de travail au logiciel",htico);
            barrehorz->addWidget(fictrv);
    centrervue = new QToolButton;
        CreerUnBouton( centrervue, ":/icone/recadrer.png", "centrer le schéma", htico);
            barrehorz->addWidget(centrervue);


    connect(lierobjet, SIGNAL(clicked()), this, SLOT(LierDesObjets()));
    connect(ficcfg, SIGNAL(clicked()), this, SLOT(FichierDeConfiguration()));
    connect(fictrv, SIGNAL(clicked()), this, SLOT(FichierDeTravail()));
    connect(centrervue, SIGNAL(clicked()), this, SLOT(CentrerSchema()));

    return barrehorz;
}

void MainWindow::BarreBoutonLogiciel()
{
    QList<quint8> lstclasse;
    lstbtnlogiciel.clear();
    lstcollogiciel.clear();
    layoutgauche = new QGridLayout;
    triagelogiciel = new QSignalMapper(this);
    if(CfgMTStartApp.ListeDesClassesLogiciels(lstclasse,true))
    {
        ptrenrglogiciel ptrlogiciel=NULL;
        int htico = CfgMTStartApp.HtrIcoLog();
        for(int indexcol=0;indexcol<lstclasse.length();indexcol++)
        {
            QVBoxLayout *barrevrt = new QVBoxLayout;
            int indexlig=0;
            ptrlogiciel = CfgMTStartApp.PointerClasseLogiciel( lstclasse[indexcol] );
            while(ptrlogiciel!=NULL)
            {
                QToolButton *tmpbtn = new QToolButton;
                CreerUnBouton( tmpbtn, ptrlogiciel->Icone(), ptrlogiciel->Aide(), htico, true);
                barrevrt->addWidget(tmpbtn);
                lstbtnlogiciel.append( tmpbtn );
                connect(tmpbtn, SIGNAL(clicked()), triagelogiciel, SLOT(map()) );
                triagelogiciel->setMapping( tmpbtn, lstclasse[indexcol]*100+indexlig );
                ptrlogiciel = CfgMTStartApp.LireLogicielParClasse();
                indexlig++;
            }
            lstcollogiciel.append(barrevrt);
            layoutgauche->addLayout(barrevrt,1,indexcol,Qt::AlignTop);
        }
        connect(triagelogiciel, SIGNAL(mappedInt(int)), this, SLOT(AjouterLogiciel(int)));
    }
}
