#ifndef FICHIERTRAVAIL_H
#define FICHIERTRAVAIL_H

#include "fichier.h"

class FichierTravail : public Fichier
{
public:

    FichierTravail();
    FichierTravail(ConfigurationObjet *ptrconf, const EnrgFichier &valeur  );


    void CollationnerDescripteur( EnrgObjetCtx *retval );

private:


    void InitFicTrv();

};

#endif // FICHIERTRAVAIL_H
