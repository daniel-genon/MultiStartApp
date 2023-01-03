#include "dialogconfiggenerale.h"
#include "ui_dialogconfiggenerale.h"
#include <QColor>
#include <qcolordialog.h>
#include <qfiledialog.h>
#include <qinputdialog.h>
#include "infovariablemsa.h"

DialogConfigGenerale::DialogConfigGenerale(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfigGenerale)
{
    ui->setupUi(this);
    msgmsa = new MessageMSA(this);
}

DialogConfigGenerale::~DialogConfigGenerale()
{
    delete msgmsa;
    delete ui;
}

void DialogConfigGenerale::IniBoite(FBlocConfig *pvaleur, LstVarMSA *lvarmsa )
{
    pfichier    = pvaleur;
    plvarmsa    = lvarmsa;
    TransfererValeur();
    InitialiserValeur();
    if(ui->LST_Configuration->count()==0)
        ui->BTN_charger->hide();

}

void DialogConfigGenerale::on_btcoulfondgraph_clicked(){    CouleurBouton(0);}
void DialogConfigGenerale::on_btcoulfondmenu_clicked(){    CouleurBouton(1);}
void DialogConfigGenerale::on_btcoulpolgen_clicked(){    CouleurBouton(2);}
void DialogConfigGenerale::on_btcoulconnexion_0_clicked(){    CouleurBouton(12);}
void DialogConfigGenerale::on_btcoulconnexion_1_clicked(){    CouleurBouton(13);}
void DialogConfigGenerale::on_btcoulconnexion_2_clicked(){    CouleurBouton(14);}
void DialogConfigGenerale::on_btcoulfondelmgraph_clicked(){    CouleurBouton(4);}
void DialogConfigGenerale::on_btcoulbandelmgraph_clicked(){    CouleurBouton(5);}
void DialogConfigGenerale::on_btcoulpolelmgraph_clicked(){    CouleurBouton(6);}
void DialogConfigGenerale::on_btcoulfondficli_clicked(){    CouleurBouton(7);}
void DialogConfigGenerale::on_btcoulbandficli_clicked(){    CouleurBouton(8);}
void DialogConfigGenerale::on_btcoulpolficli_clicked(){    CouleurBouton(9);}
void DialogConfigGenerale::on_btcoulfondancre_clicked(){    CouleurBouton(10);}
void DialogConfigGenerale::on_btcoulpolancre_clicked(){    CouleurBouton(11);}

