#ifndef FBLOCOBJETCONTEXTE_H
#define FBLOCOBJETCONTEXTE_H

#include "ficbinbloc.h"
#include "../enrg/enrgobjetctx.h"

/*
bloc : BLOC
    taille;
    ocnx
    nom de la config (160 octet = 80 cars)
bloc : LIST
    tailleliste;
    (
    nom bloc "obje";
        taille
        (liste :
            balise = "enrg";
            taille enrg;
                structure BlocObjet
            balise = "enrg";
            taille enrg;
                structure BlocObjet

            autre enrg...
        )
    nom bloc "liai";
        taille
        (liste :
            balise = "enrg";
            taille enrg;
                structure BlocObjet
            balise = "enrg";
            taille enrg;
                structure BlocObjet
            autre enrg...
        )
    )
)
*/

struct BlocObjetCTX{
    qint8    nomclair[160];
    qint8    fictrv[160];
    qint8    ficcfg[160];
    qint32  posX;
    qint32  posY;
    qint32  posXcfg;
    qint32  posYcfg;
    qint32  posXtrv;
    qint32  posYtrv;
    quint8  priorite;
};

class FBlocObjetContexte : public ficbinDGBLOC
{
public:

    BlocObjetCTX enrgB;
    FBlocObjetContexte();
    EnrgObjetCtx *PtrEnrg();

    void EntrerContexte( const QString &nomcontexte );

    virtual void CreerNomFichier();

//    void AjouterObjetContexte();
    void EcrireObjetContexte();
    bool LireObjetContexte();

    bool LireElement( int rang );
    bool lireLiaison( int rang );
    void AjouterObjet();
    void AjouterLiaison();

private:

    quint32 baliseobjet;
    quint32 baliseliaison;

    EnrgObjetCtx    objctxtmp;
//    EnrgObjetCtx    *pobjctx;

    QList<EnrgObjetCtx> lstobjetsCtx;
    QList<EnrgObjetCtx> lstliaisonCtx;

    QString nomducontexte;

    quint32 CalculTailleEnrg();
    void  ViderEnrg();
    void  ValiderValeurBloc();
    void  Collationner();

};

#endif // FBLOCOBJETCONTEXTE_H
