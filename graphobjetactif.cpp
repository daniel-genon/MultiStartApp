#include "graphobjetactif.h"

GraphObjetActif::GraphObjetActif()
{
    pancretmp = NULL;
    pelemresu = NULL;
}
GraphObjetActif::~GraphObjetActif()
{
//    if(!lstconex.isEmpty())
//    {
//        for(int i=0;i<lstconex.size();i++)
//        {
//            pconexencours = lstconex.at(i);
//            SupprimerConnexion();
//        }
//        lstconex.clear();
//    }
}

void GraphObjetActif::EntrerUneConnexion( Connexion *valeur )
{
    pconexencours = valeur;
    lstconex.append(pconexencours);
}

bool GraphObjetActif::CreerConnexion(Element *ptrcible)
{
   if(ptrcible!=NULL)
   {
      pconexencours =  new Connexion(ptrcible, cfgobjet->PointeurCo() );
      if(pconexencours!=NULL)
      {
          lstconex.append(pconexencours);
          return true;
      }
   }
   return false;
}

bool GraphObjetActif::TrouverConnexion( int valgenre )
{
    if(!lstconex.isEmpty())
    {
        for(int i=0;i<lstconex.size();i++)
        {
            Element *pelem = lstconex.at(i)->ValeurCible();
            if(pelem!=NULL)
                if(pelem->GenreElement()==valgenre)
                {
                    pelemresu=pelem;
                    return true;
                }
        }
    }
    pelemresu=NULL;
    return false;
}
Connexion *GraphObjetActif::DerniereConnexionDeLaListe() const
{
    if(!lstconex.isEmpty())
    {
        return lstconex.last();
    }
    return NULL;
}

void GraphObjetActif::ActualiserConnexion()
{
    if(!lstconex.isEmpty())
    {
        for(int i=0;i<lstconex.size();i++)
            lstconex.at(i)->Actualiser();
    }
}
bool GraphObjetActif::EntrerSourceConnexion( Element *valeur )
{
    if(!pconexencours->EntrerContact(valeur)) return false;
    ActualiserConnexion();
    return true;
}
bool GraphObjetActif::AncreNonLarguee()
{
    if(pancretmp==NULL) return false;
    return pancretmp->AncreMaterialisee();
}
void GraphObjetActif::RetirerAncre()
{
    pancretmp = NULL;
}
void GraphObjetActif::EntrerUneAncre(Ancrage *pvaleur, Element *vbateau, EnrgConnexion *pvalconex )
{
    pancretmp = pvaleur;
    pconexencours =  new Connexion(pancretmp,pvalconex);
    EntrerSourceConnexion( vbateau );
    pancretmp->EntrerUneConnexionTemporaire(pconexencours);
    lstconex.append(pconexencours);
}
void GraphObjetActif::TransfererUneConnexionAncre( Connexion *valeur )
{
    EntrerUneConnexion( valeur );
    SupprimerLesItemsAncre();
}
bool GraphObjetActif::CreerUneConnexionNouvelle(Element *psource, Element *pcible )
{
    if(!CreerConnexion(pcible)) return false;
    return EntrerSourceConnexion(psource);
}
void GraphObjetActif::SupprimerLesItemsAncre()
{
    QGraphicsItem *pobjet;
    QList<QGraphicsItem *> tabitem = pscene->items();
    for(int i=0;i<tabitem.length();i++)
    {
        pobjet = tabitem.at(i);
        Element *pelem = (Element *)pobjet;
        if((pelem->GenreElement()==1000))
            pscene->removeItem( pobjet );
    }
}
QGraphicsItem *GraphObjetActif::ValeurConnexion()
{
    if(pconexencours==NULL)
        return NULL;
    else
        return (QGraphicsItem *) pconexencours;
}

bool GraphObjetActif::ConnecterFichier( Element *valeur )
{
   if(valeur==NULL) return false;
   ((GraphObjetActif *)valeur)->pscene = pscene;
   if(!CreerConnexion( valeur)) return false;
   return EntrerSourceConnexion(( Element *)this);
}
void GraphObjetActif::Deconnecter( Connexion *pconex, bool detruireconex )
{
    lstconex.removeOne(pconex);
    if(detruireconex)
    {
        delete pconex;
    }
    pconexencours=NULL;
}
void GraphObjetActif::SupprimerConnexion()
{// initialiser pconexencours. // supprime le graphique et l'instance connexion
    Element *pcible = pconexencours->ValeurCible();
    if(pcible!=NULL)
    {
        pscene->removeItem((QGraphicsItem *)pconexencours);
        ((GraphObjetActif *)pcible)->Deconnecter(pconexencours,true);
    }
}
ConfigurationObjet *GraphObjetActif::PtrConfObjet() const
{
    return cfgobjet;
}


////************************************************************
////     Gestion des événements
////************************************************************


void GraphObjetActif::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    bool okup=false;
    QGraphicsItem::mouseMoveEvent(event);
    if(AncreNonLarguee())
    {
        pancretmp->RemonterLAncre();
        okup=true;
    }
    if(!lstconex.isEmpty())
    {
        for(int i=0;i<lstconex.size();i++)
            lstconex.at(i)->Actualiser();
        okup=true;
    }
    if(okup) update();
}
