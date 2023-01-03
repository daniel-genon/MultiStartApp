#include "ficbin.h"

ficbin::ficbin()
{
    taille = 0;
    fichierexiste = false;
    adrenrg = NULL;
    NBOCTET = 0;
}

ficbin::ficbin( const QString &nmfic, char* aenrg, ulong lgenrg )
{
    NomDuFichier.append( nmfic );
    adrenrg = aenrg;
    NBOCTET = lgenrg;
}

ficbin::ficbin( const QString &nmfic ){    NomDuFichier.append( nmfic );}

ficbin::~ficbin(){}

bool ficbin::Statistique()
{
    QFile fichierencours;
    fichierencours.setFileName( NomDuFichier );
    if(fichierencours.exists())
    {
        fichierexiste = true;
        taille = fichierencours.size();
    }
    else
    {
        fichierexiste = false;
        taille = 0;
    }
    fichierencours.close();

    return fichierexiste;
}

qint64 ficbin::TailleFichier(){    return taille;}
bool ficbin::FichierExiste(){    return fichierexiste;}

void ficbin::ReinitEnrg( char* aenrg, ulong lgenrg )
{
    adrenrg = aenrg;
    NBOCTET = lgenrg;
}

int ficbin::Ecrire()
{
    int typerr = 100102;
    if( adrenrg != NULL )
    {
        QFile fichierencours;
        fichierencours.setFileName( NomDuFichier );
        if(fichierencours.open( QIODevice::Append ))
        {
            nboretour = fichierencours.write( adrenrg, NBOCTET );
            if( nboretour!=0 ) typerr = 0;
        }
        fichierencours.close();
    } else typerr = 100103;
    return typerr;
}

int ficbin::REcrire()
{
    int typerr = 100101;
    if( adrenrg != NULL )
    {
        QFile fichierencours;
        fichierencours.setFileName( NomDuFichier );
        if(fichierencours.open( QIODevice::WriteOnly ))
        {
            nboretour = fichierencours.write( adrenrg, NBOCTET );
            if( nboretour!=0 ) typerr = 0;
        }
        fichierencours.close();
    } else typerr = 100103;
    return typerr;
}

int ficbin::CollerDerriere( const QString &nomdurajout )
{
    char listoctet[2048];
    char* penrg = &listoctet[0];

    size_t NOCTET = 0;
    LgCopie	= 0;

    if( nomdurajout.compare( NomDuFichier  )==0) return 100114;

    QFile fichiertemporaire;
    QFile fichierencours;

    fichiertemporaire.setFileName(nomdurajout);
    fichierencours.setFileName( NomDuFichier );

    if(fichiertemporaire.open( QIODevice::ReadOnly ))
    {
        if(fichierencours.open(QIODevice::Append))
        {
            typerr=0;
            while((NOCTET=fichiertemporaire.read( penrg, 2048))!=0)
            {
                nboretour = fichierencours.write( penrg, NBOCTET );
                if(nboretour==0) { typerr=100100; break;}
                LgCopie += NOCTET;
            }
            fichierencours.close();
        }
        else typerr=100101;

        fichiertemporaire.close();
    }
    else
        typerr=100104;

    return typerr;
}

int ficbin::Lire()
{
    int typerr = 100102;
    if( adrenrg != NULL )
    {
        QFile fichierencours;
        fichierencours.setFileName( NomDuFichier );
        if(fichierencours.open( QIODevice::ReadOnly ))
        {
            nboretour = fichierencours.read( adrenrg, NBOCTET );
            if( nboretour!=0 ) typerr = 0;
        }
        fichierencours.close();
    } else typerr = 100103;
    return typerr;
}
