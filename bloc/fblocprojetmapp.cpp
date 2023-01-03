#include "fblocprojetmapp.h"

FBlocProjetMApp::FBlocProjetMApp()
{
    nomtype         = 1886216560;//pmap #706D6170
    baliseprojet    = 1785688688;//proj #70726f6a
}

void FBlocProjetMApp::CreerNomFichier()
{
    NomDuFichier.append("projet.gla");
}

bool FBlocProjetMApp::Initialiser( QString *cheminracine )
{
    pChRacineMApp = cheminracine;
    return ficbinDGBLOC::Initialiser( pChRacineMApp );
}

void FBlocProjetMApp::EntrerPointeur(EnrgSessionProjet *pvaleur )
{
    fichiercontexte.penrg = pvaleur;
}
QString *FBlocProjetMApp::CheminDuProjet()
{
    CreerCheminDeCeProjet();
    return &cheminduprojet;
}

void FBlocProjetMApp::Lister( QStringList &lstvaleur )
{
    if(noerreur==0)
    {
        nomliste = 0;
        if(PointerDebutListe())
        {
            nomliste = baliseprojet;
            BlocProjet  enrgtmp;
            bool oktourner = true;
            InitBlocParticulier((char *)&enrgtmp);
            while(LireListe() && oktourner)
            {
                oktourner = false;
                if(LireEnrg())
                {
                    if(LireBlocParticulier())
                        lstvaleur.append(QString((QChar *)enrgtmp.nom));
                    oktourner = PointerProchainNomListe();
                }
            }
            FermerFichierContinu();
        }
    }
}

bool FBlocProjetMApp::EcrireProjet()
{
/*
balise = proj;
taille;
(
    balise = enrg;
    taille enrg;
       structure BlocProjet
)
balise = proj
taille
(
    balise = enrg;
    taille enrg;
    etc.....
)
etc....
*/
    return Ecrire();
}

void FBlocProjetMApp::Collationner()
{
    fichiercontexte.penrg->projet.nom = QString((QChar *)&enrgB.nom);
    fichiercontexte.penrg->projet.dcreation = enrgB.dcrea;
    fichiercontexte.penrg->projet.commentaire = QString((QChar *)&enrgB.commentaire);
}

bool FBlocProjetMApp::LireProjet( const QString &valeur, bool evaluertoutenrg )
{
    if(noerreur!=0) return false;
    phrtest = valeur;
    if(!PointerProjet()) return false;
    Collationner();
        if(evaluertoutenrg)
        {
//            posoctetadebutfic += tailleblocdata;
//            posoctetadebutfic += sizeof(enrgB);
//            if(PointerOctetCible())
//                LireLaSuite();
        }
    FermerFichierContinu();
    return true;
}

bool FBlocProjetMApp::ListerContexte( QStringList &lstvaleur )
{
    CreerCheminDeCeProjet();
    fichiercontexte.Initialiser( &cheminduprojet );
    return fichiercontexte.Lister( lstvaleur );
}

bool FBlocProjetMApp::PointerProjet()
{
    if(noerreur!=0) return false;
    nomliste = 0;
    if(PointerDebutListe())
    {
        nomliste = baliseprojet;
        bool oktourner = true;
        InitBlocParticulier((char *)&enrgB);
        while(LireListe() && oktourner)
        {
            oktourner = false;
            if(LireEnrg())
            {
                if(LireBlocParticulier())
                {
                    if(phrtest==QString((QChar *)&enrgB.nom))
                        return true;
                }
                oktourner = PointerProchainNomListe();
            }
        }
        FermerFichierContinu();
    }
    return false;
}

bool FBlocProjetMApp::LirePremierProjet()
{
    bool oktrouver=false;
    nomliste = 0;
    if(PointerDebutListe())
    {
        nomliste = baliseprojet;
        InitBlocParticulier((char *)&enrgB);
        if(LireListe())
        {
            if(LireEnrg())
            {
                if(LireBlocParticulier())
                {
                    oktrouver=true;
                    Collationner();
//                    posoctetadebutfic += tailleblocdata;
//                    posoctetadebutfic += sizeof(enrgB);
//                    if(PointerOctetCible())
//                        LireLaSuite();
                }
            }
        }
        FermerFichierContinu();
    }
    return oktrouver;
}

bool FBlocProjetMApp::LirePremierContexte()
{
    CreerCheminDeCeProjet();
    if(!fichiercontexte.Initialiser( &cheminduprojet )) return false;
    return fichiercontexte.LirePremierContexte();
}

bool FBlocProjetMApp::LireContexte( const QString &valeur )
{
    CreerCheminDeCeProjet();
    if(!fichiercontexte.Initialiser( &cheminduprojet )) return false;
    return fichiercontexte.LireContexte(valeur);
}

bool FBlocProjetMApp::EcrireContexte()
{
    CreerCheminDeCeProjet();
    fichiercontexte.Initialiser( &cheminduprojet );
    return fichiercontexte.EcrireContexte();
}

quint32 FBlocProjetMApp::CalculTailleEnrg()
{
    quint32 tailleenrg = sizeof(enrgB);
    return tailleenrg;
}

void FBlocProjetMApp::EcrirePreBalise()
{
    OuvrirBalise(baliseprojet, CalculTailleEnrg()+8);
}

void FBlocProjetMApp::EcrireLesBlocs()
{
    ValiderValeurBloc();
    valeurtaille = sizeof(enrgB);
    OuvrirEnrg();
    InitBlocParticulier((char *)&enrgB);
    EcrireBlocParticulier();
//    nombalise = balisechemin;
//    for(int i=0;i<fichiermorceau.penrg->oeuvre.Chconfig.length();i++)
//        EcrireData(fichiermorceau.penrg->oeuvre.Chconfig.at(i));
}

void FBlocProjetMApp::ViderEnrg()
{
    memset(&enrgB,0,sizeof(enrgB));
}

void FBlocProjetMApp::ValiderValeurBloc()
{
    ViderEnrg();
    TransQstrVersStr( fichiercontexte.penrg->projet.nom, &enrgB.nom );
    TransQstrVersStr( fichiercontexte.penrg->projet.commentaire, &enrgB.commentaire );
    enrgB.dcrea = fichiercontexte.penrg->dcreation;
}

void FBlocProjetMApp::CreerCheminDeCeProjet()
{
    cheminduprojet.clear();
    cheminduprojet.append(*pChRacineMApp);
    cheminduprojet.append(fichiercontexte.penrg->projet.nom);
    cheminduprojet.append("/");
}