void DialogConfigGenerale::CouleurBouton(int cas)
{
    IniCouleur(cas);
    BoiteACouleur();
}
void DialogConfigGenerale::InitialiserValeur()
{
    QStringList lstmp;
        indgraph=0;
        indlogic=0;
        indficli=0;
        indconfg=0;
        indpagew=ui->tabWidget->currentIndex();

    pfichier->Lister(lstmp);
    if(!lstmp.isEmpty())
    {
        ui->LST_Configuration->addItems(lstmp);
        indconfg = lstmp.indexOf(econfig.Nom());
        ui->LST_Configuration->setCurrentRow(indconfg);
        pfichier->LireConfiguration(econfig.Nom());
    }

// init valeur générale et connexion
    /*
            NoPen,
            SolidLine,
            DashLine,
            DotLine,
            DashDotLine,
    */
    ui->boitetpligne_0->addItem("continu");
    ui->boitetpligne_0->addItem("tirets");
    ui->boitetpligne_0->addItem("pointillé");
    ui->boitetpligne_0->addItem("axe");
        ui->boitetpligne_1->addItem("continu");
        ui->boitetpligne_1->addItem("tirets");
        ui->boitetpligne_1->addItem("pointillé");
        ui->boitetpligne_1->addItem("axe");
            ui->boitetpligne_2->addItem("continu");
            ui->boitetpligne_2->addItem("tirets");
            ui->boitetpligne_2->addItem("pointillé");
            ui->boitetpligne_2->addItem("axe");
// init graphique
    for(int i=0; i<lstgraph.length(); i++)
        ui->LST_Priorite->addItem(lstgraph.at(i)->Nom());
// init logiciel
    for(int i=0; i<lstlogiciel.length(); i++)
        ui->LST_Logiciel->addItem(lstlogiciel.at(i)->NomClair());
    GererZoneVariable_MSA();
 // init fichier lie
    for(int i=0; i<lstficlie.length(); i++)
        ui->LST_FicCFGLog->addItem(lstficlie.at(i)->Nom());
    AfficherValeur();
}
void DialogConfigGenerale::AfficherValeur()
{
    AfficherConfigConnexion();
    AfficherGraphique();
    AfficherLogiciel();
    AfficherGraphFicLie();
    indpagew=0;
    ui->tabWidget->setCurrentIndex(indpagew);
}
void DialogConfigGenerale::AfficherConfigConnexion()
{
    ui->policegen->setCurrentFont(QFont(econfig.Police().Nom()));
    ui->hautpolgen->setValue(econfig.Police().Hauteur());
    ui->hauticodessous->setValue(econfig.IconeDessous());
    ui->hauticodrt->setValue(econfig.IconeGestion());
    ui->hauticogah->setValue(econfig.IconeSymbole());
        ColoriserBouton(0);// fond
        ColoriserBouton(1);// menu
        ColoriserBouton(2);// police

    ui->eprconnect_0->setValue(econnex.tligne[0].Epaisseur());
    ui->boitetpligne_0->setCurrentIndex(econnex.tligne[0].TypeLigne());
    ui->eprconnect_1->setValue(econnex.tligne[1].Epaisseur());
    ui->boitetpligne_1->setCurrentIndex(econnex.tligne[1].TypeLigne());
    ui->eprconnect_2->setValue(econnex.tligne[2].Epaisseur());
    ui->boitetpligne_2->setCurrentIndex(econnex.tligne[2].TypeLigne());
        ColoriserBouton(12);// ligne logiciel
        ColoriserBouton(13);// ligne logiciel
        ColoriserBouton(14);// ligne logiciel

    ui->hautpolancre->setValue(econnex.enrancrage.PPolice()->Hauteur());
    ui->policeancre->setCurrentFont(QFont(econnex.enrancrage.PPolice()->Nom()));
    ui->hautancre->setValue(econnex.enrancrage.Hauteur());
    ui->largancre->setValue(econnex.enrancrage.Largeur());
    ui->L_imicoancre->setText(econnex.enrancrage.Icone());
        ColoriserBouton(10);// ancre fond
        ColoriserBouton(11);// ancre police

}
void DialogConfigGenerale::AfficherLogiciel()
{
    if(lstlogiciel.length()>0)
    {
        ui->LST_Logiciel->setCurrentRow(indlogic);
        ui->L_dossierprocessus->setText(lstlogiciel.at(indlogic)->Dossier());
        ui->L_aide->setText(lstlogiciel.at(indlogic)->Aide());
        ui->L_imicone->setText(lstlogiciel.at(indlogic)->Icone());
        ui->L_nomprocessus->setText(lstlogiciel.at(indlogic)->NomProcessus());
        ui->L_options->setText(lstlogiciel.at(indlogic)->Options());
        ui->L_dependance->setText(lstlogiciel.at(indlogic)->Dependance());
        ui->classemenu->setValue(lstlogiciel[indlogic]->Classe());
        ui->delaiprocess->setValue(lstlogiciel[indlogic]->Delai());
        if(lstlogiciel.operator[](indlogic)->UniqueB())
            ui->B_uniquedugenre->setCheckState(Qt::Checked);
        else
            ui->B_uniquedugenre->setCheckState(Qt::Unchecked);
        ui->L_stdcfg->setText(lstlogiciel.at(indlogic)->StdCFG());
        ui->L_stdtrv->setText(lstlogiciel.at(indlogic)->StdTRV());
        ui->L_optCFG->setText(lstlogiciel.at(indlogic)->OptCFG());
        ui->L_optTRV->setText(lstlogiciel.at(indlogic)->OptTRV());
    }
    else
    {
        ui->L_dossierprocessus->clear();
        ui->L_aide->clear();
        ui->L_imicone->clear();
        ui->L_nomprocessus->clear();
        ui->L_options->clear();
        ui->L_dependance->clear();
        ui->classemenu->setValue(1);
        ui->delaiprocess->setValue(5);
        ui->B_uniquedugenre->setCheckState(Qt::Unchecked);
        ui->L_stdcfg->clear();
        ui->L_stdtrv->clear();
        ui->L_optCFG->clear();
        ui->L_optTRV->clear();
    }
    if(ui->QCVarMultStart->isVisible())
    {
        if(plvarmsa->VerifierVariableMSA(ui->L_options->text()))
        {
            qsizetype i = ui->QCVarMultStart->findText(plvarmsa->RtPtrEnrg()->Valeur());
            if( i != -1 )
            {
                ui->QCVarMultStart->setCurrentIndex(i);
            }
        }
    }
}
void DialogConfigGenerale::AfficherGraphique()
{
    if(lstgraph.length()>0)
    {
        ui->LST_Priorite->setCurrentRow(indgraph);
        ui->policegraph->setCurrentFont(QFont(lstgraph.at(indgraph)->PPolice()->Nom()));
        ui->hautpolgraph->setValue(lstgraph.at(indgraph)->PPolice()->Hauteur());
        ui->hautsym->setValue(lstgraph.at(indgraph)->Hauteur());
        ui->largesym->setValue(lstgraph.at(indgraph)->Largeur());
        ui->niveauprio->setValue(lstgraph.at(indgraph)->Priorite());
        ColoriserBouton(4);
        ColoriserBouton(5);
        ColoriserBouton(6);
    }
    else
    {
        ui->policegraph->setCurrentFont(QFont("Bitstream Charter"));
        ui->hautpolgraph->setValue(12);
        ui->hautsym->setValue(60);
        ui->largesym->setValue(160);
        ui->niveauprio->setValue(126);

        couleurboite.setNamedColor("#89fbfa");
        ptrboutontraite = ui->btcoulfondelmgraph;
        ColoriserBouton();
        couleurboite.setNamedColor("#ffff00");
        ptrboutontraite = ui->btcoulbandelmgraph;
        ColoriserBouton();
        couleurboite.setNamedColor("#000000");
        ptrboutontraite = ui->btcoulpolelmgraph;
        ColoriserBouton();
    }
}
void DialogConfigGenerale::AfficherGraphFicLie()
{
    ui->LST_FicCFGLog->setCurrentRow(indficli);
    ui->policeficli->setCurrentFont(QFont(lstficlie.at(indficli)->PPolice()->Nom()));
    ui->hautpollie->setValue(lstficlie.at(indficli)->PPolice()->Hauteur());
    ui->hautsymlie->setValue(lstficlie.at(indficli)->Hauteur());
    ui->largesymlie->setValue(lstficlie.at(indficli)->Largeur());
    ColoriserBouton(7);
    ColoriserBouton(8);
    ColoriserBouton(9);
}
void DialogConfigGenerale::ColoriserBouton( int i )
{
    IniCouleur(i);
    ColoriserBouton();
}
void DialogConfigGenerale::ColoriserBouton()
{
    QString phrCSS = QString("QPushButton { background-color: %1; }").arg(couleurboite.name());
    ptrboutontraite->setStyleSheet(phrCSS);
//    pcouleurencours->clear();
//    pcouleurencours->append( toto );
}
bool DialogConfigGenerale::BoiteACouleur()
{
    QColorDialog dlcol;
    dlcol.setModal(true);
    dlcol.setCurrentColor(couleurboite);

    if(dlcol.exec()!=QDialog::Accepted) return false;

    couleurboite = dlcol.selectedColor();
    ColoriserBouton();
    return true;
}
void DialogConfigGenerale::IniCouleur( int cas )
{
    switch(cas)
    {
    case 0:
            couleurboite.setNamedColor(econfig.CouleurGraphique());
            ptrboutontraite = ui->btcoulfondgraph;
            break;
    case 1:
            couleurboite.setNamedColor(econfig.CouleurMenu());
            ptrboutontraite = ui->btcoulfondmenu;
            break;
    case 2:
            couleurboite.setNamedColor(econfig.Police().Couleur());
            ptrboutontraite = ui->btcoulpolgen;
            break;
//    case 3:
//            couleurboite.setNamedColor(econnex.Couleur());
//            ptrboutontraite = ui->btcoulconnexion;
//            break;
    case 4:
            couleurboite.setNamedColor(lstgraph.at(indgraph)->CouleurFond());
            ptrboutontraite = ui->btcoulfondelmgraph;
            break;
    case 5:
            couleurboite.setNamedColor(lstgraph.at(indgraph)->CouleurBandeau());
            ptrboutontraite = ui->btcoulbandelmgraph;
            break;
    case 6:
            couleurboite.setNamedColor(lstgraph.at(indgraph)->Police().Couleur());
            ptrboutontraite = ui->btcoulpolelmgraph;
            break;
    case 7:
            couleurboite.setNamedColor(lstficlie.at(indficli)->CouleurFond());
            ptrboutontraite = ui->btcoulfondficli;
            break;
    case 8:
            couleurboite.setNamedColor(lstficlie.at(indficli)->CouleurBandeau());
            ptrboutontraite = ui->btcoulbandficli;
            break;
    case 9:
            couleurboite.setNamedColor(lstficlie.at(indficli)->Police().Couleur());
            ptrboutontraite = ui->btcoulpolficli;
            break;
    case 10:
            couleurboite = econnex.enrancrage.CouleurFond();
            ptrboutontraite = ui->btcoulfondancre;
            break;
    case 11:
            couleurboite.setNamedColor(econnex.enrancrage.PPolice()->Couleur());
            ptrboutontraite = ui->btcoulpolancre;
            break;
    case 12:
            couleurboite.setNamedColor(econnex.tligne[0].Couleur());
            ptrboutontraite = ui->btcoulconnexion_0;
            break;
    case 13:
            couleurboite.setNamedColor(econnex.tligne[1].Couleur());
            ptrboutontraite = ui->btcoulconnexion_1;
            break;
    case 14:
            couleurboite.setNamedColor(econnex.tligne[2].Couleur());
            ptrboutontraite = ui->btcoulconnexion_2;
            break;
    }
}

