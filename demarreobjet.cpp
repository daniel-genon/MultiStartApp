#include "demarreobjet.h"
#include "bloc/fictexte.h"

DemarreObjet::DemarreObjet()
{
    lstprocessus.clear();
    paquet  = 200000000;// pour délai d'attente => 1 = env 1 seconde
}
void DemarreObjet::InitSession( GererSession *valeur, QGraphicsScene *pvalscene  )
{
    psession    = valeur;
    pscene      = pvalscene;
}
bool DemarreObjet::ReinitialiserLaScene()
{
    tabitem = pscene->items();
    if(tabitem.isEmpty()) return false;
    ClasserObjets();
    return true;
}

int DemarreObjet::AjouterATable( Logiciel *plogi )
{
    quint8 valprio = plogi->Priorite();
    if(!tabdemarrage.isEmpty())
    {
        for(int j=0;j<tabdemarrage.length();j++)
        {
            if(tabdemarrage.at(j)->Priorite()<valprio)
            {
                tabdemarrage.insert(j,plogi);
                return j;
            }
        }
    }
    tabdemarrage.append(plogi);
    return (tabdemarrage.length()-1);
}

void DemarreObjet::ClasserObjets()
{
// classer les objets (sélectionner les logiciels dans l'ordre de leur priorité
    for(int i=0;i<tabitem.length();i++)
    {
        if(((Element *)tabitem.at(i))->EstUnLogiciel())
        {
           AjouterATable((Logiciel *)tabitem.at(i));
        }
    }

}
void DemarreObjet::DemarrerLaSession()
{
    lstprocessus.clear();
    nomfichiercfgobjet.clear();
    nomfichiertrvobjet.clear();
    phrasededemarreur.clear();
    phrasepouroptions.clear();
    bool oklancer       = true;
    if(ReinitialiserLaScene())
    {
        for(int i=0;i<tabdemarrage.length();i++)
        {
           plogi = tabdemarrage.at(i);
           nomdulogiciel = plogi->NomDuProcess();
           if(plogi->UnSeulAutorise())
               oklancer = !ProcessusExistant();
           else
               oklancer = true;
           if(oklancer)
           {
               PhraseFichierCFG();
               PhraseFichierTRV();
               if(LancerProcessus())
               {
                   IntegrerDansListeDesDemarres();
               }
           }
           else
           {// logiciel déjà démarré ( intégration dans la liste pour le stopper en fin de session)
               IntegrerDansListeDesDemarres();
           }
        }
    }
}
void DemarreObjet::IntegrerDansListeDesDemarres()
{
    lstprocessus.append(nomdulogiciel);
    IntegrerLesDependances();
}
void DemarreObjet::IntegrerLesDependances()
{
    lstdependance.clear();
    lstdependance.append(plogi->Dependance().split(','));
    if(!lstdependance.isEmpty())
    {
        lstprocessus.append(lstdependance);
    }
}

void DemarreObjet::PhraseFichierTRV()
{
// plogi contient le no item en objet "logiciel"
    if(plogi->PtrFicTrv()!=NULL)
        nomfichiertrvobjet = PhraseFichier( plogi->PtrFicTrv()->NomFichier(true), plogi->OptTRV() );
}

void DemarreObjet::PhraseFichierCFG()
{
// plogi contient le no item en objet "logiciel"
    if(plogi->PtrFicCfg()!=NULL)
        nomfichiercfgobjet = PhraseFichier( plogi->PtrFicCfg()->NomFichier(true), plogi->OptCFG() );
}

