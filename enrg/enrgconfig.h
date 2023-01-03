#ifndef ENRGCONFIG_H
#define ENRGCONFIG_H

#include "enrgpolice.h"
#include <QRect>

class EnrgConfig
{
public:
    EnrgConfig();
    EnrgConfig( const QString &vnom,
                       const QString &vcogra,
                       const QString &vcomen,
                       const EnrgPolice &vpoli,
                       quint8 vhidrt,
                       quint8 vhigah,
                       quint8 vhidso );

    void Valeur( const QString &vnom,
               const QString &vcogra,
               const QString &vcomen,
               const EnrgPolice &vpoli,
               quint8 vhidrt,
               quint8 vhigah,
               quint8 vhidso );

    void Valeur( const EnrgConfig &autre );
    void Valeur( const EnrgConfig *pautre );

    void Nom( const QString &valeur);
    void CouleurGraphique( const QString &valeur);
    void CouleurMenu( const QString &valeur);
    void IconeGestion( quint8 valeur );
    void IconeSymbole(quint8 valeur );
    void IconeDessous( quint8 valeur );
    void Icones( quint8 vdeo, quint8 vdrt, quint8 vgah );
    void Police( const EnrgPolice &valeur );


    QString Nom() const;
    QString CouleurGraphique() const;
    QString CouleurMenu() const;
    quint8  IconeGestion() const;
    quint8  IconeSymbole() const;
    quint8  IconeDessous() const;
    EnrgPolice Police() const;
    EnrgPolice *PPolice();

    QString *PCouleurGraphique();
    QString *PCouleurMenu();

    bool EgaleA(const EnrgConfig &autre , bool testnom=true);
    void CopierDepuisBloc( const BlocConfig &source );
    void CopierVersBloc( BlocConfig &cible );
    void Standard();
    QRect *GeometrieFenetreSVD() const;

private:
    QString     nom;
    quint8      hticodessous;
    quint8      hticodroite;
    quint8      hticogauche;
    QString     coulecrangraph;
    QString     coulbarremenu;
    EnrgPolice  police;
    QRect       DimFenetre;

};

#endif // ENRGCONFIG_H
