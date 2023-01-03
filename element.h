#ifndef ELEMENT_H
#define ELEMENT_H

#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

class Element : public QGraphicsItem
{
public:

    Element();

    void InitIcone(const QString &phricone);

    int  GenreElement()  const;
    QString NomElement() const;
    bool EstUnLogiciel();

    void PositionDansScene(int &valx, int &valy );
    int PositionXDansScene();
    int PositionYDansScene();
    int Largeur() const;
    int Hauteur() const;
    void AnnulerCartouche();
    int HauteurElement() const;
    int LargeurElement() const;
    QImage ImageIcone() const;
    void Dimensions( qreal &large, qreal &haut );
    QPointF PointDeContact( int idx );

protected:


    bool objetselectionne;
    bool objetenmouvement;
    bool objetappuye;

    int valgra3;//htcartouche;
    int valgra1;
    int valgra2;

    QPainter *plume;

    void GenreElement(int valeur );
    void NomElement(const QString &valeur);
    void EntrerValeurGraph(const int val1, const int val2 );

    QRectF TourFeuille() const;
    QRectF TourInfo() const;
    void DessinerIcone();


    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

// virtuelles vides
    virtual void DessinerSymbole();
    virtual QString LirePhraseInfo() const;

private :

    int genre;// 100=logiciel  1000=ancre (graphtemporaire)


    int eprcadre;
    int margeicone;
    int hticone;
    int lgicone;

    QImage icoelement;

    QString nomelement;
//    QString nomgenre;

//    QPoint  ancrage[4];//0:pbas 1:pdrt 2:phaut 3:pgah

//    void    DessinerCartouche(QPainter *painter);
//    QRectF TourCartouche() const;

};

#endif // ELEMENT_H
