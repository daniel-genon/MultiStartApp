#include "fblocobjetcontexte.h"

FBlocObjetContexte::FBlocObjetContexte()
{
    nomtype         = 2020500335; //ocnx #6F636E78
    baliseobjet     = 1701470831; //obje #6F626A65
    baliseliaison   = 1767991660; //liai #6C696169
}

void FBlocObjetContexte::EntrerContexte(const QString &nomcontexte ){    nomducontexte   = nomcontexte;}
void FBlocObjetContexte::CreerNomFichier()
{
    if(nomducontexte.isEmpty())
        nomducontexte = "objetducontexte";

    NomDuFichier.append(nomducontexte);
    NomDuFichier.append(".gla");

}
EnrgObjetCtx *FBlocObjetContexte::PtrEnrg(){    return &objctxtmp;}
void FBlocObjetContexte::EcrireObjetContexte()
{
    /*
    bloc : BLOC
        taille;
        ocnx
        ???? nom config [160] octets
    bloc : LIST
        tailleliste;
        (
            ("obje";
             taille
                balise = "enrg";
                taille enrg;
                    structure BlocObjet
                    ???autre data
                 balise = "enrg";
                taille enrg;
                    structure BlocObjet
                    ???autre data
            etc...
            )
            ("liai";
             taille
                balise = "enrg";
                taille enrg;
                    structure BlocObjet
                autre data
                balise = "enrg";
                taille enrg;
                    structure BlocObjet
                autre data
            etc...
            )
        )
    )
    */
    //    quint32 tailleobjet   = lstobjetsmusicaux.length()*(sizeof(enrgB)+tailleblocdata);
    //    quint32 tailleliaison = lstliaisonmusicale.length()*(sizeof(enrgB)+tailleblocdata);
    //    qint64 dimfichier = TailleFichier();
    valeurtaille = 0;
    EcrireEntete();
    InitBlocParticulier((char *)&enrgB);
    quint32 tailledata = CalculTailleEnrg();

    OuvrirListe();
    valeurtaille = (tailledata*lstobjetsCtx.length())+8;
    nombalise = baliseobjet;
    OuvrirBalise();
    valeurtaille = tailledata;
    for( int i=0;i<lstobjetsCtx.length();i++)
    {
        objctxtmp = lstobjetsCtx.at(i);
            ValiderValeurBloc();
        OuvrirEnrg();
        EcrireBlocParticulier();
    }
    valeurtaille = (tailledata*lstliaisonCtx.length())+16;
    nombalise = baliseliaison;
    OuvrirBalise();
    valeurtaille = tailledata;
    for( int i=0;i<lstliaisonCtx.length();i++)
    {
        objctxtmp = lstliaisonCtx.at(i);
            ValiderValeurBloc();
        OuvrirEnrg();
        EcrireBlocParticulier();
    }

    FermerFichierOuvert();
}
bool FBlocObjetContexte::LireObjetContexte()
{
    lstobjetsCtx.clear();
    lstliaisonCtx.clear();
    if(noerreur==0)
    {
        bool oktourner;
        nomliste = 0;
        if(PointerDebutListe())
        {
            nomliste = baliseobjet;
            if(LireListe())
            {
                oktourner = true;
                InitBlocParticulier((char *)&enrgB);
                while(LireEnrg() && oktourner)
                {
                    oktourner=false;
                    if(LireBlocParticulier())
                    {
                        Collationner();
                        AjouterObjet();
                    }
                    oktourner = PointerProchainEnrg();
                }
                RetourPointageDeBloc();
            }
            nomliste = baliseliaison;
            if(LireListe())
            {
                oktourner = true;
                InitBlocParticulier((char *)&enrgB);
                while(LireEnrg() && oktourner)
                {
                    oktourner=false;
                    if(LireBlocParticulier())
                    {
                        Collationner();
                        AjouterLiaison();
                    }
                    oktourner = PointerProchainEnrg();
                }
            }
        }
        FermerFichierContinu();
    }
    return !lstobjetsCtx.isEmpty();

}
bool FBlocObjetContexte::LireElement( int rang )
{
    if(rang >= lstobjetsCtx.length()) return false;
    objctxtmp = lstobjetsCtx.at(rang);
    return true;
}
bool FBlocObjetContexte::lireLiaison( int rang )
{
    if(rang >= lstliaisonCtx.length()) return false;
    objctxtmp = lstliaisonCtx.at(rang);
    return true;
}
quint32 FBlocObjetContexte::CalculTailleEnrg()
{
    quint32 tailleenrg = sizeof(enrgB);
    return tailleenrg;
}
void  FBlocObjetContexte::ViderEnrg(){    memset(&enrgB,0,sizeof(enrgB));}
void  FBlocObjetContexte::ValiderValeurBloc()
{
    ViderEnrg();
    enrgB.posX      = objctxtmp.X();
    enrgB.posY      = objctxtmp.Y();
    enrgB.posXcfg   = objctxtmp.XConfig();
    enrgB.posYcfg   = objctxtmp.YConfig();
    enrgB.posXtrv   = objctxtmp.XTravail();
    enrgB.posYtrv   = objctxtmp.YTravail();
    enrgB.priorite  = objctxtmp.Priorite();
    TransQstrVersStr( objctxtmp.Nom(), &enrgB.nomclair );
    TransQstrVersStr( objctxtmp.NomTravail(), &enrgB.fictrv );
    TransQstrVersStr( objctxtmp.NomConfig() , &enrgB.ficcfg );
}
void  FBlocObjetContexte::Collationner()
{
    objctxtmp.ValeurObjet( QString((QChar *)&enrgB.nomclair), enrgB.posX, enrgB.posY );
    objctxtmp.Travail( QString((QChar *)&enrgB.fictrv), enrgB.posXtrv, enrgB.posYtrv );
    objctxtmp.Config( QString((QChar *)&enrgB.ficcfg), enrgB.posXcfg, enrgB.posYcfg );
    objctxtmp.X( enrgB.posX );
    objctxtmp.Y( enrgB.posY );
    objctxtmp.XConfig( enrgB.posXcfg );
    objctxtmp.YConfig( enrgB.posYcfg );
    objctxtmp.XTravail( enrgB.posXtrv );
    objctxtmp.YTravail( enrgB.posYtrv );
    objctxtmp.Priorite( enrgB.priorite );
}
void  FBlocObjetContexte::AjouterObjet(){    lstobjetsCtx.append( objctxtmp );}
void  FBlocObjetContexte::AjouterLiaison(){    lstliaisonCtx.append(objctxtmp);}
