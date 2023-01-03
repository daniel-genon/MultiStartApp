#ifndef FBLOCCONTEXTE_H
#define FBLOCCONTEXTE_H

#include "ficbinbloc.h"
#include "../structuredemarreur.h"
#include <QRect>

struct BlocContexte{
    qint8       nom[80];
    EnrgDate    dcrea;
    EnrgDate    dmodi;
    qint8       commentaire[128];
};

/*
bloc liste contexte "cont" :
(
    balise = cont;
    tailleliste;
    (
        balise = enrg;
        taille enrg;
           structure BlocContexte

        balise = enrg;
        taille enrg;
           structure BlocContexte

        autre enrg
        .......
    )
)
*/

class FBlocContexte : public ficbinDGBLOC
{
public:

    EnrgSessionProjet   *penrg;
    BlocContexte        enrgB;

    FBlocContexte();

    QString *CheminDuContexte();
    bool EcrireContexte();
    bool ModifierContexte();
    bool LireContexte( const QString &valeur );
    bool LirePremierContexte();
    bool Lister( QStringList &lstvaleur );

    virtual bool Initialiser( QString *cheminracine );

protected:
    virtual bool PointerObjet();
    virtual void CreerNomFichier();
    virtual void EcrirePreBalise();
    virtual void EcrireLesBlocs();

private:

    quint32     balisecontexte;
    QString     *pChRacineProjet;
    QString     cheminducontexte;

    void Collationner();
    void CreerCheminDeCeContexte();
    quint32 CalculTailleEnrg();
    void ViderEnrg();
    void ValiderValeurBloc();

};

#endif // FBLOCCONTEXTE_H