QStringList DemarreObjet::PhraseFichier(const QString &nmfic, const QString &opfic )
{
    QStringList nomliste;
    QString nomfichier(nmfic);
    QFileInfo nomfic(nomfichier);
    nomliste.clear();

    if(nomfic.path().isEmpty())
    {
        nomfichier = psession->CheminContexte();
        nomfichier.append(nmfic);
        nomfic.setFile(nomfichier);
    }
    if(nomfic.exists())
    {
        if(nomfic.suffix()==(QString("txt")))
        {
            QString ligne;
            FicTexte tmpfic( nomfichier, &ligne );
            if(tmpfic.OuvrirEnLecture())
            {
                if(tmpfic.LireEnContinu())
                {
                    if(ligne==(QString("nom-interne")))
                    {
                        nomfichier.clear();
                        if(tmpfic.LireEnContinu())
                            nomfichier=ligne;
                    }
                }
                tmpfic.FermerFichierContinu();
            }
        }
        if(!nomfichier.isEmpty())
        {
            if(!opfic.isEmpty())
                nomliste.append(opfic);
            nomliste.append(nomfichier);
        }
    }
    return nomliste;
}

bool DemarreObjet::ProcessusExistant()
{
    QProcess scruteur;
    QStringList phroptions;
    phroptions << "-C" << nomdulogiciel;
//    machin.setStandardOutputFile( "tititi.txt", QIODevice::Truncate );
    scruteur.start("ps", phroptions );
    scruteur.waitForFinished();
    QByteArray resultat = scruteur.readAllStandardOutput();
    scruteur.close();
//#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
//    QByteArrayView test(nomdulogiciel.toUtf8());
//    return resultat.indexOf(test)!=-1;
//#else
    return resultat.indexOf(nomdulogiciel.toUtf8())!=-1;
//#endif

}
bool DemarreObjet::LancerProcessus()
{
    bool reussi = false;
        phrasededemarreur = plogi->CheminProcess();
        phrasededemarreur.append(plogi->NomDuProcess());
    if(!phrasededemarreur.isEmpty())
    {
        QProcess lanceur;
        if(!plogi->ListeOptions().isEmpty())
        {
            phrasepouroptions = plogi->ListeOptions().split(',');
            plogi->PtrConfObjet()->lvarmsa.RemplacerCode(phrasepouroptions);
        }
        if(!nomfichiercfgobjet.isEmpty())
            phrasepouroptions << nomfichiercfgobjet;
        if(!nomfichiertrvobjet.isEmpty())
            phrasepouroptions << nomfichiertrvobjet;
//        if(phrasepouroptions.isEmpty())
//             reussi = lanceur.startDetached( phrasededemarreur );
//        else
//        {
             reussi = lanceur.startDetached( phrasededemarreur, phrasepouroptions );
//        }
        lanceur.waitForStarted(plogi->DelaiApresDemarrage()*2000);
//        Attendre(plogi->DelaiApresDemarrage());
    }
    phrasededemarreur.clear();
    nomfichiercfgobjet.clear();
    nomfichiertrvobjet.clear();
    phrasepouroptions.clear();
    return reussi;
}
void DemarreObjet::Attendre(int valeur)
{
    for(quint64 i=0;i<valeur*paquet;i++){}
}
bool DemarreObjet::DesProcessusSontDemarres()
{
    return !lstprocessus.isEmpty();
}
//bool DemarreObjet::UnProcessusType4Present()
//{
//    return !lstprocessusT4.isEmpty();
//}
//void DemarreObjet::RetirerLesT4DeLaListe()
//{
//    for(int i=0;i<lstprocessusT4.length();i++)
//        lstprocessus.removeOne(lstprocessusT4.at(i));
//}
void DemarreObjet::ArreterLesProcessus(  )
{
    if(!lstprocessus.isEmpty())
    {
        QStringList listeoptiondebase;
        listeoptiondebase << "-I" << "-u" << psession->NomUtilisateur();
        phrasededemarreur = "killall";
        QProcess tueur;
        for(int i=0;i<lstprocessus.length();i++)
        {
            phrasepouroptions = listeoptiondebase;
            phrasepouroptions.append(lstprocessus.at(i));
            tueur.start(phrasededemarreur,phrasepouroptions);
            tueur.waitForFinished();
            tueur.close();
//            lstprocessusT4.removeAll(lstprocessus.at(i));
        }
        lstprocessus.clear();
    }
}