void DialogConfigGenerale::on_tabWidget_currentChanged(int index)
{
    switch(indpagew)
    {
    case 0:
        CollationnerConfig();
        break;
    case 1:
        CollationnerConnexion();
        break;
    case 2:
        CollationnerLogiciel();
        break;
    case 3:
        CollationnerPriorite();
        break;
    case 4:
        CollationnerGraphFicLie();
        break;
    }
    indpagew = index;
}
void DialogConfigGenerale::on_LST_Configuration_clicked(const QModelIndex &index)
{
    if(SauvegardeOK())
    {
        if(indconfg!=index.row())
        {
            indconfg = index.row();
            if(pfichier->LireConfiguration(ui->LST_Configuration->currentItem()->text()))
                AfficherValeur();
        }
    }
}
void DialogConfigGenerale::on_LST_Priorite_clicked(const QModelIndex &index)
{
    CollationnerPriorite();
    indgraph = index.row();
    AfficherGraphique();

}
void DialogConfigGenerale::on_LST_Logiciel_clicked(const QModelIndex &index)
{
    CollationnerLogiciel();
    indlogic = index.row();
    AfficherLogiciel();
}
void DialogConfigGenerale::on_LST_FicCFGLog_clicked(const QModelIndex &index)
{
    CollationnerGraphFicLie();
    indficli = index.row();
    AfficherGraphFicLie();
}
void DialogConfigGenerale::on_buttonBox_clicked(QAbstractButton *)
{
    on_tabWidget_currentChanged(indpagew);
    if(SauvegardeOK())
        accept();
    else
        reject();
}
void DialogConfigGenerale::on_BTN_nouvelle_clicked()
{
    if(SauvegardeOK())
    {
        int nb=0;
        QString nomconfig;
        do{
            nomconfig = QString("fichierconfig%1").arg(nb);nb++;
        }while(!ui->LST_Configuration->findItems( nomconfig, Qt::MatchFixedString).isEmpty());
        //        EntrerUnNom dlgn;
        //        dlgn.setModal(true);
        //        dlgn.IniNom(&nomconfig);
        //        if(dlgn.exec()==QDialog::Accepted)
        //        {
        //            dlgn.collationner();
        bool ok;
        nomconfig = QInputDialog::getText(this, tr("Configuration"),
                                              tr("nom :"), QLineEdit::Normal,
                                              nomconfig, &ok,
                                              Qt::WindowFlags(),
                                              Qt::ImhLowercaseOnly|Qt::ImhDigitsOnly);
        if(ok && !nomconfig.isEmpty())
        {
            if(ui->LST_Configuration->findItems( nomconfig, Qt::MatchFixedString).isEmpty())
            {
                ui->LST_Configuration->addItem(nomconfig);
                ui->LST_Configuration->setCurrentRow(ui->LST_Configuration->count()-1);
                econfig.Nom(nomconfig);
                CollationnerValeur();
                pfichier->EcrireConfig();
            }
            else
                msgmsa->AlerteMessage("Création d'une configuration","Le nom existe !");

        }
    }
}
void DialogConfigGenerale::on_BTN_charger_clicked()
{
    CollationnerValeur();
    accept();
}

