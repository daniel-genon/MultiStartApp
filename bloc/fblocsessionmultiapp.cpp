#include "fblocsessionmultiapp.h"

FBlocSessionMultiApp::FBlocSessionMultiApp()
{
    nomtype             = 1885433191;//gmap #676D6170
    balisesession       = 1936942451;//sess #73657373
    tailledereference   = sizeof(enrgB);// provisoire
}

void FBlocSessionMultiApp::EntrerPointeur( EnrgSessionProjet *pvaleur )
{
    ptrenrgsespro = pvaleur;
}

void FBlocSessionMultiApp::EcrirePreBalise()
{
    OuvrirBalise(balisesession, sizeof(enrgB)+8);
}
void FBlocSessionMultiApp::EcrireLesBlocs()
{
    ValiderValeurBloc();
    valeurtaille    = sizeof(enrgB);
    OuvrirEnrg();
    InitBlocParticulier((char *)&enrgB);
    EcrireBlocParticulier();
}

bool FBlocSessionMultiApp::EcrireSession()
{
// enrB initialiser avant l'appel
/*
00 00 00 00 : BLOC
00 00 00 00 :   taille fichier - 8 = 180
00 00 00 00 : gmap
00 00 00 00 : enrg
00 00 00 00 :   taille bloc (172 octets)

80 octets   : utilisateur;
80 octets   : projet;

00 00 00 00 : jdatemodif;
00 00 00 00 : mdatemodif;
00 00 00 00 : adatemodif;
*/
    return Ecrire( true );
}

bool FBlocSessionMultiApp::LireSession()
{
    bool oktrouver=false;
    if(noerreur==0)
    {
        nomliste = balisesession;
        if(PointerDebutListe())
        {
            if(LireEnrg())
            {
                InitBlocParticulier((char *)&enrgB);
                if(LireBlocParticulier())
                {
                    oktrouver=true;
                    ptrenrgsespro->projet.nom = QString((QChar *)&enrgB.projet);
                    ptrenrgsespro->nom = QString((QChar *)&enrgB.contexte);
                    ptrenrgsespro->dmodifsession = enrgB.dmodi;
                    ptrenrgsespro->configuration = QString((QChar *)&enrgB.configuration);
                }
            }
        }
        FermerFichierContinu();
    }
    return oktrouver;
}

void FBlocSessionMultiApp::CreerNomFichier()
{
    NomDuFichier.append("dongen.gla");
}

void FBlocSessionMultiApp::ViderEnrg()
{
    memset(&enrgB,0,sizeof(enrgB));
}

void FBlocSessionMultiApp::ValiderValeurBloc()
{
    ViderEnrg();
    TransQstrVersStr( ptrenrgsespro->projet.nom, &enrgB.projet );
    TransQstrVersStr( ptrenrgsespro->nom, &enrgB.contexte );
    TransQstrVersStr( ptrenrgsespro->utilisateur, &enrgB.utilisateur );
    enrgB.dmodi = ptrenrgsespro->dmodifsession;
    TransQstrVersStr( ptrenrgsespro->configuration, &enrgB.configuration );
}
