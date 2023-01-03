#include "enrgconnexion.h"

/*
    Structure de données pour connexion
*/
EnrgConnexion::EnrgConnexion(){encours=0;}
EnrgConnexion::EnrgConnexion( const EnrgConnexion &autre ){ encours=0; Valeur( autre );}
void EnrgConnexion::Valeur( const EnrgConnexion &autre )
{
    for( int i=0; i<MTLIG; i++)
        tligne[i].Valeur(autre.tligne[i]);
    enrancrage.Valeur(autre.enrancrage);
}
QString EnrgConnexion::CCouleur() const {    return tligne[encours].Couleur();}
quint8  EnrgConnexion::CTypeLigne() const{    return tligne[encours].TypeLigne();}
quint8  EnrgConnexion::CEpaisseur() const{    return tligne[encours].Epaisseur();}
bool EnrgConnexion::EgaleA( const EnrgConnexion &autre )
{
    for( int i=0; i<MTLIG; i++)
        if (!tligne[i].EgaleA(autre.tligne[i])) return false;

    return enrancrage.EgaleA(autre.enrancrage);
}
void EnrgConnexion::CopierVersBloc( BlocConnexion &cible )
{
    memset(&cible,0,sizeof(cible));
    for( int i=0; i<MTLIG; i++)
        tligne[i].CopierVersBloc(cible.tligne[i]);

    enrancrage.CopierVersBloc(cible.ancre);
}
void EnrgConnexion::CopierDepuisBloc( const BlocConnexion &source )
{
    for( int i=0; i<MTLIG; i++)
        tligne[i].CopierDepuisBloc(source.tligne[i]);

    enrancrage.CopierDepuisBloc(source.ancre);
}
void EnrgConnexion::Standard()
{
    for( int i=0; i<MTLIG; i++)
        tligne[i].Standard();
    enrancrage.Standard();
}
EnrgAncre *EnrgConnexion::PtrAncrage(){ return &enrancrage; }




