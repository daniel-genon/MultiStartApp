#include "connexion.h"
#include <QtGui>
Connexion::Connexion(Element *valeur , EnrgConnexion *ptr )
{
    pcible=valeur;
    psource=NULL;
    pntcible.setX(1);
    pntcible.setY(1);
    pntsource.setX(0);
    pntsource.setY(0);
    GenreElement(5000);
    NomElement("connecteur");
    if(ptr==NULL)
    {
        CouleurConnexion("#FF0000");
        typedeligne = 1;
        epaisseur   = 2;
    }
    else
    {
        CouleurConnexion(ptr->CCouleur());
        typedeligne = ptr->CTypeLigne();
        epaisseur   = ptr->CEpaisseur();
    }

}
void Connexion::Actualiser()
{
   if((pcible!=NULL)&&(psource!=NULL))
   {
       qreal toClarg,toSlarg,toChaut,toShaut;
       QPointF pntc    = pcible->pos();
       QPointF pnts    = psource->pos();
       qreal xstmp = pnts.x();
       qreal xctmp = pntc.x();
       qreal ystmp = pnts.y();
       qreal yctmp = pntc.y();
       pcible->Dimensions( toClarg, toChaut );
       psource->Dimensions( toSlarg, toShaut );
           qreal dx,dy;
           int idxS=100;
           int idxC=100;
           int cas=0;
       if(EgalAvecTolerance( xstmp, xctmp,(toClarg+toSlarg) )) cas=1;//aligne en X
       if(EgalAvecTolerance( ystmp, yctmp,(toChaut+toShaut) )) cas+=2;//aligne en Y
       if(xstmp>xctmp) cas+=4;//cible à gauche
       if(ystmp>yctmp) cas+=8;//cible haut
       dx=qAbs(xstmp-xctmp);
       dy=qAbs(ystmp-yctmp);
       switch(cas)
       {
        case  1:{//aligne X cible en bas
          idxS = 0;
          idxC = 2;
               }break;
       case  5:{//aligne X cible en bas
         idxS = 0;
         idxC = 2;
              }break;
       case  9:{//aligne X cible haut
          idxS = 2;
          idxC = 0;
               }break;
       case 13:{//aligne X cible haut
          idxS = 2;
          idxC = 0;
               }break;
       case  2:{//aligne en Y cible drt
         idxS = 1;
         idxC = 3;
              }break;
       case  10:{//aligne en Y cible drt
         idxS = 1;
         idxC = 3;
              }break;
       case  6:{//aligne Y cible à gah
          idxS = 3;
          idxC = 1;
               }break;
       case 14:{//aligne Y cible à gah
          idxS = 3;
          idxC = 1;
               }break;
       case   0:{//cible bas drt
           if(dx>dy)
            {idxS = 1;idxC = 3;}
           else
            {idxS = 0;idxC = 2;}
                }break;
       case   4:{//cible bas gauche
           if(dx>dy)
            {idxS = 3;idxC = 1;}
           else
            {idxS = 0;idxC = 2;}
                }break;
       case   8:{//cible haut drt
           if(dx>dy)
           {idxS = 1;idxC = 3;}
           else
           {idxS = 2;idxC = 0;}
                }break;
       case  12:{//cible haut gah
           if(dx>dy)
            {idxS = 3;idxC = 1;}
           else
            {idxS = 2;idxC = 0;}
                }break;
       default:{//aligne en XetY (superposé) 3 7 11 15
           idxS = 100;
           idxC = 100;
               }
       }
       pntsource = psource->PointDeContact(idxS);
       pntcible  = pcible->PointDeContact(idxC);
   }
}
bool Connexion::EntrerContact( Element *valeur )
{
    if(psource!=NULL) return false;
    psource=valeur;
    return true;
}
Element *Connexion::ValeurCible() const {   return pcible;}
Element *Connexion::ValeurSource() const {   return psource;}
Element *Connexion::ValeurAutreConnecter( Element *pexistant ) const
{
    if(psource!=pexistant) return psource;
    return pcible;
}
void Connexion::RemplacerContact( Element *pexistant, Element *pnouveau )
{
    if(psource==pexistant)
        psource = pnouveau;
    else
        pcible = pnouveau;
}
QRectF Connexion::boundingRect() const
{// zone graphique de l'objet : sensibilité, effacement et
// persistance des graphiques de ce conteneur
    return QRectF( QPointF(qMin(pntsource.x(),pntcible.x()),qMin(pntsource.y(),pntcible.y())),
                   QPointF(qMax(pntsource.x(),pntcible.x()),qMax(pntsource.y(),pntcible.y()))
                 );
}
//QPainterPath Connexion::shape() const
//{
//    QPainterPath path;
//    QRectF toto(QPointF(qMin(pntsource.x(),pntcible.x()),qMin(pntsource.y(),pntcible.y())),
//                QPointF(qMax(pntsource.x(),pntcible.x()),qMax(pntsource.y(),pntcible.y())));
//    path.addRect(toto);
//    return path;
//}
void Connexion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if((pcible!=NULL)&&(psource!=NULL))
    {
        Q_UNUSED(widget);
        painter->save();

        objetselectionne   = (option->state & QStyle::State_Selected);
        objetenmouvement   = (option->state & QStyle::State_MouseOver);
        objetappuye        = (option->state & QStyle::State_Sunken);

        QColor couleursymbole(CouleurFond());
        Qt::PenStyle  typeligne = Qt::SolidLine;
        //        Qt::PenStyle  typeligne = ( Qt::PenStyle) penrcon->TypeLigne();

        if(objetselectionne)    couleursymbole = couleursymbole.darker(150);// assombrir;
        if(objetenmouvement)    couleursymbole = couleursymbole.lighter(125);// éclairer;
        if(objetappuye) typeligne = Qt::DotLine;

        QPen pen;
            pen.setStyle(typeligne);
            pen.setColor(couleursymbole);
            pen.setWidth(epaisseur);
            painter->setPen(pen);
            painter->drawLine(pntsource, pntcible);
        painter->restore();
    }
}
////************************************************************
////    Gestion des événements
////************************************************************
//******************* Routines persos ************************/
///******************* Routines QT ****************************/
void Connexion::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
//    QGraphicsItem::mouseReleaseEvent(event);
}
void Connexion::mouseMoveEvent(QGraphicsSceneMouseEvent *)
{
//    QGraphicsItem::mouseMoveEvent(event);
}
void Connexion::mousePressEvent(QGraphicsSceneMouseEvent *)
{
//    QGraphicsItem::mousePressEvent(event);
}
