#ifndef FICHIERCONFIGURATION_H
#define FICHIERCONFIGURATION_H

#include "fichier.h"

class FichierConfiguration : public Fichier
{
public:
    FichierConfiguration();
    FichierConfiguration(ConfigurationObjet *ptrconf , const EnrgFichier &valeur);

    void CollationnerDescripteur(EnrgObjetCtx *retval );

private:
    void InitFicCfg();
};

#endif // FICHIERCONFIGURATION_H
