#include "gerersession.h"
#include <QDir>
#include <QDate>
#include "dialogue/creerunprojet.h"
#include "dialogue/chargeruncontexte.h"

GererSession::GererSession()
{
    noerreur        = 0;
    Enrsesproj.utilisateur = QProcessEnvironment::systemEnvironment().value("USER","INCONNU");
    VerifierRepertoire();
    ChargerSession();
}

// Zone des routines publiques

bool GererSession::oksession()
{// erreur 999 = sortie annuler de boite de dialogue
    return (noerreur==0||noerreur==999);
}
bool GererSession::okboite()
{// erreur 999 = sortie annuler de boite de dialogue
    return noerreur==999;
}

int GererSession::ChargerPremierProjetEtContexte()
{
    if(!fichierprojet.okfichier()) return 1;
    if(!fichierprojet.LirePremierProjet()) return 998;
    if(!fichierprojet.LirePremierContexte()) return 997;
    return 0;
}

void GererSession::Enregistrer()
{
    QDate tmpdate(QDate::currentDate());
    tmpdate.getDate(&Enrsesproj.dmodifsession.a,&Enrsesproj.dmodifsession.m,&Enrsesproj.dmodifsession.j);
    fichiersession.EcrireSession();
}

QString GererSession::CheminRacine() const
{
    return cheminracine;
}

QString *GererSession::ptrCheminRacine()
{
    return &cheminracine;
}

QString GererSession::CheminStandard() const
{
    QString phr = CheminRacine();
    phr.append( "fichierstandard/" );
    return phr;
}

QString GererSession::CheminProjet() const
{
    QString phr = CheminRacine();
    phr.append( NomDuProjet() );
    phr.append("/");
    return phr;
}
QString GererSession::CheminContexte() const
{
    QString phr = CheminProjet();
    phr.append( NomDuContexte() );
    phr.append("/");
    return phr;
}

QString GererSession::NomDuProjet() const
{
    return Enrsesproj.projet.nom;
}
QString GererSession::NomDuContexte() const
{
    return Enrsesproj.nom;
}
QString GererSession::NomUtilisateur() const
{
    return Enrsesproj.utilisateur;
}

QString GererSession::NomConfiguration() const
{
    return Enrsesproj.configuration;
}

void GererSession::ChangerConfiguration( const QString &valeur )
{
    Enrsesproj.configuration = valeur;
}

void GererSession::OuvrirUnContexte()
{
    noerreur=0;
    ChargerUnContexte *dlg = new ChargerUnContexte;
    dlg->setModal(true);
    dlg->IniBoite( &fichierprojet );
    if((dlg->exec()==QDialog::Accepted))
        noerreur=0;
    else
        noerreur=999;
    delete dlg;
}

void GererSession::CreerNouveauProjet()
{
//    CreerCheminParDefaut();
    QStringList lstprojet;
    fichierprojet.Lister( lstprojet );
    CreerUnProjet *dlg = new CreerUnProjet;
    dlg->setModal(true);
    dlg->IniBoite( &lstprojet, &Enrsesproj );
    if(dlg->exec()==QDialog::Accepted)
    {
        noerreur = 0;
        dlg->Collationner();
        CreerEnvironnementProjet();
        fichierprojet.EcrireProjet();
        CreerNouveauContexte();
        Enregistrer();
    }
    else
    {
        noerreur=998;
    }

    delete dlg;
}

void GererSession::CreerNouveauContexte()
{
    CreerUnContexte *dlg = new CreerUnContexte;
    dlg->setModal(true);
    dlg->IniBoite( &fichierprojet );
    if(dlg->exec()==QDialog::Accepted)
    {
        noerreur=0;
        dlg->Collationner();
        fichierprojet.EcrireContexte();
        QDir gestionrepertoire;
        phrtmp = CheminContexte();
//        phrtmp.append( fichierprojet.fichiercontexte.CheminDuContexte());
        gestionrepertoire.mkpath( phrtmp );
    }
    else
            noerreur=997;
    delete dlg;
}

// Zone des routines internes

