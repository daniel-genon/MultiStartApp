#ifndef FICHIER_H
#define FICHIER_H

#include "graphobjetactif.h"
#include "enrg/enrgfichier.h"

class Fichier : public GraphObjetActif
{
public:

    Fichier();

    void Entrer ( const EnrgFichier &valeur );
    void Extension( const QString &valeur );
    void Libelle( const QString &valeur );

    QString Libelle() const;
    QString NomFichier(bool maison) const;

protected:

    void InitFichier();
    void EcrireTitre();
    void EcrireNom();


private:

    EnrgFichier Enrg;

};

#endif // FICHIER_H