void DialogConfigGenerale::CollationnerValeur()
{
    pfichier->penrg->Valeur(econfig);

    pfichier->plstlog->Nettoyer();
    pfichier->plstlog->Copier(lstlogiciel);

    pfichier->plstpri->Nettoyer();
    pfichier->plstfic->Nettoyer();
    pfichier->plstpri->Copier(lstgraph);
    pfichier->plstfic->Copier(lstficlie);

    pfichier->pconnexion->Valeur(econnex);
}
void DialogConfigGenerale::TransfererValeur()
{
    econfig.Valeur( *pfichier->penrg);
    lstlogiciel.Copier( *pfichier->plstlog );
    lstgraph.Copier( *pfichier->plstpri );
    econnex.Valeur( *pfichier->pconnexion);
    lstficlie.Copier( *pfichier->plstfic );
}
bool DialogConfigGenerale::ValeursModifiees()
{
    if(ConfigGeneralModifiee()) return true;
    if(LogicielModifie()) return true;
    if(PrioriteModifiee()) return true;
    if(ConnexionModifiee()) return true;
    if(FiclieModifie()) return true;
    return false;
}
bool DialogConfigGenerale::SauvegardeOK()
{
    if(ValeursModifiees())
    {
        if(msgmsa->QuestionMSA("Sauvegarde configuration",
                               "Des valeurs de la configuration ont été modifiées. <br/>Sauver les modifications ?"))
        {
            CollationnerValeurs();
            CollationnerValeur();//sauver
            pfichier->ModifierConfig();
        }
        return true;
    }
    return false;//abandonner la commande
}
void DialogConfigGenerale::CollationnerConfig()
{
    poltmp.Valeur(ui->policegen->currentText(),CouleurBouton(ui->btcoulpolgen),
                  ui->hautpolgen->value());
    econfig.Valeur(ui->LST_Configuration->currentItem()->text(),
                   CouleurBouton(ui->btcoulfondgraph),CouleurBouton(ui->btcoulfondmenu),poltmp,
                   ui->hauticodrt->value(),ui->hauticogah->value(),ui->hauticodessous->value());
}
void DialogConfigGenerale::CollationnerLogiciel()
{
    if(lstlogiciel.length()>0)
    {
        quint8 unique=0;
        if(ui->B_uniquedugenre->isChecked()) unique=1;

        lstlogiciel[indlogic]->Valeur( ui->L_nomprocessus->text(),
                                       ui->LST_Logiciel->item( indlogic )->text(),
                                       ui->L_options->text(),
                                       ui->L_aide->text(),
                                       ui->L_dossierprocessus->text(),
                                       ui->L_imicone->text(),
                                       ui->L_dependance->text(),
                                       ui->delaiprocess->value(),
                                       unique,
                                       ui->classemenu->value(),
                                       ui->L_stdcfg->text(),
                                       ui->L_stdtrv->text(),
                                       ui->L_optCFG->text(),
                                       ui->L_optTRV->text()
                                       );
    }
}
void DialogConfigGenerale::CollationnerPriorite()
{
    if(lstgraph.length()>0)
    {
        poltmp.Valeur( ui->policegraph->currentText(),
                    CouleurBouton(ui->btcoulpolelmgraph),ui->hautpolgraph->value());

        lstgraph[indgraph]->Valeur(ui->LST_Priorite->item( indgraph )->text(),CouleurBouton(ui->btcoulfondelmgraph),
                    CouleurBouton(ui->btcoulbandelmgraph),
                    poltmp,ui->largesym->value(),ui->hautsym->value(),ui->niveauprio->value());
    }
}
void DialogConfigGenerale::CollationnerConnexion()
{
    poltmp.Valeur(ui->policeancre->currentText(),CouleurBouton(ui->btcoulpolancre),
                  ui->hautpolancre->value());

    econnex.tligne[0].Valeur(CouleurBouton(ui->btcoulconnexion_0),ui->boitetpligne_0->currentIndex(),
                   ui->eprconnect_0->value());
    econnex.tligne[1].Valeur(CouleurBouton(ui->btcoulconnexion_1),ui->boitetpligne_1->currentIndex(),
                   ui->eprconnect_1->value());
    econnex.tligne[2].Valeur(CouleurBouton(ui->btcoulconnexion_2),ui->boitetpligne_2->currentIndex(),
                   ui->eprconnect_2->value());

    econnex.enrancrage.Valeur(ui->L_imicoancre->text(),CouleurBouton(ui->btcoulfondancre),poltmp,
                 ui->largancre->value(),ui->hautancre->value());
}
void DialogConfigGenerale::CollationnerGraphFicLie()
{
    poltmp.Valeur( ui->policeficli->currentText(),
                   CouleurBouton(ui->btcoulpolficli),ui->hautpollie->value());
    lstficlie[indficli]->Valeur(ui->LST_FicCFGLog->item( indficli )->text(),
                               CouleurBouton(ui->btcoulfondficli),
                               CouleurBouton(ui->btcoulbandficli),poltmp,
                               ui->largesymlie->value(),ui->hautsymlie->value(),0);
}
void DialogConfigGenerale::CollationnerValeurs()
{
    CollationnerConfig();
    CollationnerConnexion();
    CollationnerPriorite();
    CollationnerLogiciel();
    CollationnerGraphFicLie();
}
bool DialogConfigGenerale::ConfigGeneralModifiee()
{
    CollationnerConfig();
    return !pfichier->penrg->EgaleA(econfig,false);
}
bool DialogConfigGenerale::LogicielModifie()
{
    return !pfichier->plstlog->EgaleA(lstlogiciel,false);
}
bool DialogConfigGenerale::PrioriteModifiee()
{
    return !pfichier->plstpri->EgaleA(lstgraph,false);
}
bool DialogConfigGenerale::ConnexionModifiee()
{
    return !pfichier->pconnexion->EgaleA(econnex);
}
bool DialogConfigGenerale::FiclieModifie()
{
    return !pfichier->plstfic->EgaleA(lstficlie);
}
QString DialogConfigGenerale::CouleurBouton( const QPushButton *bouton ) const
{
    QString b = bouton->styleSheet();
    int a = b.indexOf("background-color:");
    if(a==-1) return "#000000";
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
          return b.sliced((a+18),7);
#else
           return b.mid((a+18),7);
#endif
}
bool DialogConfigGenerale::Initialiser_Variable_MSA()
{
    if(plvarmsa)
    {
        if(plvarmsa->count()>0)
        {
            for(int i=0;i<plvarmsa->count();i++)
            {
                ui->QCVarMultStart->addItem(plvarmsa->at(i)->Valeur());
            }
            return true;
        }
    }
    return false;
}
void DialogConfigGenerale::GererZoneVariable_MSA()
{
    if(Initialiser_Variable_MSA())
    {
        ui->QCVarMultStart->show();
        ui->Insere_Variable->show();
        ui->label_VarMutApp->show();
        ui->Info_Variable->show();
    }
    else
    {
        ui->QCVarMultStart->hide();
        ui->Insere_Variable->hide();
        ui->label_VarMutApp->hide();
        ui->Info_Variable->hide();
    }
}


