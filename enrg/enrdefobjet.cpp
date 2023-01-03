#include "enrdefobjet.h"

EnrDefObjet::EnrDefObjet(){Raz();}
EnrDefObjet::EnrDefObjet(const QString &valeur, qint32 vx, qint32 vy)
{
    Raz();
    Valeur( valeur, vx, vy );
}

QString EnrDefObjet::Nom() const {    return nom;}
qint32  EnrDefObjet::X(){    return posX;}
qint32  EnrDefObjet::Y(){    return posY;}

void EnrDefObjet::Valeur( const QString &valeur, qint32 vx, qint32 vy )
{
    Nom( valeur);
    X( vx );
    Y( vy );
}
void EnrDefObjet::Nom( const QString &valeur)
{
    nom.clear();
    nom.append(valeur);
}
void EnrDefObjet::X( qint32 valeur ){   posX = valeur;}
void EnrDefObjet::Y( qint32 valeur ){   posY = valeur;}

void EnrDefObjet::Raz()
{
    nom.clear();
    posX = 0;
    posY = 0;
}