bool GererSession::ChargerSession()
{
        noerreur=0;
    fichiersession.EntrerPointeur( &Enrsesproj );
    fichierprojet.EntrerPointeur( &Enrsesproj );
    fichierprojet.Initialiser(&cheminracine);
    if(fichiersession.Initialiser(&cheminracine)&&(fichiersession.LireSession()))
    {
        if(fichierprojet.LireProjet(Enrsesproj.projet.nom))
        {
            if(fichierprojet.LireContexte(Enrsesproj.nom))
                return true;
            else
            {
                if(fichierprojet.LirePremierContexte())
                    return true;
                else
                    CreerNouveauContexte();
            }
        }
        else
        {
            QStringList lstprojet;
            fichierprojet.Lister(lstprojet);
            if(lstprojet.isEmpty())
                CreerNouveauProjet();
            else
            {
                for(int i=0;i<lstprojet.length();i++)
                {
                    fichierprojet.LireProjet(lstprojet.at(i));
                    if(fichierprojet.LirePremierContexte())
                        return true;
                }
                fichierprojet.LireProjet(lstprojet.first());
                CreerNouveauContexte();
            }
        }
    }
    else
    {//problème de fichier session : créer une nouvelle session
        noerreur = ChargerPremierProjetEtContexte();
        switch(noerreur)
        {
        case 998 : CreerNouveauProjet();break;
        case 997 : CreerNouveauContexte();break;
        case   1 : CreerNouveauProjet();break;
        }
    }
    return (noerreur==0);
}

void GererSession::DetruireProjet()
{

}

void GererSession::CreerEnvironnementProjet()
{
    QDir gestionrepertoire;
    QString phrtmpcfg(CheminProjet());
    if(gestionrepertoire.exists(phrtmpcfg))
        DetruireProjet();

    CreerRepertoire();// vérifier l'existence des répertoires ou les créer suivant projetencours
    gestionrepertoire.mkpath(phrtmpcfg);// créer répertoire du nouveau projet
}

FBlocContexte *GererSession::pFichierContexte()
{
    return &fichierprojet.fichiercontexte;
}

//QRect *GererSession::LireDimFenetre()
//{
//    return fichierprojet.fichiercontexte.LireDimFenetre();
//}
//void GererSession::EcrireDimFenetre(const QRect &valeur)
//{
//    fichierprojet.fichiercontexte.EcrireDimFenetre(valeur);
//}
QString GererSession::LibelleErreur() const
{
    QString phrmessage;
    switch(noerreur)
    {
    case 0: phrmessage.append("aucune erreur");break;
    case 1: phrmessage.append("Le projet ou le contexte n'est pas créé");break;
    case 2: phrmessage.append("Il n'y a aucun projet ou contexte sauvegardé.");break;


    case 997: phrmessage.append("Le contexte n'est pas créé.");break;
    case 998: phrmessage.append("Le projet n'est pas créée.");break;
    case 999: phrmessage.append("Sortie abandon de boite");break;// ne pas afficher
    default : phrmessage.append("erreur non répertoriée");
    }
    return phrmessage;
}

void GererSession::CreerRepertoire()
{
    QDir gestionrepertoire;
    gestionrepertoire.mkpath(cheminracine);
    QString phtmp (cheminracine);
    phtmp.append("fichierstandard/");
    gestionrepertoire.mkpath(phtmp);
}

void GererSession::CreerCheminParDefaut()
{
}

void GererSession::VerifierRepertoire()
{
    QDir gestionrepertoire;
    cheminhome = QProcessEnvironment::systemEnvironment().value("HOME",gestionrepertoire.currentPath());
    cheminhome.append("/");
    cheminracine = cheminhome;
    cheminracine.append("MultiApp/");
    CreerCheminParDefaut();
    if(!gestionrepertoire.exists(cheminracine))
    {
        CreerRepertoire();
    }
}

void GererSession::SauverEnrgProjet(){ SVDEnrsesproj = Enrsesproj; }
void GererSession::RestaurerEnrgProjet(){ Enrsesproj = SVDEnrsesproj; }
void GererSession::ReserverEnrgProjet(){ RESEnrsesproj = Enrsesproj; }
void GererSession::RetablirEnrgProjet(){ Enrsesproj = RESEnrsesproj; }
