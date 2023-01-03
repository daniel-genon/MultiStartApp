#include "enrgobjetctx.h"

EnrgObjetCtx::EnrgObjetCtx()
{
    Raz();
}

QString EnrgObjetCtx::Nom() const { return (valeurobjet.Nom()); }
QString EnrgObjetCtx::NomTravail() const { return (travail.Nom()); }
QString EnrgObjetCtx::NomConfig() const { return (config.Nom()); }
quint8  EnrgObjetCtx::Priorite() { return priorite;}

qint32  EnrgObjetCtx::X(){ return valeurobjet.X();}
qint32  EnrgObjetCtx::XTravail(){ return travail.X();}
qint32  EnrgObjetCtx::XConfig(){ return config.X();}

qint32  EnrgObjetCtx::Y(){ return valeurobjet.Y();}
qint32  EnrgObjetCtx::YTravail(){ return travail.Y();}
qint32  EnrgObjetCtx::YConfig(){ return config.Y();}

void EnrgObjetCtx::PositionObjet( QPointF &retval )
{
    retval.setX( X() );
    retval.setY( Y() );
}
void EnrgObjetCtx::PositionTravail( QPointF &retval )
{
    retval.setX( XTravail() );
    retval.setY( YTravail() );
}
void EnrgObjetCtx::PositionConfig( QPointF &retval )
{
    retval.setX( XConfig() );
    retval.setY( YConfig() );
}

void EnrgObjetCtx::ValeurObjet(const QString &valeur, qint32 vx, qint32 vy )
{
    valeurobjet.Valeur( valeur, vx, vy );
}
void EnrgObjetCtx::ValeurObjet(const QString &valeur, qint32 vx, qint32 vy, quint8 noprio )
{
    valeurobjet.Valeur( valeur, vx, vy );
    priorite = noprio;
}
void EnrgObjetCtx::ValeurObjetConnexion( qint32 vx, qint32 vy )
{
    ValeurObjet("connexion", vx, vy );
}


void EnrgObjetCtx::Travail(const QString &valeur, qint32 vx, qint32 vy ){    travail.Valeur( valeur, vx, vy );}
void EnrgObjetCtx::Config(const QString &valeur, qint32 vx, qint32 vy ){    config.Valeur( valeur, vx, vy );}

void EnrgObjetCtx::Nom( const QString &valeur){    valeurobjet.Nom(valeur);}
void EnrgObjetCtx::NomTravail( const QString &valeur){    travail.Nom(valeur);}
void EnrgObjetCtx::NomConfig( const QString &valeur){    config.Nom(valeur);}
void EnrgObjetCtx::Priorite( quint8 valeur){ priorite=valeur;}

void EnrgObjetCtx::X( qint32 valeur ){  valeurobjet.X(valeur);}
void EnrgObjetCtx::XTravail( qint32 valeur ){  travail.X(valeur);}
void EnrgObjetCtx::XConfig( qint32 valeur ){  config.X(valeur);}

void EnrgObjetCtx::Y( qint32 valeur ){  valeurobjet.Y(valeur);}
void EnrgObjetCtx::YTravail( qint32 valeur ){  travail.Y(valeur);}
void EnrgObjetCtx::YConfig( qint32 valeur ){  config.Y(valeur);}


void EnrgObjetCtx::Raz()
{
    valeurobjet.Raz();
    travail.Raz();
    config.Raz();
    priorite=127;
}
