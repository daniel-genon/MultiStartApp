#ifndef ENRGANCRE_H
#define ENRGANCRE_H

#include "../graphiquesurface.h"

class EnrgAncre : public GraphiqueSurface
{
public:
    EnrgAncre();
    EnrgAncre( const QString &vico,
              const QString &vcofon,
              const EnrgPolice &vpoli,
              quint8  vlar,
              quint8  vhau );

    void Valeur( const EnrgAncre &autre );
//    void Valeur( EnrgAncre *autre );
    void Valeur(  const QString &vico,
                  const QString &vcofon,
                  const EnrgPolice &vpoli,
                  quint8  vlar,
                  quint8  vhau );

    void Standard();
//    void Icone( const QString &valeur);

//    QString Nom() const;
//    quint16 Famille() const;
//    QString NomClair() const;

    QString Icone() const;

    bool EgaleA( const EnrgAncre &autre );

    void CopierVersBloc( BlocAncre &cible );
    void CopierDepuisBloc( const BlocAncre &source );

private:

    QString imicone;

};

#endif // ENRGANCRE_H
