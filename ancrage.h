#ifndef ANCRAGE_H
#define ANCRAGE_H

#include "connexion.h"
#include "configurationobjet.h"
#include "dialogue/messagemsa.h"


class Ancrage : public GraphiqueSurface
{
public:

    Ancrage();
    Ancrage( Element *vbateau, ConfigurationObjet *ptrcfg );

    ~Ancrage();

    void Valeur( EnrgAncre *pobjetancre );
    void Valeur( const QString &imicon, quint8 large, quint8 haut, const EnrgPolice &vpoli );
    void Standard();

    void EntrerUneConnexionTemporaire( Connexion *valeur );
//    QGraphicsItem *ValeurConnexion();

    bool AncreMaterialisee();
    void Nettoyerconnexion();
    void RemonterLAncre();

protected:

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:

    Connexion   *pconextmp;
    Element     *bateau;
    QPointF     svdposition;
    MessageMSA  *messagemsa;

    bool TransfererConnexion( Element *pelem );

};

#endif // ANCRAGE_H
