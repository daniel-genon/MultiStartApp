#ifndef ENRGCONNEXION_H
#define ENRGCONNEXION_H

#include "enrgancre.h"
#include "enrgligne.h"

class EnrgConnexion
{
public:

    int encours;

    EnrgAncre enrancrage;
    EnrgLigne tligne[MTLIG];// 0:log, 1:cfg, 2:trv

    EnrgConnexion();
    EnrgConnexion( const EnrgConnexion &autre );

    void Valeur( const EnrgConnexion &autre );

    QString CCouleur() const;
    quint8  CTypeLigne() const;
    quint8  CEpaisseur() const;

    virtual bool EgaleA( const EnrgConnexion &autre );

    void CopierVersBloc( BlocConnexion &cible );
    void CopierDepuisBloc( const BlocConnexion &source );
    void Standard();

    EnrgAncre *PtrAncrage();

};

#endif // ENRGCONNEXION_H
