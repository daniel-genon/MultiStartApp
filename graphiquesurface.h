#ifndef GRAPHIQUESURFACE_H
#define GRAPHIQUESURFACE_H

#include "element.h"
#include "enrg/enrggraph.h"

class GraphiqueSurface : public Element
{
public:

    GraphiqueSurface();

    void Couleurs( const QString &coulband, const QString &coulfond );
    void Police (const EnrgPolice &pol );
    void CouleurConnexion( const QString &valeur );

    QColor CouleurFond() const;
    QColor CouleurBandeau() const;
    QString SCouleurFond() const;
    QString SCouleurBandeau() const;
    EnrgPolice Police() const;
    EnrgPolice *PPolice();

    bool EgaleA(const GraphiqueSurface &autre );
    void CopierVersBloc( BlocSymbole &cible );
    void CopierDepuisBloc( const BlocSymbole &source );


protected:

    QRectF TourCartouche() const;

    virtual void DessinerSymbole();


//************************* vituelles vides *****************
    virtual void EcrireTitre();
    virtual void EcrireNom();


private:

    QColor couleurbandeau;
    QColor couleurfond;

    EnrgPolice vpolice;

    //    QPoint  ancrage[4];//0:pbas 1:pdrt 2:phaut 3:pgah

    void    DessinerCartouche();
    //    QRectF TourInfo() const;

};

#endif // GRAPHIQUESURFACE_H
