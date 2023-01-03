#include "enrgpolice.h"

/*
    Structure de données pour police de caractères
*/
EnrgPolice::EnrgPolice(){}
EnrgPolice::EnrgPolice( const EnrgPolice &autre ){Valeur( autre );}
EnrgPolice::EnrgPolice( const QString &vnom, const QString &vcoul, int haut ){Valeur( vnom, vcoul, haut );}
void EnrgPolice::Valeur( const QString &vnom, const QString &vcoul, int haut )
{
    if(!vnom.isEmpty()) nompol  = vnom;
    if(!vcoul.isEmpty()) coulpol = vcoul;
    hautpol = haut;
}

void EnrgPolice::Valeur( const EnrgPolice &autre )
{
    nompol  = autre.Nom();
    coulpol = autre.Couleur();
    hautpol = autre.Hauteur();
}

void EnrgPolice::Nom( const QString &vnom ){ nompol  = vnom;}
void EnrgPolice::Couleur( const QString &vcoul){    coulpol = vcoul;}
void EnrgPolice::Hauteur( quint8 haut ){    hautpol = haut;}
QString EnrgPolice::Nom() const{    return nompol;}
QString EnrgPolice::Couleur() const{    return coulpol;}
quint8 EnrgPolice::Hauteur() const{    return hautpol;}
QString *EnrgPolice::PCouleur(){    return &coulpol;}
bool EnrgPolice::EgaleA( const EnrgPolice &autre )
{
    if(hautpol!=autre.Hauteur()) return false;
    if(QString::compare(nompol,autre.Nom(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(coulpol,autre.Couleur(),Qt::CaseInsensitive)!=0) return false;
    return true;
}

void EnrgPolice::CopierVersBloc( BlocPolice &cible )
{
        memset(&cible,0,sizeof(cible));
    TransQstrVersStr( nompol, &cible.nompol );
    TransQstrVersStr( coulpol, &cible.coulpol );
    cible.hautpol   = hautpol;
}
void EnrgPolice::CopierDepuisBloc( const BlocPolice &source )
{
    nompol  = QString((QChar *)&source.nompol);
    coulpol = QString((QChar *)&source.coulpol);
    hautpol = source.hautpol;
}

