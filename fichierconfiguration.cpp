#include "fichierconfiguration.h"

FichierConfiguration::FichierConfiguration()
{
    cfgobjet = NULL;
    InitFicCfg();
}
FichierConfiguration::FichierConfiguration(ConfigurationObjet *ptrconf , const EnrgFichier &valeur )
{
    Entrer(valeur);
    cfgobjet = ptrconf;
    InitFicCfg();
}
void FichierConfiguration::InitFicCfg()
{
    GenreElement( 200 );
    NomElement("fichier configuration");
    if(cfgobjet!=NULL)
    {
        if(cfgobjet->PointerCfg())
        {
            InitFichier();
            InitIcone(":/icone/ficcfg.png");
        }
    }
}
void FichierConfiguration::CollationnerDescripteur( EnrgObjetCtx *retval )
{
    retval->Config( NomFichier(false)  , PositionXDansScene(), PositionYDansScene());
}
