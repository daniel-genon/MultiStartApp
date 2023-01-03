#include "enrgancre.h"

/*
    Structure de données pour graphique ancre
*/

EnrgAncre::EnrgAncre(){}
EnrgAncre::EnrgAncre( const QString &vico,
          const QString &vcofon,
          const EnrgPolice &vpoli,
          quint8  vlar,
          quint8  vhau )
{    Valeur( vico, vcofon, vpoli, vlar, vhau );}
void EnrgAncre::Valeur( const EnrgAncre &autre )
{
    EntrerValeurGraph( autre.Largeur(), autre.Hauteur() );
    Couleurs( autre.SCouleurBandeau(), autre.SCouleurFond() );
    Police ( autre.Police() );
    imicone     = autre.Icone();
}
void EnrgAncre::Standard()
{
    EnrgPolice policetmp("Bitstream Charter","#000000",4);
    EntrerValeurGraph( 54, 64 );
    Couleurs( "#baddf2", "#baddf2" );
    Police ( policetmp );
    imicone     = ":/icone/attache.png";
}
void EnrgAncre::Valeur(  const QString &vico,
              const QString &vcofon,
              const EnrgPolice &vpoli,
              quint8  vlar,
              quint8  vhau )
{
    EntrerValeurGraph( vlar, vhau );
    Couleurs( vcofon, vcofon );
    Police ( vpoli );
    if(!vico.isEmpty())
        imicone = vico;
}

//void EnrgAncre::Icone( const QString &valeur){imicone = valeur;}

//QString EnrgAncre::Nom() const{return "ancrage";}
//quint16 EnrgAncre::Famille() const{return 999;}
//QString EnrgAncre::NomClair() const{return "ANCRE";}

QString EnrgAncre::Icone() const{return imicone;}

bool EnrgAncre::EgaleA(const EnrgAncre &autre )
{
    if(QString::compare(imicone,autre.Icone(),Qt::CaseInsensitive)!=0) return false;
//    if(imicone.operator != (autre.Icone())) return false;
    return GraphiqueSurface::EgaleA(autre);
}

void EnrgAncre::CopierVersBloc( BlocAncre &cible )
{
    GraphiqueSurface::CopierVersBloc(cible.Bsymbole);
    TransQstrVersStr( imicone, &cible.imicone );
}
void EnrgAncre::CopierDepuisBloc( const BlocAncre &source )
{
    GraphiqueSurface::CopierDepuisBloc(source.Bsymbole);
    imicone = QString((QChar *)&source.imicone);
}
