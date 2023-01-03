#ifndef FBLOCCONFIG_H
#define FBLOCCONFIG_H

#include "ficbinbloc.h"
#include "../structuredemarreur.h"
#include "../enrg/enrgconfig.h"
#include "../enrg/enrglogiciel.h"
#include "../enrg/enrggraph.h"
#include "../enrg/enrgconnexion.h"

//bloc : BLOC
//    taille;
//    cmao
//bloc : LIST
//    tailleliste;
//    (
//        ("conf";
//        balise = "gene";
//            taille enrg (taile de la structure+8)
//                structure BlocConfig (1 seul)

//        balise = "conn";
//            taille enrg (taile de la structure+8)
//                structure BlocConnexion; (1 seul)

//        balise "logi" ( logiciel : données pour les logiciels de la config )
//            taille enrg (taile de la structure: enrg*n+8 ) 0 ou n
//            balise "enrg"
//                taille enrg
//                Bloclogiciel 1
//            balise "enrg"
//                taille enrg
//                Bloclogiciel 2
//            etc...

//        balise "fami" (priorite : données pour les graphiques )
//            taille enrg (taile de la structure: enrg*n+8)
//            balise "enrg"
//                taille enrg
//                BlocGraph 1
//            balise "enrg"
//                taille enrg
//                BlocGraph 2
//        etc...

//        balise = "cfgf";
//            taille enrg (taille de la structure) 1 ou n
//                structure BlocGraphCFG 1
//        balise = "cfgf";
//            taille enrg (taille de la structure)
//                structure BlocGraphCFG 2
//        etc...
//        )
//    )
//)


class FBlocConfig : public ficbinDGBLOC
{
public:

    FBlocConfig();


    EnrgConfig      *penrg;
    LstEnrgLogiciel *plstlog;
    LstEnrgGrLog    *plstpri;
    EnrgConnexion   *pconnexion;
    LstEnrgGrFic    *plstfic;

    void CreerConfigurationStandard();
    bool ModifierConfig();
    void Lister( QStringList &lstvaleur );
    bool LireConfiguration( const QString &valeur );
    bool LirePremiereConfig();
    bool EcrireConfig();

    void InitPointeur(EnrgConfig *pv1, EnrgConnexion *ps2, LstEnrgLogiciel *pv2, LstEnrgGrLog *pv3, LstEnrgGrFic *pv4 );

    virtual bool Initialiser( QString *cheminracine );

protected:

    virtual void CreerNomFichier();
    virtual bool PointerObjet();
    virtual void EcrirePreBalise();
    virtual void EcrireLesBlocs();

private:

    QString *pChRacineConfig;

    quint64 differencedetaille;

    quint32 baliseconfig;
    quint32 balisepriorite;
    quint32 baliselogiciel;
    quint32 balisefichier;
    quint32 balisegeneral;
    quint32 baliseconnexion;

    BlocConfig      enrconfig;
    BlocLogiciel    enrlogiciel;
    BlocGraph       enrgraph;
    BlocConnexion   enrconnexion;

    void ViderEnrg();
    void NettoyerListeEnrg();

    bool LireValeurConfig();
    bool PointerConfig();

    quint32 CalculTailleConf();

};

#endif // FBLOCCONFIG_H
