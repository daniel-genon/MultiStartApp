#ifndef FBLOCDIMFEN_H
#define FBLOCDIMFEN_H

#include <QRect>
#include "ficbinbloc.h"
#include "../structuredemarreur.h"

/*
bloc liste projet "gdfe" :
(
    balise = dife;
    tailleliste;
    (
        balise = enrg;
        taille enrg;
           structure BlocDimFen

        dev futur : autre enrg

    )
)
*/

class FBlocDimFen : public ficbinDGBLOC
{
public:
    FBlocDimFen();
    bool LireDimFen();
    void LireValeur(QRect &valeur);
    bool EcrireValeur(const QRect *valeur);

protected:
    virtual void CreerNomFichier();
    virtual void EcrirePreBalise();
    virtual void EcrireLesBlocs();

private :
    quint32     balisedimfen;
    BlocDimFen  enrgfen;
    QRect       valeurdimfen;

    void ViderEnrg();
    bool EcrireDimFen();
};

#endif // FBLOCDIMFEN_H
