#ifndef ENRDEFOBJET_H
#define ENRDEFOBJET_H

#include "../structuredemarreur.h"


class EnrDefObjet
{
public:

    EnrDefObjet();
    EnrDefObjet( const QString &valeur, qint32 vx, qint32 vy );

    QString Nom() const;
    qint32  X();
    qint32  Y();

    void Valeur( const QString &valeur, qint32 vx, qint32 vy );
    void Nom( const QString &valeur);
    void X( qint32 valeur );
    void Y( qint32 valeur );

    void Raz();

private :

    QString nom;// 80 cars max
    qint32  posX;// pour liaison : no du rang du source
    qint32  posY;// pour liaison : no du rang du cible

};

#endif // ENRDEFOBJET_H
