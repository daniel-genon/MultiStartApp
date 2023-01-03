#include "fichiertravail.h"

FichierTravail::FichierTravail()
{
    cfgobjet = NULL;
    InitFicTrv();
}

FichierTravail::FichierTravail( ConfigurationObjet *ptrconf , const EnrgFichier &valeur )
{
    Entrer(valeur);
    cfgobjet = ptrconf;
    InitFicTrv();
}

void FichierTravail::InitFicTrv()
{
    GenreElement( 300 );
    NomElement("fichier travail");

    if(cfgobjet!=NULL)
    {
        if(cfgobjet->PointerTravail())
        {
            InitFichier();
            InitIcone(":/icone/fictrv.png");
        }
    }
}

void FichierTravail::CollationnerDescripteur( EnrgObjetCtx *retval )
{
    retval->Travail( NomFichier(false) , PositionXDansScene(), PositionYDansScene());
}
