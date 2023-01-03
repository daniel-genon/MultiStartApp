#ifndef UTILFICBINBLOC_H
#define UTILFICBINBLOC_H
#include <qglobal.h>

bool EgalAvecTolerance( qreal v1, qreal v2, qreal tolerance=1 );
bool ValeurEntre( qreal vmin, qreal vmax, qreal vtest, qreal tolerance=1 );
void TransQstrVersStr( const QString &valeur, void * memdestinataire, int lgchaine=0 );

#endif // UTILFICBINBLOC_H
