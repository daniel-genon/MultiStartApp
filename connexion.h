#ifndef CONNEXION_H
#define CONNEXION_H

//#include"enrg/enrgconnexion.h"

#include "configurationobjet.h"

class Connexion : public GraphiqueSurface
{
public:

    Connexion( Element *valeur , EnrgConnexion *ptr );
    void Actualiser();
    bool EntrerContact( Element *valeur );
    QGraphicsItem *ValeurConnexion();

    void RemplacerContact( Element *pexistant, Element *pnouveau );
    Element *ValeurCible() const;
    Element *ValeurSource() const;

    Element *ValeurAutreConnecter(Element *pexistant ) const;

protected:

//    int     eprtrait;

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *);

private:

    Element *pcible;
    Element *psource;

    QPointF pntcible;
    QPointF pntsource;
//    QPointF pntinterc;
//    QPointF pntinters;

    quint8  typedeligne;
    quint8  epaisseur;

};

typedef Connexion *ptrconnexion;


#endif // CONNEXION_H