void DialogConfigGenerale::on_BTN_ajoutlog_clicked()
{
    QString nouveaulogiciel;
    bool    encore=true;
    while(encore)
    {
        bool ok;
        nouveaulogiciel.clear();
        nouveaulogiciel = QInputDialog::getText(this, tr("Ajout d'un logiciel"),
                                              tr("nom :"), QLineEdit::Normal,
                                              nouveaulogiciel, &ok,
                                              Qt::WindowFlags(),
                                              Qt::ImhLowercaseOnly|Qt::ImhDigitsOnly);
        if(ok && !nouveaulogiciel.isEmpty())
        {
            QString phrtmp = "Vous souhaitez ajouter le logiciel : ";
            phrtmp.append(nouveaulogiciel);
            if(msgmsa->QuestionMSA("Inserer un logiciel à la liste",phrtmp))
            {
                    lstlogiciel.Ajouter( nouveaulogiciel, nouveaulogiciel,"","","","","",5,0,1,"","","","");
                    ui->LST_Logiciel->addItem(nouveaulogiciel);
                    indlogic = ui->LST_Logiciel->count()-1;
                    AfficherLogiciel();
                    encore = false;
            }
        }
    }
}
void DialogConfigGenerale::on_BTN_supprlog_clicked()
{
    if(lstlogiciel.length()>0)
    {
        if(msgmsa->QuestionSuppression(tr("ATTENTION : si le logiciel est utilisé dans un contexte de lancement <br/> il ne pourra plus être démarré.")))
        {
            indlogic = ui->LST_Logiciel->currentRow();
            //ui->LST_Logiciel->removeItemWidget(ui->LST_Logiciel->currentItem());
            lstlogiciel.removeAt(indlogic);
            indlogic--;
            if(indlogic < 0) indlogic=0;
            ui->LST_Logiciel->clear();
            for(int i=0; i<lstlogiciel.length(); i++)
                ui->LST_Logiciel->addItem(lstlogiciel.at(i)->NomClair());
            AfficherLogiciel();
        }
    }
}
void DialogConfigGenerale::on_BTN_ajoutprio_clicked()
{
    QString nouvelleprio;
    bool    encore=true;
    while(encore)
    {
        encore = false;
        bool ok;
        nouvelleprio.clear();
        nouvelleprio = QInputDialog::getText(this, tr("Ajout d'une priorité"),
                                              tr("label :"), QLineEdit::Normal,
                                              nouvelleprio, &ok,
                                              Qt::WindowFlags(),
                                              Qt::ImhLowercaseOnly|Qt::ImhDigitsOnly);
        if(ok && !nouvelleprio.isEmpty())
        {
            QString phrtmp = "Souhaitez-vous ajouter <br/> le label de priorité : ";
            phrtmp.append(nouvelleprio);
            if(msgmsa->QuestionMSA("Inserer une priorité à la liste",phrtmp))
            {
                    EnrgPolice policetmp("Bitstream Charter","#000000",12);
                    lstgraph.Ajouter(nouvelleprio,"#fbae36","#ffff00",policetmp,150,60,126 );
                    ui->LST_Priorite->addItem(nouvelleprio);
                    indgraph = ui->LST_Priorite->count()-1;
                    AfficherGraphique();
                    encore=false;
            }
        }
    }

}
void DialogConfigGenerale::on_BTN_suppprio_clicked()
{
    if(lstgraph.length()>0)
    {
        if(msgmsa->QuestionSuppression(tr("ATTENTION : si l'élément est affecté à un ou plusieurs logigiels <br/> il ne sera plus pris en compte lors du démarrage.",
                              "Souhaitez-vous vraiment le supprimer ?")))
        {
            indgraph = ui->LST_Priorite->currentRow();
            lstgraph.removeAt(indgraph);
            indgraph--;
            if(indgraph < 0) indgraph=0;
            ui->LST_Priorite->clear();
            for(int i=0; i<lstgraph.length(); i++)
                ui->LST_Priorite->addItem(lstgraph.at(i)->Nom());
            AfficherGraphique();
        }
    }

}
void DialogConfigGenerale::on_s_proc_clicked()
{
    QString nomtmp = QFileDialog::getOpenFileName( this, "processus", ui->L_nomprocessus->text());
    if(!nomtmp.isEmpty())
    {
        QFileInfo nomfic ( nomtmp );
        ui->L_nomprocessus->setText( nomfic.fileName() );
        ui->L_dossierprocessus->setText( nomfic.filePath().left(nomtmp.length()-ui->L_nomprocessus->text().length()) );
    }
}

