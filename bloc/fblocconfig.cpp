#include "fblocconfig.h"

FBlocConfig::FBlocConfig()
{
    nomtype             = 1885433187;//cmap #636D6170
    baliseconfig        = 1718513507;//conf #636F6E66
    balisegeneral       = 1701733735;//gene #67656E65
    baliseconnexion     = 1852731235;//conn #636F6E6E
    balisepriorite      = 1768776038;//fami #66616D69
    baliselogiciel      = 1768386412;//logi #6C6F6769
    balisefichier       = 1768384099;//cfgf #63666766
}

bool FBlocConfig::Initialiser( QString *cheminracine )
{
    pChRacineConfig = cheminracine;
    return ficbinDGBLOC::Initialiser( pChRacineConfig );
}

void FBlocConfig::CreerNomFichier()
{
    NomDuFichier.append("cfgmultiapp.gla");
}

void FBlocConfig::InitPointeur(EnrgConfig *pv1, EnrgConnexion *ps2, LstEnrgLogiciel *pv2, LstEnrgGrLog *pv3, LstEnrgGrFic *pv4 )
{
    penrg       = pv1;
    plstlog     = pv2;
    plstpri     = pv3;
    pconnexion  = ps2;
    plstfic     = pv4;
}

void FBlocConfig::Lister( QStringList &lstvaleur )
{
    if(noerreur==0)
    {
        nomliste = 0;
        if(PointerDebutListe())
        {
            nomliste    = baliseconfig;
            bool oktourner = true;
            while(LireListe() && oktourner)
            {
                oktourner = false;
                if(LireEnrgBalise( balisegeneral, (char *)&enrconfig))
                    lstvaleur.append(QString((QChar *)enrconfig.nom));

                oktourner = PointerProchainNomListe();
            }
            FermerFichierContinu();
        }
    }
}

void FBlocConfig::CreerConfigurationStandard()
{
    EcrireConfig();
}

bool FBlocConfig::EcrireConfig()
{

//    ENTETE
//    ("conf";
//     taille (taille de tout le bloc "conf")

//        balise = "gene";
//            taille enrg (taile de la structure+8)
//                structure BlocConfig (1 seul)

//        balise = "conn";
//            taille enrg (taile de la structure+8)
//                structure BlocConnexion; (1 seul)

//        balise "logi" ( logiciel : données pour les logiciels de la config )
//            taille enrg (taille de la structure: enrg+8 )
//            Bloclogiciel 1
//        balise "logi"
//            taille enrg
//            Bloclogiciel 2
//        etc...

//        balise "fami" (priorite : données pour les graphiques )
//            taille enrg (taile de la structure: enrg+8)
//            BlocGraph 1
//        balise "fami"
//            taille enrg
//            BlocGraph 2
//        etc...

//        balise = "cfgf";
//            taille enrg (taille de la structure) 1 ou n
//                structure BlocGraph 1
//        balise = "cfgf";
//            taille enrg (taille de la structure)
//                structure BlocGraph 2
//        etc...

//    )

        ViderEnrg();
        return Ecrire();
}

void FBlocConfig::ViderEnrg()
{
    memset(&enrconfig,0,sizeof(enrconfig));
    memset(&enrgraph,0,sizeof(enrgraph));
    memset(&enrlogiciel,0,sizeof(enrlogiciel));
    memset(&enrconnexion,0,sizeof(enrconnexion));
}

void FBlocConfig::NettoyerListeEnrg()
{
    plstlog->clear();
    plstpri->clear();
    plstfic->clear();
}

bool FBlocConfig::LireConfiguration( const QString &valeur )
{
    bool oktrouver=false;
    phrtest = valeur;
    if(PointerObjet())
    {
        penrg->CopierDepuisBloc(enrconfig);
        oktrouver = LireValeurConfig();
        FermerFichierContinu();
    }
    return oktrouver;
}

