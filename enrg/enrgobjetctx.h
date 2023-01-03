#ifndef ENRGOBJETCTX_H
#define ENRGOBJETCTX_H

#include "enrdefobjet.h"
#include <QPointF>

class EnrgObjetCtx
{
public:

    EnrgObjetCtx();

    QString Nom() const;
    QString NomTravail() const;
    QString NomConfig() const;
    qint32  X();
    qint32  Y();
    qint32  XTravail();
    qint32  YTravail();
    qint32  XConfig();
    qint32  YConfig();
    quint8  Priorite();

    void ValeurObjet(const QString &valeur, qint32 vx, qint32 vy );
    void ValeurObjet(const QString &valeur, qint32 vx, qint32 vy, quint8 noprio );

    void ValeurObjetConnexion( qint32 vx, qint32 vy );

    void Travail(const QString &valeur, qint32 vx, qint32 vy );
    void Config(const QString &valeur, qint32 vx, qint32 vy );

    void Nom( const QString &valeur);
    void NomTravail( const QString &valeur);
    void NomConfig( const QString &valeur);
    void Priorite( quint8 valeur );
    void X( qint32 valeur );
    void Y( qint32 valeur );
    void XTravail( qint32 valeur );
    void YTravail( qint32 valeur );
    void XConfig( qint32 valeur );
    void YConfig( qint32 valeur );

    void PositionObjet( QPointF &retval );
    void PositionTravail( QPointF &retval );
    void PositionConfig( QPointF &retval );

    void Raz();

protected :

private :

    EnrDefObjet valeurobjet;
    EnrDefObjet travail;
    EnrDefObjet config;
    quint8      priorite;

};

#endif // ENRGOBJETCTX_H
