#ifndef GRAPHOBJETACTIF_H
#define GRAPHOBJETACTIF_H

#include "graphiquesurface.h"
#include <qgraphicsscene.h>
#include "configurationobjet.h"
#include "ancrage.h"

class GraphObjetActif : public GraphiqueSurface
{
public:

    GraphObjetActif();
    ~GraphObjetActif();
    void EntrerUneConnexion( Connexion *valeur );

    QGraphicsItem *ValeurConnexion();
    void EntrerUneAncre( Ancrage *pvaleur, Element *vbateau, EnrgConnexion *pvalconex );
    void TransfererUneConnexionAncre( Connexion *valeur );
    bool CreerUneConnexionNouvelle( Element *psource, Element *pcible );
    bool AncreNonLarguee();
    void RetirerAncre();
    bool ConnecterFichier( Element *valeur );
    void Deconnecter( Connexion *pconex, bool detruireconex );
    Connexion *DerniereConnexionDeLaListe() const;
    void SupprimerConnexion();
    ConfigurationObjet *PtrConfObjet() const;

protected:

    bool EntrerSourceConnexion( Element *valeur );
    bool CreerConnexion(Element *ptrcible);
    bool TrouverConnexion( int valgenre );

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    ConfigurationObjet *cfgobjet;
    QGraphicsScene *pscene;

    Element *pelemresu;

private:

    Connexion *pconexencours;
    QList<Connexion *> lstconex;
    Ancrage *pancretmp;

    void ActualiserConnexion();
    void SupprimerLesItemsAncre();

};

#endif // GRAPHOBJETACTIF_H
