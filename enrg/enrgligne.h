#ifndef ENRGLIGNE_H
#define ENRGLIGNE_H

#include "../structuredemarreur.h"

class EnrgLigne
{
public:

    EnrgLigne();
    EnrgLigne( const EnrgLigne &autre );

    void Valeur( const EnrgLigne &autre );
    void Valeur( const QString &vcou, quint8 vtyp, quint8 vepr );
    void Standard();

    void Couleur( const QString &valeur);
    void TypeLigne( quint8 valeur);
    void Epaisseur( quint8 valeur);

    QString Couleur() const;
    quint8  TypeLigne() const;
    quint8  Epaisseur() const;

    void CopierVersBloc(Ligne &cible );
    void CopierDepuisBloc( const Ligne &source );

    virtual bool EgaleA( const EnrgLigne &autre );


private:
    //1    SolidLine,
    //2    DashLine,
    //3    DotLine,
    //4    DashDotLine,
    //5    DashDotDotLine,
    //6    CustomDashLine

    QString couleur;
    quint8  typeligne;
    quint8  epaisseur;

};

#endif // ENRGCONNEXION_H
