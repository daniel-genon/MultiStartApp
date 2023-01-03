#include "fblocdimfen.h"

FBlocDimFen::FBlocDimFen()
{
    nomtype         = 1734633061;//gdfe #67646665
    balisedimfen    = 1684629093;//dife #64696665
}
void FBlocDimFen::CreerNomFichier()
{
    NomDuFichier.append("donfen.gla");
}
bool FBlocDimFen::EcrireValeur(const QRect *valeur)
{
    enrgfen.posx = valeur->x();
    enrgfen.posy = valeur->y();
    enrgfen.largeur = valeur->width();
    enrgfen.hauteur = valeur->height();
    return EcrireDimFen();
}
void FBlocDimFen::EcrirePreBalise()
{
    OuvrirBalise(balisedimfen, sizeof(enrgfen)+8);
}
void FBlocDimFen::EcrireLesBlocs()
{
    valeurtaille    = sizeof(enrgfen);
    OuvrirEnrg();
    InitBlocParticulier((char *)&enrgfen);
    EcrireBlocParticulier();
}
bool FBlocDimFen::LireDimFen()
{
    bool oktrouver=false;
    nomliste = 0;
    if(PointerDebutListe())
    {
        nomliste = balisedimfen;
        InitBlocParticulier((char *)&enrgfen);
        if(LireListe())
        {
            if(LireEnrg())
            {
                 oktrouver = LireBlocParticulier();
            }
        }
        FermerFichierContinu();
    }
    return oktrouver;
}
void FBlocDimFen::LireValeur(QRect &valeur)
{
    valeur.setRect(enrgfen.posx,enrgfen.posy, enrgfen.largeur, enrgfen.hauteur);
}
bool FBlocDimFen::EcrireDimFen()
{
/*
balise = dife;
taille;
(
    balise = enrg;
    taille enrg;
       structure BlocDimFen
)
dev futur etc....
*/
    return Ecrire( true );
}
void FBlocDimFen::ViderEnrg()
{
    memset(&enrgfen,0,sizeof(enrgfen));
}
