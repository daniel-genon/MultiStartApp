#include "fichier.h"
#include "configurationobjet.h"
#include "enrg/enrgobjetctx.h"

Fichier::Fichier(){}

QString Fichier::Libelle() const {    return Enrg.Libelle();}

QString Fichier::NomFichier(bool maison) const
{
    return Enrg.NomComplet(maison);
}

void Fichier::Entrer ( const EnrgFichier &valeur ){    Enrg.Entrer(valeur);}

void Fichier::Extension( const QString &valeur ){    Enrg.Extension(valeur);}

void Fichier::Libelle( const QString &valeur ){    Enrg.Libelle(valeur);}

void Fichier::InitFichier()
{
   Couleurs( cfgobjet->PointeurFi()->CouleurBandeau(), cfgobjet->PointeurFi()->CouleurFond() );
   Police( cfgobjet->PointeurFi()->Police() );
   EntrerValeurGraph( cfgobjet->PointeurFi()->Largeur(), cfgobjet->PointeurFi()->Hauteur() );
}

void Fichier::EcrireTitre()
{
    plume->drawText( TourInfo(), Qt::AlignCenter, Libelle() );
}
void Fichier::EcrireNom()
{
    plume->drawText( TourCartouche(), Qt::AlignCenter, NomElement() );
}

////************************************************************
////     Gestion des événements
////************************************************************

