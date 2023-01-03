#include "enrgconfig.h"

/*
    Structure de données pour config generale
*/

EnrgConfig::EnrgConfig(){}
EnrgConfig::EnrgConfig( const QString &vnom,
                   const QString &vcogra,
                   const QString &vcomen,
                   const EnrgPolice &vpoli,
                   quint8 vhidrt,
                   quint8 vhigah,
                   quint8 vhidso )
{
    Valeur( vnom, vcogra, vcomen, vpoli, vhidrt, vhigah, vhidso );
}

void EnrgConfig::Valeur( const QString &vnom,
           const QString &vcogra,
           const QString &vcomen,
           const EnrgPolice &vpoli,
           quint8 vhidrt,
           quint8 vhigah,
           quint8 vhidso )
{
    Nom( vnom );
    CouleurGraphique( vcogra );
    CouleurMenu( vcomen );
    police.Valeur(vpoli);
    Icones( vhidso, vhidrt, vhigah );
}

void EnrgConfig::Valeur( const EnrgConfig &autre )
{
    Nom( autre.Nom() );
    CouleurGraphique( autre.CouleurGraphique());
    CouleurMenu( autre.CouleurMenu() );
    Icones( autre.IconeDessous(), autre.IconeGestion(), autre.IconeSymbole() );
    police.Valeur(autre.Police());
}
void EnrgConfig::Valeur( const EnrgConfig *pautre )
{
    Nom( pautre->Nom() );
    CouleurGraphique( pautre->CouleurGraphique());
    CouleurMenu( pautre->CouleurMenu() );
    Icones( pautre->IconeDessous(), pautre->IconeGestion(), pautre->IconeSymbole() );
    police.Valeur(pautre->Police());
}

void EnrgConfig::Nom( const QString &valeur){ nom = valeur;}
void EnrgConfig::CouleurGraphique( const QString &valeur){ coulecrangraph = valeur;}
void EnrgConfig::CouleurMenu( const QString &valeur){ coulbarremenu = valeur;}
void EnrgConfig::IconeGestion( quint8 valeur ){ hticodroite = valeur;}
void EnrgConfig::IconeSymbole(quint8 valeur ){ hticogauche = valeur;}
void EnrgConfig::IconeDessous( quint8 valeur ){hticodessous = valeur;}
void EnrgConfig::Icones( quint8 vdeo, quint8 vdrt, quint8 vgah )
{
    hticodessous = vdeo;
    hticodroite = vdrt;
    hticogauche = vgah;
}
void EnrgConfig::Police( const EnrgPolice &valeur ){police.Valeur(valeur);}

QString EnrgConfig::Nom() const {return nom;}
QString EnrgConfig::CouleurGraphique() const {return coulecrangraph;}
QString EnrgConfig::CouleurMenu() const {return coulbarremenu;}
quint8  EnrgConfig::IconeGestion() const{ return hticodroite; }
quint8  EnrgConfig::IconeSymbole() const{ return hticogauche; }
quint8  EnrgConfig::IconeDessous() const{ return hticodessous; }
EnrgPolice EnrgConfig::Police() const{    return police;}
EnrgPolice *EnrgConfig::PPolice(){    return &police;}

QString *EnrgConfig::PCouleurGraphique(){return &coulecrangraph;}
QString *EnrgConfig::PCouleurMenu(){return &coulbarremenu;}

bool EnrgConfig::EgaleA( const EnrgConfig &autre, bool testnom )
{
    if(testnom)
        if(QString::compare(nom,autre.Nom(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(coulecrangraph,autre.CouleurGraphique(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(coulbarremenu,autre.CouleurMenu(),Qt::CaseInsensitive)!=0) return false;
    if(hticodessous!=autre.IconeDessous()) return false;
    if(hticodroite!=autre.IconeGestion()) return false;
    if(hticogauche!=autre.IconeSymbole()) return false;
    return police.EgaleA( autre.Police() );
}
void EnrgConfig::CopierVersBloc( BlocConfig &cible )
{
    memset(&cible,0,sizeof(cible));
    cible.hticodeo = hticodessous;
    cible.hticodrt = hticodroite;
    cible.hticogah = hticogauche;
    TransQstrVersStr( nom, &cible.nom );
    TransQstrVersStr( coulecrangraph, &cible.coulecrangraph );
    TransQstrVersStr( coulbarremenu, &cible.coulbarremenu );
    police.CopierVersBloc(cible.Bpolice);
}

void EnrgConfig::CopierDepuisBloc( const BlocConfig &source )
{
    hticodessous    = source.hticodeo;
    hticodroite     = source.hticodrt;
    hticogauche     = source.hticogah;
    nom             = QString((QChar *)&source.nom);
    coulecrangraph  = QString((QChar *)&source.coulecrangraph);
    coulbarremenu   = QString((QChar *)&source.coulbarremenu);
    police.CopierDepuisBloc(source.Bpolice);
}

void EnrgConfig::Standard()
{
    EnrgPolice policetmp("Bitstream Charter","#000000",12);
    Valeur( "STANDARD", "#3c6483", "#3b3b3b", policetmp, 40, 20, 20 );
}
