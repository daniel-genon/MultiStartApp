#include "element.h"

Element::Element()
{
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
    genre = 99999;
    valgra1 = 50;
    valgra2 = 25;
    valgra3 = 0;
    icoelement.load(":/icone/demarre.png");
    hticone = icoelement.height();
    lgicone = icoelement.width();
    eprcadre    = 1;
    margeicone  = 2;
    nomelement  = "élément";

//    nomfamille = "inconnu";
//    nomgenre = "inconnu";
}

void Element::InitIcone(const QString &phricone)
{
//    extern QString *pCHRacine;
    if(phricone.isEmpty())
        icoelement.load(":/icone/attache.png");
    else
    {
//        if(phricone.operator [](0)==':')
            icoelement.load(phricone);
//        else
//        {
//            QString phtmp(pCHRacine->data());
//            phtmp.append(phricone);
//            icoelement.load(phtmp);
//        }
    }
    hticone = icoelement.height();
    lgicone = icoelement.width();
}

void Element::GenreElement( int valeur ){    genre = valeur;}
void Element::NomElement(const QString &valeur){    nomelement = valeur;}
void Element::EntrerValeurGraph( const int val1, const int val2 )
{
    valgra1 = val1/2;
    valgra2 = val2/2;
}
int Element::GenreElement() const {    return genre;}
QString Element::NomElement() const { return nomelement;}
bool Element::EstUnLogiciel()
{
    return (genre==100);
}

void Element::PositionDansScene( int &valx, int &valy  )
{
    QPointF valret = pos();
    valx = (int)valret.x();
    valy = (int)valret.y();
}
void Element::Dimensions( qreal &large, qreal &haut )
{
    large = valgra1;
    haut  = valgra2+valgra3;
}
int Element::PositionXDansScene(){    return (int)pos().x();}
int Element::PositionYDansScene(){    return (int)pos().y();}
int Element::Largeur() const { return (valgra1 * 2); }
int Element::Hauteur() const { return (valgra2 * 2); }
int Element::HauteurElement() const{    return valgra2;}
int Element::LargeurElement() const{    return valgra1;}
void Element::AnnulerCartouche(){ valgra3=0; }
QImage Element::ImageIcone() const{    return icoelement;}
QPointF Element::PointDeContact( int idx )
{
    QPointF pncentre(pos());
    switch(idx)
    {
        case 0:{
            pncentre.setY(pncentre.ry()+valgra2+(valgra3/2));
        }break;
        case 1:{
            pncentre.setX(pncentre.rx()+valgra1);
        }break;
        case 2:{
            pncentre.setY(pncentre.ry()-valgra2-(valgra3/2));
        }break;
        case 3:{
            pncentre.setX(pncentre.rx()-valgra1);
        }break;
//        default:{

//        }
    }
    return ( pncentre );
}

///******************* Routines Graphiques perso ****************************/
QRectF Element::TourInfo() const
{
    return QRectF(-valgra1, 0, (valgra1-margeicone)*2-lgicone , valgra3);
}
QRectF Element::TourFeuille() const
{
    return QRectF(-valgra1, -valgra2+valgra3/2, valgra1*2, valgra2*2);
}
void Element::DessinerIcone()
{
    plume->drawImage( valgra1-lgicone-margeicone,-(int)hticone/2+valgra3/2, icoelement );
}

///******************* Routines QT ****************************/
QRectF Element::boundingRect() const
{
//    return QRectF(-valgra1-2, -valgra2-(int)htcartouche/2-2, valgra1*2+4, valgra2*2+htcartouche+4);
    return QRectF(-valgra1-2, -valgra2-(int)valgra3/2-2, valgra1*2+4, valgra2*2+valgra3+4);
}

void Element::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    plume = painter;
    Q_UNUSED(widget);
    plume->save();

       objetselectionne   = (option->state & QStyle::State_Selected);
       objetenmouvement   = (option->state & QStyle::State_MouseOver);
       objetappuye        = (option->state & QStyle::State_Sunken);

   QPen crayon = painter->pen();
       crayon.setWidth(eprcadre);
   plume->setPen(crayon);

   DessinerSymbole();
// texte info
    if(!LirePhraseInfo().isEmpty())
        plume->drawText( TourInfo(), Qt::AlignCenter, LirePhraseInfo() );

    plume->restore();
}
////************************************************************
////    Gestion des événements
////************************************************************
///******************* Routines QT ****************************/
void Element::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
//    ActualiserPosition();
    update();
}


////************************************************************
////    Virtuelles vides
////************************************************************
QString Element::LirePhraseInfo() const { return QString("");}
//void Element::StockerPosition(){}
//QString Element::LireNom(){ return QString("");}
void Element::DessinerSymbole(){}
