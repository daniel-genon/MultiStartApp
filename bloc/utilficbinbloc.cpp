#include <QtCore>
#include "utilficbinbloc.h"

bool EgalAvecTolerance( qreal v1, qreal v2, qreal tolerance )
{
    if(v1>(v2+tolerance)) return false;
    if(v1<(v2-tolerance)) return false;
    return true;
}

bool ValeurEntre( qreal vmin, qreal vmax, qreal vtest, qreal tolerance )
{
    if(vtest<(vmin-tolerance)) return false;
    if(vtest>(vmax+tolerance)) return false;
    return true;
}

void TransQstrVersStr( const QString &valeur, void * memdestinataire, int lgchaine )
{
    int taille = valeur.size();
    if(lgchaine!=0)
    {
        if(taille>lgchaine)
            taille=lgchaine;
    }
    memcpy( memdestinataire, valeur.data(),2*taille);// 2 pour unicode
}
