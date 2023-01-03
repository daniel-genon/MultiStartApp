#include "graphiquesurface.h"

GraphiqueSurface::GraphiqueSurface()
{
//    genre       = 999;
//    famille     = 999;
//    nomfamille = "inconnu";
//    nomgenre = "inconnu";
    couleurbandeau  = Qt::yellow;
    couleurfond     = Qt::blue;
    vpolice.Valeur("Times", "black", 8 );
}



void  GraphiqueSurface::Couleurs(const QString &coulband, const QString &coulfond )
{
    couleurbandeau.setNamedColor(coulband);
    couleurfond.setNamedColor(coulfond);
}

void  GraphiqueSurface::Police (const EnrgPolice &pol )
{
    vpolice.Valeur(pol);
    valgra3 = vpolice.Hauteur()*1.5;
}
void GraphiqueSurface::CouleurConnexion(const QString &valeur){couleurfond.setNamedColor(valeur);}
QColor GraphiqueSurface::CouleurFond() const{return couleurfond;}
QColor GraphiqueSurface::CouleurBandeau() const{return couleurbandeau;}
QString GraphiqueSurface::SCouleurFond() const { return couleurfond.name(); }
QString GraphiqueSurface::SCouleurBandeau() const { return couleurbandeau.name(); }
EnrgPolice *GraphiqueSurface::PPolice(){ return &vpolice;}
EnrgPolice GraphiqueSurface::Police() const { return vpolice;}

bool GraphiqueSurface::EgaleA( const GraphiqueSurface &autre )
{
    if(Hauteur()!=autre.Hauteur()) return false;
    if(Largeur()!=autre.Largeur()) return false;
    if(QString::compare(SCouleurFond(),autre.SCouleurFond(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(SCouleurBandeau(),autre.SCouleurBandeau(),Qt::CaseInsensitive)!=0) return false;
    return vpolice.EgaleA(autre.Police());
}

void GraphiqueSurface::CopierVersBloc( BlocSymbole &cible )
{
    vpolice.CopierVersBloc(cible.Bpolice);
    TransQstrVersStr( SCouleurFond(), &cible.Bcoulf );
    TransQstrVersStr( SCouleurBandeau(), &cible.Bcoulb );
    cible.Bentier1  = Largeur();
    cible.Bentier2  = Hauteur();
}
void GraphiqueSurface::CopierDepuisBloc(const BlocSymbole &source )
{
    Couleurs(QString((QChar *)&source.Bcoulb),QString((QChar *)&source.Bcoulf));
    vpolice.CopierDepuisBloc(source.Bpolice);
    EntrerValeurGraph( source.Bentier1, source.Bentier2 );
}




// ****************** Routine graphisue perso  *********************
QRectF GraphiqueSurface::TourCartouche() const
{
    return QRectF(-valgra1, -valgra2-(int)valgra3/2, valgra1*2, valgra3);
}

void GraphiqueSurface::DessinerCartouche()
{
    QColor couleursymbole(couleurbandeau);
    if(objetselectionne)    couleursymbole = couleursymbole.darker(150);// assombrir;
    if(objetenmouvement)    couleursymbole = couleursymbole.lighter(125);// éclairer;
    QBrush pinceau = plume->brush();
        pinceau.setStyle(Qt::SolidPattern);
        pinceau.setColor(couleursymbole);
    plume->setBrush(pinceau);
    plume->drawRect(TourCartouche());
// texte cartouche
    plume->setPen(QPen(QColor(Qt::black), 0));
    QFont font( "Times", 8 );
    font.setFamily(vpolice.Nom());
    font.setPixelSize(vpolice.Hauteur());
    font.setStyleStrategy(QFont::ForceOutline);
        plume->setPen(QPen(QColor(vpolice.Couleur()), 0));
        plume->setFont(font);
        plume->scale(1, 1);
        EcrireNom();
}

void GraphiqueSurface::DessinerSymbole()
{
    if(valgra3!=0) DessinerCartouche();
    QColor couleursymbole(couleurfond);
    Qt::BrushStyle  typefond = Qt::SolidPattern;

    QBrush pinceau = plume->brush();
       pinceau.setStyle(typefond);
       pinceau.setColor(couleursymbole);
    plume->setBrush(pinceau);
    plume->drawRect( TourFeuille() );

    DessinerIcone();

// texte symbole
    plume->setPen(QPen(QColor(Qt::black), 0));
    QFont font( "Times", 8 );
    font.setFamily(vpolice.Nom());
    font.setPixelSize(vpolice.Hauteur());
    font.setStyleStrategy(QFont::ForceOutline);
    plume->setPen(QPen(QColor(vpolice.Couleur()), 0));
        plume->setFont(font);
        plume->scale(1, 1);
    EcrireTitre();
}


void GraphiqueSurface::EcrireTitre(){}
void GraphiqueSurface::EcrireNom(){}
