#include "ficbinbloc.h"

ficbinDGBLOC::ficbinDGBLOC()
{
    nomriff         = 1129270338;//BLOC #424C4F43
    nombornelist    = 1414744396;//LIST
    nomenrg         = 1735552613;//enrg #656E7267
    nomtype         = 0;
    nombalise       = 0;
    noerreur        = 0;
    taillebaliselist    = sizeof(baliselist);
    tailleblocdata      = sizeof(blocdata);
    posoctetadebutfic   = 0;
    typecodec = 2;
    tailledereference = 0;
}
bool ficbinDGBLOC::Initialiser(QString *cheminracine )
{
    NomDuFichier.clear();
    NomDuFichier.append(*cheminracine);
    CreerNomFichier();
    return LireEntete()==0;
}
bool ficbinDGBLOC::Initialiser(const QString &cheminracine )
{
    QString phrtmp(cheminracine);
    return Initialiser( &phrtmp );
}
bool ficbinDGBLOC::okfichier(){    return noerreur==0;}
void ficbinDGBLOC::CreerNomFichier(){    NomDuFichier.append("dongen.gla");}
void ficbinDGBLOC::EcrireEntete()
{
    ReinitEnrg((char *)&entete,sizeof(entete));
    entete.typestructure    = nomriff;
    entete.taillefichier    = valeurtaille;
    entete.typefichier      = nomtype;
    OuvrirEnREcriture();
    EcrireEnContinu();
}
void ficbinDGBLOC::OuvrirListe()
{
    baliselist.balise = nombornelist;
    baliselist.taille = valeurtaille;
    InitEnrgListe();
    EcrireEnContinu();
}
void ficbinDGBLOC::OuvrirBalise()
{
    blocdata.balise = nombalise;
    blocdata.taille = valeurtaille;
    InitEnrgBloc();
    EcrireEnContinu();
}
void ficbinDGBLOC::OuvrirBalise( quint32 valeur, quint32 taille )
{
    nombalise = valeur;
    valeurtaille = taille;
    OuvrirBalise();
}
void ficbinDGBLOC::EcrireData( const QString &valeur )
{
    valeurtaille = (quint32)valeur.length()*typecodec;
    OuvrirBalise();
    ReinitEnrg((char *) valeur.data(),valeurtaille);
    EcrireEnContinu();
}
void ficbinDGBLOC::OuvrirEnrg()
{
    ReinitEnrg((char *)&blocenrg,tailleblocdata);
    blocenrg.balise = nomenrg;
    blocenrg.taille = valeurtaille;
    EcrireEnContinu();
}
bool ficbinDGBLOC::EcrireBlocParticulier()
{
    ReinitEnrg( adrenrgparticulier, blocenrg.taille );
    return EcrireEnContinu();
}
void ficbinDGBLOC::OuvrirEnrgBalise( quint32 nomdebalise, char *adrenrg, quint16 taille, bool ecrire )
{
    nombalise       = nomdebalise;
    valeurtaille    = taille;
    InitBlocParticulier ( adrenrg );
    if(ecrire) EcrireEnrgBalise();
}
bool ficbinDGBLOC::EcrireEnrgBalise()
{
    OuvrirBalise();
    ReinitEnrg( adrenrgparticulier, valeurtaille );
    return EcrireEnContinu();
}
bool ficbinDGBLOC::LireEnrgBalise( quint32 nomdebalise, char *adrenrg )
{
    nombalise           = nomdebalise;
    adrenrgparticulier  = adrenrg;
    return LireEnrgBalise();
}
bool ficbinDGBLOC::LireEnrgBalise()
{
    InitEnrgBloc();
    if(LireEnContinu())
    {
        if(blocdata.balise==nombalise)
        {
            if((tailledereference<blocdata.taille)&&(tailledereference!=0))
                ReinitEnrg( adrenrgparticulier, tailledereference );
            else
                ReinitEnrg( adrenrgparticulier, blocdata.taille );
            return LireEnContinu();
        }
    }
    return false;
}
int ficbinDGBLOC::LireEntete()
{
    if(Existe())
    {
        ReinitEnrg((char *)&entete,sizeof(entete));
        if(Lire()==0)
        {
            if(entete.typestructure==nomriff && entete.typefichier==nomtype)
                noerreur=0;
            else
                noerreur=3;// n'est pas fichier bloc souhaité
        }
        else
            noerreur=2;// problème de lecture
    }
    else
        noerreur=1;// fichier inconnu

    return noerreur;
}
bool ficbinDGBLOC::LireDataChaine()
{
    if(LireBloc())
    {
        if(PointerOctetCible())
        {
            InitTamponChaine();
            if(LireEnContinu())
            {
                posoctetadebutfic += blocdata.taille;
                return true;
            }
        }
    }
    return false;
}
QString ficbinDGBLOC::ValeurChaine() const {    return QString((QChar *)&tamponchaine);}
void ficbinDGBLOC::RecupererChaine( QString &cible, qint8 *psource ){    cible = QString((QChar *)psource);}
void ficbinDGBLOC::InitBlocParticulier ( char *adrenrg ){    adrenrgparticulier  = adrenrg;}
bool ficbinDGBLOC::LireBlocParticulier ()
{
        if((tailledereference<blocenrg.taille)&&(tailledereference!=0))
            ReinitEnrg( adrenrgparticulier, tailledereference );
        else
            ReinitEnrg( adrenrgparticulier, blocenrg.taille );
    return LireEnContinu();
}
bool ficbinDGBLOC::LireEnrg()
{
    InitEnrgEnrg();
    if(LireEnContinu())
        return (blocenrg.balise==nomenrg);

    return false;
}
bool ficbinDGBLOC::LireListe()
{
    InitEnrgNomListe();
    if(LireEnContinu())
    {
        if(blocnomlist.balise==nomliste)
        {
           posoctetadebutfic += taillebaliselist;
           return true;
        }
    }
    return false;
}
bool ficbinDGBLOC::OkNomListe(){    return blocnomlist.balise==nomliste;}
quint32 ficbinDGBLOC::TailleNomListe(){    return blocnomlist.taille;}
quint32 ficbinDGBLOC::TailleBlocData(){    return blocdata.taille;}
bool ficbinDGBLOC::LireBloc()
{
    InitEnrgBloc();
    if(LireEnContinu())
    {
        if(blocdata.balise==nombalise)
        {
            posoctetadebutfic += tailleblocdata;
            return true;
        }
    }
    return false;
}
bool ficbinDGBLOC::PointerProchainNomListe()
{
    posoctetadebutfic += blocnomlist.taille;
    return PointerOctetCible();
}
bool ficbinDGBLOC::PointerProchainEnrg()
{
    posoctetadebutfic += tailleblocdata;
    posoctetadebutfic += blocenrg.taille;
    return PointerOctetCible();
}
bool ficbinDGBLOC::PointerProchaineBalise()
{
    posoctetadebutfic += tailleblocdata;
    posoctetadebutfic += blocdata.taille;
    return PointerOctetCible();
}
bool ficbinDGBLOC::RetourPointageDeBloc(){    return RePositionnerpointage(-tailleblocdata);}
bool ficbinDGBLOC::PointerDebutListe()
{
    ReinitEnrg((char *)&entete,sizeof(entete));
    OuvrirEnLecture();
    LireEnContinu();
    posoctetadebutfic = sizeof(entete);
    InitEnrgListe();
    while(LireEnContinu())
    {
        posoctetadebutfic += taillebaliselist;
        if(baliselist.balise==nombornelist)
        {
            if(nomliste!=0)
            {
                if(LireListe()) return true;
                InitEnrgListe();
            }
            else
                return true;
        }
        PasserListeSuivante();
    }
    FermerFichierContinu();
    return false;
}
void ficbinDGBLOC::PasserListeSuivante(){    posoctetadebutfic += baliselist.taille;}
void ficbinDGBLOC::InitEnrgListe(){    ReinitEnrg((char *)&baliselist,taillebaliselist);}
void ficbinDGBLOC::InitEnrgNomListe(){    ReinitEnrg((char *)&blocnomlist,taillebaliselist);}
void ficbinDGBLOC::InitEnrgBloc(){    ReinitEnrg((char *)&blocdata,tailleblocdata);}
void ficbinDGBLOC::InitEnrgEnrg(){    ReinitEnrg((char *)&blocenrg,tailleblocdata);}
void ficbinDGBLOC::InitTamponChaine()
{
    memset(&tamponchaine,0,sizeof(tamponchaine));
    ReinitEnrg((char *)&tamponchaine[0],blocdata.taille);
}
void ficbinDGBLOC::FermerFichierOuvert()
{
    fichiertraite.close();
    quint32 taille = (quint32) fichiertraite.size() - 8;
    fichiertraite.open( QIODevice::ReadWrite );
    fichiertraite.seek(4);
    fichiertraite.write( (char *)&taille, 4 );
    fichiertraite.close();
}
void ficbinDGBLOC::EcrireEnteteFichier( bool FACancien )
{
    /*
    00 00 00 00 : nomriff
    00 00 00 00 :   taille fichier - 8
    00 00 00 00 : nomtype
    00 00 00 00 : LIST
    00 00 00 00 : taille LIST
    */
    if(FACancien)
    {
        valeurtaille = 0;
        EcrireEntete();
        valeurtaille = 0;
        OuvrirListe();
    }
    else
    {
        qint64 dimfichier = TailleFichier();
        if(dimfichier<1)
        {//créer le fichier
            valeurtaille = 0;
            EcrireEntete();
            valeurtaille = 0;
            OuvrirListe();
        }
        else
            OuvrirEnAjoutEcriture();
    }
}
bool ficbinDGBLOC::Superposer()
{// le pointeur est en position
    quint32   tdata           = TailleBlocData();
    qint64 positioncurseur  = fichiertraite.pos()-tdata-8;
    fichiertraite.close();
    fichiertraite.open( QIODevice::ReadWrite );
    fichiertraite.seek(positioncurseur);
    EcrireLesBlocs();
    return true;
}
bool ficbinDGBLOC::RemplacerBloc()
{// le pointeur est en position
    bool resu = Superposer();
    FermerFichierContinu();
    return resu;
}
bool ficbinDGBLOC::ReEcrireBloc()
{
    volumeexpansion = qAbs(differencedetaille);
    Decaler();
    if(!PointerObjet()) return false;
    Superposer();
    FermerFichierOuvert();
    return true;
}
bool ficbinDGBLOC::Ecrire(bool FACancien)
{
    EcrireEnteteFichier(FACancien);
    EcrirePreBalise();
    EcrireLesBlocs();
    noerreur=0;
    FermerFichierOuvert();
    return true;
}
bool ficbinDGBLOC::Modifier()
{// initialiser : phrtest;
    // vtnouv
    differencedetaille = 0;
    if(PointerObjet())
    {
        quint32 vtanci = TailleBlocData();
        if(vtanci==tailledereference)
            return RemplacerBloc();
        else
        {
            differencedetaille = qAbs(tailledereference-vtanci);
            if(vtanci<tailledereference)
            {
                posoctetadebutfic = fichiertraite.pos()-differencedetaille;
                FermerFichierContinu();
                return ReEcrireBloc();
            }
            else
                return RemplacerBloc();
        }
    }
    else
        return Ecrire();
}

/****************************************
        Fonctions virtuelles vides
*****************************************/

void ficbinDGBLOC::EcrireLesBlocs(){}
void ficbinDGBLOC::EcrirePreBalise(){}
bool ficbinDGBLOC::PointerObjet(){return false;}
