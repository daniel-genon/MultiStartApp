#include "enrgligne.h"

/*
    Structure de données pour connexion
*/
EnrgLigne::EnrgLigne(){}
EnrgLigne::EnrgLigne( const EnrgLigne &autre ){Valeur( autre );}
void EnrgLigne::Valeur( const EnrgLigne &autre )
{
    Valeur( autre.Couleur(), autre.TypeLigne(), autre.Epaisseur() );
}
void EnrgLigne::Valeur( const QString &vcou, quint8 vtyp, quint8 vepr )
{
    if(!vcou.isEmpty()) couleur = vcou;
    typeligne   = vtyp;
    epaisseur   = vepr;
}
void EnrgLigne::Couleur( const QString &valeur){    couleur     = valeur;}
void EnrgLigne::TypeLigne( quint8 valeur){    typeligne   = valeur;}
void EnrgLigne::Epaisseur( quint8 valeur){    epaisseur   = valeur;}
QString EnrgLigne::Couleur() const{    return couleur;}
quint8  EnrgLigne::TypeLigne() const{    return typeligne;}
quint8  EnrgLigne::Epaisseur() const{    return epaisseur;}
bool EnrgLigne::EgaleA( const EnrgLigne &autre )
{
    if(typeligne!=autre.TypeLigne()) return false;
    if(QString::compare(couleur,autre.Couleur(),Qt::CaseInsensitive)!=0) return false;
    return epaisseur!=autre.Epaisseur();
}
void EnrgLigne::Standard(){    Valeur( "#7b1d93", 1, 2 );}
void EnrgLigne::CopierVersBloc( Ligne &cible )
{
    TransQstrVersStr( couleur, &cible.coul );
    cible.epr    = epaisseur;
    cible.typlig = typeligne;
}
void EnrgLigne::CopierDepuisBloc(const Ligne &source )
{
    couleur  = QString((QChar *)&source.coul );
    epaisseur = source.epr;
    typeligne = source.typlig;
}