void DialogConfigGenerale::on_s_icon_clicked()
{
    QString nomtmp = QFileDialog::getOpenFileName( this, "processus", ui->L_nomprocessus->text());
    if(!nomtmp.isEmpty())
    {
        ui->L_imicone->setText( nomtmp );
    }
}

void DialogConfigGenerale::on_s_ch_proc_clicked()
{
    QString nomtmp = QFileDialog::getExistingDirectory( this, "chemin du processus", ui->L_nomprocessus->text() );
    if(!nomtmp.isEmpty())
    {
        ui->L_dossierprocessus->setText( nomtmp );
    }
}

void DialogConfigGenerale::on_s_cfg_clicked()
{
    QString nomtmp = QFileDialog::getOpenFileName( this, "fichier de configuration standard", ui->L_stdcfg->text() );
    if(!nomtmp.isEmpty())
    {
        QFileInfo nomfic ( nomtmp );
        ui->L_stdcfg->setText( nomfic.fileName() );
    }
}

void DialogConfigGenerale::on_s_trv_clicked()
{
    QString nomtmp = QFileDialog::getOpenFileName( this, "fichier de travail standard", ui->L_stdtrv->text() );
    if(!nomtmp.isEmpty())
    {
        QFileInfo nomfic ( nomtmp );
        ui->L_stdtrv->setText( nomfic.fileName() );
    }
}

void DialogConfigGenerale::on_Insere_Variable_clicked()
{
    if(plvarmsa->PointerValeur(ui->QCVarMultStart->currentText()))
    {
        QString phrtmpcode;
        if(plvarmsa->ConstruireInsertionCode(phrtmpcode))
        {
            QString phrtmp = ui->L_options->text();
            if(!phrtmp.isEmpty())
                phrtmpcode.prepend(",");
            phrtmp.append(phrtmpcode);
            ui->L_options->setText(phrtmp);
        }
    }
}

void DialogConfigGenerale::on_Info_Variable_clicked()
{
    if(plvarmsa->PointerValeur(ui->QCVarMultStart->currentText()))
    {
        InfoVariableMSA *dli = new InfoVariableMSA(this);
        dli->setModal(true);
        dli->IniBoite(plvarmsa->RtPtrEnrg());
        dli->exec();
        delete dli;
    }
}

