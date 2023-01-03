#ifndef FBLOCPROJETMAPP_H
#define FBLOCPROJETMAPP_H

#include "ficbinbloc.h"
#include "../structuredemarreur.h"
#include "fbloccontexte.h"

struct BlocProjet{
    qint8        nom[80];
    EnrgDate    dcrea;
    qint8        commentaire[128];
};

/*
bloc liste projet "proj" :
(
    balise = proj;
    tailleliste;
    (
        balise = enrg;
        taille enrg;
           structure BlocOeuvre

        autre enrg

    )
)
*/



class FBlocProjetMApp : public ficbinDGBLOC
{
public:

    FBlocContexte   fichiercontexte;
    BlocProjet      enrgB;

    FBlocProjetMApp();

    void EntrerPointeur( EnrgSessionProjet *pvaleur );
    void Lister( QStringList &lstvaleur );
    bool EcrireProjet();
    bool LireProjet( const QString &valeur, bool evaluertoutenrg=true);
    bool LirePremierProjet();

    bool LirePremierContexte();
    bool LireContexte( const QString &valeur );
    bool EcrireContexte();
    bool ListerContexte( QStringList &lstvaleur );

    virtual bool Initialiser( QString *cheminracine );

    QString *CheminDuProjet();

protected:

    bool PointerProjet();

    virtual void CreerNomFichier();
    virtual void EcrirePreBalise();
    virtual void EcrireLesBlocs();

private:

    quint32 baliseprojet;
    QString *pChRacineMApp;
    QString cheminduprojet;

    void CreerCheminDeCeProjet();
    void Collationner();
    quint32 CalculTailleEnrg();
    void ViderEnrg();
    void ValiderValeurBloc();


};

#endif // FBLOCPROJETMAPP_H
