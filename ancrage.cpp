//#include "ancrage.h"
#include "logiciel.h"
//#include <QtGui>

Ancrage::Ancrage(){}
Ancrage::Ancrage( Element *vbateau, ConfigurationObjet *ptrcfg )
{
    pconextmp = NULL;
    bateau = NULL;
    GenreElement(1000);
    NomElement("ancre");
    Valeur(&ptrcfg->PointeurCo()->enrancrage);
    AnnulerCartouche();
    bateau = vbateau;
    messagemsa = new MessageMSA;
}

Ancrage::~Ancrage(){}

void Ancrage::Valeur( EnrgAncre *pobjetancre )
{
    Valeur(pobjetancre->Icone(),
           pobjetancre->Largeur(),
           pobjetancre->Hauteur(),
           pobjetancre->Police());
}
void Ancrage::Valeur( const QString &imicon, quint8 large, quint8 haut, const EnrgPolice &vpoli )
{
    Police(vpoli);
    EntrerValeurGraph( large, haut );
    InitIcone(imicon);
}

void Ancrage::EntrerUneConnexionTemporaire( Connexion *valeur )
{
    pconextmp = valeur;
    RemonterLAncre();
}

void Ancrage::Nettoyerconnexion()
{
    if(pconextmp!=NULL)
    {
        Logiciel* toto = (Logiciel *)bateau;
        toto->RetirerAncre();
        scene()->removeItem(pconextmp);
        delete pconextmp;
        pconextmp=NULL;
    }
}

//QGraphicsItem *Ancrage::ValeurConnexion()
//{
//    if(pconextmp==NULL)
//        return NULL;
//    else
//        return (QGraphicsItem *) pconextmp;
//}

bool Ancrage::AncreMaterialisee()
{////
    return ((bateau!=NULL)&&(pconextmp!=NULL));
}
void Ancrage::RemonterLAncre()
{
    svdposition = bateau->pos();
    svdposition.setX(svdposition.rx()-LargeurElement()*2);
    setPos(svdposition);
    pconextmp->Actualiser();
    update();
}

bool Ancrage::TransfererConnexion( Element *pelem )
{
    Logiciel *plogique = (Logiciel *)pelem;
//    Element *pconnecte = pconextmp->ValeurSource();
//    if(pconnecte->Famille()!=pelem->Famille())
//    {
        plogique->TransfererUneConnexionAncre(pconextmp);
        pconextmp->RemplacerContact(this,pelem);
        pconextmp->Actualiser();
        pconextmp = NULL;
        bateau = NULL;
        return true;
//    }
//    return false;
}
void Ancrage::Standard()
{
    EnrgPolice policetmp("Bitstream Charter","#000000",5);
    Valeur(":/icone/attache.png",54,64,policetmp);
}

////************************************************************
////    Gestion des événements
////************************************************************
//******************* Routines persos ************************/
///******************* Routines QT ****************************/
void Ancrage::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    if (pconextmp!=NULL)
    {
        pconextmp->Actualiser();
        update();
    }
}

void Ancrage::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    bool revenir=true;
    QGraphicsItem::mouseReleaseEvent(event);
// detecter une collision avec un autre objet
    QList<QGraphicsItem *> tabitem = collidingItems();
    if(!tabitem.isEmpty())
    {
        for(int i=0;i<tabitem.size();i++)
        {
            Element *pelem = (Element*)tabitem.at(i);
            if(pelem->GenreElement()==100)
            {
               TransfererConnexion(pelem);
               revenir=false;
               break;
            }
        }
        if(revenir)
        {
            setPos(svdposition);
            pconextmp->Actualiser();
        }
        update();
    }
}

void Ancrage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->save();
        Qt::BrushStyle  typefond;
        bool tracerfond  = false;

        objetselectionne   = (option->state & QStyle::State_Selected);
        objetappuye        = (option->state & QStyle::State_Sunken);
        if(objetselectionne)
        {
           typefond = Qt::SolidPattern;
           tracerfond = true;
        }
        if(objetappuye)
        {
           typefond = Qt::Dense3Pattern;
           tracerfond = true;
        }
        if(tracerfond)
        {
           QPen crayon(Qt::NoPen);
           painter->setPen(crayon);
           QBrush pinceau = painter->brush();
              pinceau.setStyle(typefond);
              pinceau.setColor(CouleurFond());
           painter->setBrush(pinceau);
           painter->drawEllipse(TourFeuille());
        }
   painter->drawImage( -LargeurElement()+6, -HauteurElement()+8, ImageIcone() );
   painter->restore();
}