bool FBlocConfig::LirePremiereConfig()
{
    bool oktrouver=false;
    nomliste = 0;
    if(PointerDebutListe())
    {
        nomliste = baliseconfig;
        if(LireListe())
        {
            if(LireEnrgBalise( balisegeneral, (char *)&enrconfig))
            {
                penrg->CopierDepuisBloc(enrconfig);
                oktrouver = LireValeurConfig();
            }
        }
        FermerFichierContinu();
    }
    return oktrouver;
}

bool FBlocConfig::ModifierConfig()
{
    phrtest = penrg->Nom();
    tailledereference = CalculTailleConf();
    return Modifier();
}
void FBlocConfig::EcrirePreBalise()
{
    OuvrirBalise(baliseconfig, CalculTailleConf());
}

void FBlocConfig::EcrireLesBlocs()
{
// écriture config générale
    penrg->CopierVersBloc(enrconfig);
    OuvrirEnrgBalise( balisegeneral, (char *)&enrconfig, sizeof(enrconfig) );
// écriture connexion
    pconnexion->CopierVersBloc(enrconnexion);
    OuvrirEnrgBalise( baliseconnexion, (char *)&enrconnexion, sizeof(enrconnexion) );
//    écriture logiciel
    OuvrirEnrgBalise( baliselogiciel, (char *)&enrlogiciel, sizeof(enrlogiciel), false );
    for(int i=0;i<plstlog->length();i++)
    {
        plstlog->at(i)->CopierVersBloc( enrlogiciel );
        EcrireEnrgBalise();
    }
// écriture priorite
    OuvrirEnrgBalise( balisepriorite, (char *)&enrgraph, sizeof(enrgraph), false );
    for(int i=0;i<plstpri->length();i++)
    {
//        bool ModifierConfig();
        plstpri->at(i)->CopierVersBloc(enrgraph);
        EcrireEnrgBalise();
    }
// écriture cfg-trav
    OuvrirEnrgBalise( balisefichier, (char *)&enrgraph, sizeof(enrgraph), false );
    for(int i=0;i<plstfic->length();i++)
    {
        plstfic->at(i)->CopierVersBloc(enrgraph);
        EcrireEnrgBalise();
    }
}
quint32 FBlocConfig::CalculTailleConf()
{
    quint32 tailleenrg = sizeof(enrconfig)+8+
            sizeof(enrconnexion)+8+
            ((sizeof(enrlogiciel)+8) * (plstlog->length()))+
            ((sizeof(enrgraph)+8) * (plstpri->length()))+
            ((sizeof(enrgraph)+8) * (plstfic->length()));
    return tailleenrg;
}
bool FBlocConfig::LireValeurConfig()
{
    NettoyerListeEnrg();
    if(LireEnrgBalise( baliseconnexion, (char *)&enrconnexion))
        pconnexion->CopierDepuisBloc(enrconnexion);
    else
        pconnexion->Standard();

    if(LireEnrgBalise( baliselogiciel, (char *)&enrlogiciel))
    {
        do{
            plstlog->Ajouter(enrlogiciel);
        }while(LireEnrgBalise());
        RetourPointageDeBloc();
    }
    if(LireEnrgBalise( balisepriorite, (char *)&enrgraph))
    {
        do{
            plstpri->Ajouter( enrgraph );
        }while(LireEnrgBalise());
        RetourPointageDeBloc();
    }
    if(LireEnrgBalise( balisefichier, (char *)&enrgraph))
    {
        do{
            plstfic->Ajouter( enrgraph );
        }while(LireEnrgBalise());
        RetourPointageDeBloc();
    }
            return true;
//        }
//    return false;
}

bool FBlocConfig::PointerObjet()
{
    if(noerreur!=0) return false;
    nomliste = 0;
    if(PointerDebutListe())
    {
        nomliste = baliseconfig;
        bool oktourner = true;
        while(LireListe() && oktourner)
        {
            oktourner = false;
            if(LireEnrgBalise( balisegeneral, (char *)&enrconfig) )
            {
                if(phrtest==QString((QChar *)&enrconfig.nom))
                        return true;
            }
            oktourner = PointerProchainNomListe();
        }
        FermerFichierContinu();
    }
    return false;
}
