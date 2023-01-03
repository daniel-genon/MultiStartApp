#ifndef ENRGPOLICE_H
#define ENRGPOLICE_H

#include "../structuredemarreur.h"

class EnrgPolice
{
public:

    EnrgPolice();
    EnrgPolice( const EnrgPolice &autre );
    EnrgPolice( const QString &vnom, const QString &vcoul, int haut );

    void Valeur( const QString &vnom, const QString &vcoul, int haut );
    void Valeur( const EnrgPolice &autre );

    void Couleur( const QString &vcoul);
    void Nom( const QString &vnom );
    void Hauteur( quint8 haut );

    QString Nom() const;
    QString Couleur() const;
    quint8  Hauteur() const;

    QString *PCouleur();

    bool EgaleA( const EnrgPolice &autre );

    void CopierVersBloc( BlocPolice &cible );
    void CopierDepuisBloc( const BlocPolice &source );

private:
    QString nompol;
    QString coulpol;
    quint8  hautpol;
};

#endif // ENRGPOLICE_H
