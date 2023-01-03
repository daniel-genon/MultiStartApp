#ifndef FBLOCSESSIONMULTIAPP_H
#define FBLOCSESSIONMULTIAPP_H

#include "ficbinbloc.h"
#include "../structuredemarreur.h"
/*
bloc LIST
taille liste
(
    bloc sess;
    taille bloc;
    (
        (
            balise = enrg;
            taille enrg;
            structure BlocSession
        )
        (
            ultérieurement autres valeurs
        )
    )
    etc... autre session // applications futures
)
*/

struct BlocSession{
    qint8        utilisateur[80];
    qint8        projet[80];
    qint8        contexte[80];
    EnrgDate     dmodi;
    qint8        configuration[80];
};


class FBlocSessionMultiApp : public ficbinDGBLOC
{
public:
    BlocSession enrgB;

    FBlocSessionMultiApp();

    bool EcrireSession();
    bool LireSession();

    void EntrerPointeur(EnrgSessionProjet *pvaleur );

protected:
    virtual void CreerNomFichier();
    virtual void EcrirePreBalise();
    virtual void EcrireLesBlocs();

private:
    EnrgSessionProjet *ptrenrgsespro;
    quint32 balisesession;

    void ViderEnrg();
    void ValiderValeurBloc();

};

#endif // FBLOCSESSIONMULTIAPP_H
