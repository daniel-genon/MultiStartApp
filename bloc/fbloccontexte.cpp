#include "fbloccontexte.h"

FBlocContexte::FBlocContexte()
{
    nomtype             = 1868655981;//mmao #6D6D616F
    balisecontexte      = 1953394531;//cont #636F6E74
}

void FBlocContexte::CreerNomFichier()
{
    NomDuFichier.append(penrg->projet.nom);
    NomDuFichier.append(".gla");
}

bool FBlocContexte::Initialiser( QString *cheminracine )
{
    pChRacineProjet = cheminracine;
    return ficbinDGBLOC::Initialiser( pChRacineProjet );
}

bool FBlocContexte::Lister( QStringList &lstvaleur )
{
    if(noerreur==0)
    {
        nomliste = 0;
        if(PointerDebutListe())
        {
            nomliste    = balisecontexte;
            BlocContexte  enrgtmp;
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
    return !lstvaleur.isEmpty();
}

bool FBlocContexte::ModifierContexte()
{
//    if(!PointerObjet()) return false;
    return Modifier();
}
bool FBlocContexte::EcrireContexte()
{
/*
ENTETE

    balise = cont;
    tailleliste;

        balise = enrg;
        taille enrg;
           structure BlocContexte

        balise = enrg;
        taille enrg;
           structure BlocContexte

        autre enrg
        .......
)
*/
    return Ecrire();
}

bool FBlocContexte::LireContexte( const QString &valeur )
{
    phrtest = valeur;
    if(!PointerObjet()) return false;
    Collationner();
    FermerFichierContinu();
    return true;
}

QString *FBlocContexte::CheminDuContexte()
{
    CreerCheminDeCeContexte();
    return &cheminducontexte;
}

bool FBlocContexte::LirePremierContexte()
{
    bool oktrouver=false;
    nomliste = 0;
    if(PointerDebutListe())
    {
        nomliste    = balisecontexte;
        InitBlocParticulier((char *)&enrgB);
        if(LireListe())
        {
            if(LireEnrg())
            {
                if(LireBlocParticulier())
                {
                    Collationner();
                    oktrouver=true;
                }
            }
        }
        FermerFichierContinu();
    }
    return oktrouver;
}

void FBlocContexte::Collationner()
{
    penrg->nom = QString((QChar *)&enrgB.nom);
    penrg->dcreation = enrgB.dcrea;
    penrg->dmodifcontexte = enrgB.dmodi;
    penrg->commentcontxt = QString((QChar *)&enrgB.commentaire);
}

void FBlocContexte::CreerCheminDeCeContexte()
{
    cheminducontexte.clear();
    cheminducontexte.append(*pChRacineProjet);
    cheminducontexte.append(penrg->nom);
    cheminducontexte.append("/");
}

quint32 FBlocContexte::CalculTailleEnrg()
{
    quint32 tailleenrg = sizeof(enrgB);
    return tailleenrg;
}
void FBlocContexte::ViderEnrg()
{
    memset(&enrgB,0,sizeof(enrgB));
}
void FBlocContexte::ValiderValeurBloc()
{
    ViderEnrg();
    TransQstrVersStr( penrg->nom, &enrgB.nom );
    TransQstrVersStr( penrg->commentcontxt, &enrgB.commentaire );
    enrgB.dcrea = penrg->dcreation;
    enrgB.dmodi = penrg->dmodifcontexte;
}
void FBlocContexte::EcrirePreBalise()
{
    OuvrirBalise(balisecontexte, CalculTailleEnrg()+8);
}
void FBlocContexte::EcrireLesBlocs()
{
    ValiderValeurBloc();
    valeurtaille    = sizeof(enrgB);
    OuvrirEnrg();
    InitBlocParticulier((char *)&enrgB);
    EcrireBlocParticulier();
}

bool FBlocContexte::PointerObjet()
{
    if(noerreur!=0) return false;
    nomliste = 0;
    if(PointerDebutListe())
    {
        nomliste = balisecontexte;
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
                    {
                        return true;
                    }
                }
                oktourner = PointerProchainNomListe();
            }
        }
        FermerFichierContinu();
    }
    return false;
}
