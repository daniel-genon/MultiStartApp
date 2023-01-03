#include "logiciel.h"
#include <QInputDialog>
#include "dialogue/messagemsa.h"

Logiciel::Logiciel(){}

Logiciel::Logiciel(ConfigurationObjet *ptrconf, QGraphicsScene *ptrscene )
{
    cfgobjet = ptrconf;
    pscene   = ptrscene;
    okvalide = false;
    if(ChoisirLaPriorite())
        InitLogiciel();
}

Logiciel::Logiciel( ConfigurationObjet *ptrconf, QGraphicsScene *ptrscene, quint8 noprio )
{
    cfgobjet = ptrconf;
    pscene   = ptrscene;
    okvalide = false;
    priorite = noprio;
    InitLogiciel();
}

void Logiciel::InitLogiciel()
{
    GenreElement( 100 );

    donneelogiciel.Valeur(cfgobjet->PointeurLo());
    NomElement(donneelogiciel.NomClair());

    if(!cfgobjet->PointerPriorite(priorite))
        priorite = cfgobjet->PointerPrioriteMinimum();

    Couleurs( cfgobjet->PointeurGr()->CouleurBandeau(), cfgobjet->PointeurGr()->CouleurFond() );
    Police( cfgobjet->PointeurGr()->Police() );
    EntrerValeurGraph( cfgobjet->PointeurGr()->Largeur(), cfgobjet->PointeurGr()->Hauteur() );
    InitIcone(donneelogiciel.Icone());
    okvalide = true;
}

bool Logiciel::ChoisirLaPriorite()
{
    QStringList lstinfo;
    QList<quint8> lstprio;
    if(cfgobjet->ListeDesPriorites(lstinfo , lstprio))
    {

        bool ok;
        QString strprio = QInputDialog::getItem(Q_NULLPTR,"Liste des priorités",
                            "ordre prioritaire et désignation", lstinfo, 0, false, &ok);
        if (ok && !strprio.isEmpty())
        {
            priorite = lstprio.at(lstinfo.indexOf(strprio));
            return true;
        }
    }
//    QStringList lstinfo;
//    if(cfgobjet->ListeDesPriorites( lstprio, lstinfo ))
//    {
//        ChoixDansListe  bdial;
//        bdial.EntrerTitreEtNota("Priorité de démarrage","Valeur numérique");
//        bdial.EntrerListes(lstprio,lstinfo);
//        if(bdial.exec()==QDialog::Accepted)
//        {
//            priorite = lstinfo.at( bdial.retindex ).toUShort();
//            return true;
//        }
//    }
    else
        MessageMSA::AlerteMessage("Il n'y a aucune priorité de configurée");
    return false;
}

void Logiciel::CollationnerDescripteur(EnrgObjetCtx *enrgtmp )
{
    enrgtmp->Raz();
    enrgtmp->ValeurObjet(libelle() , PositionXDansScene(), PositionYDansScene(), priorite );
    FichierTravail *PtFT = PtrFicTrv();
    FichierConfiguration *PtFC = PtrFicCfg();

    if( PtFT != NULL)
        PtFT->CollationnerDescripteur(enrgtmp);
    if(PtFC != NULL)
        PtFC->CollationnerDescripteur(enrgtmp);
}

FichierTravail *Logiciel::PtrFicTrv()
{
    if(TrouverConnexion(300))
        return (FichierTravail *)pelemresu;
    return NULL;
}

FichierConfiguration *Logiciel::PtrFicCfg()
{
    if(TrouverConnexion(200))
        return (FichierConfiguration *)pelemresu;
    return NULL;
}

void Logiciel::EcrireTitre()
{
    plume->drawText( TourInfo(), Qt::AlignCenter, donneelogiciel.NomProcessus() );
}
void Logiciel::EcrireNom()
{
    plume->drawText( TourCartouche(), Qt::AlignCenter, donneelogiciel.NomClair() );
}



////************************************************************
////    retour valeur
////************************************************************


QString Logiciel::libelle() const {    return donneelogiciel.NomClair(); }
QString Logiciel::NomStdCFG() const {    return donneelogiciel.StdCFG(); }
QString Logiciel::NomStdTRV() const {    return donneelogiciel.StdTRV(); }
quint8  Logiciel::Priorite() const {    return priorite; }

bool Logiciel::VerifierExistenceSurScene()
{
    if(donneelogiciel.UniqueB())
    {
        QList<QGraphicsItem *> tabitem = pscene->items();
        for(int i=0;i<tabitem.length();i++)
        {
            Element *pelem = (Element *)tabitem.at(i);
            if(pelem->GenreElement()==100)
            {// ok c'est un logiciel
                Logiciel *pobjet =  (Logiciel *) pelem;
                return pobjet->EstLeProcessus( donneelogiciel.NomProcessus());
            }
        }
    }
    return false;
}

bool Logiciel::EstLeProcessus( const QString &nomtest )
{
    return QString::compare( nomtest, donneelogiciel.NomProcessus(), Qt::CaseInsensitive) == 0;
}
bool Logiciel::AUnStdTRV()
{
    return !donneelogiciel.StdTRV().isEmpty();

}
bool Logiciel::AUnStdCFG()
{
    return !donneelogiciel.StdCFG().isEmpty();

}

QString Logiciel::ListeOptions() const{    return donneelogiciel.Options();}
QString Logiciel::OptCFG() const{    return donneelogiciel.OptCFG();}
QString Logiciel::OptTRV() const{    return donneelogiciel.OptTRV();}
QString Logiciel::Dependance() const{    return donneelogiciel.Dependance();}
QString Logiciel::NomDuProcess() const { return donneelogiciel.NomProcessus();}
QString Logiciel::CheminProcess() const{    return donneelogiciel.Dossier();}
QString Logiciel::NomFicStdTRV() const{    return donneelogiciel.StdTRV();}
QString Logiciel::NomFicStdCFG() const{    return donneelogiciel.StdCFG();}
quint8  Logiciel::DelaiApresDemarrage(){    return donneelogiciel.Delai();}
bool    Logiciel::UnSeulAutorise(){ return donneelogiciel.UniqueB();}


////************************************************************
////     Gestion des événements
////************************************************************


