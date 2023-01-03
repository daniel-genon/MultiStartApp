#include "fictexte.h"

FicTexte::FicTexte()
{
    IniReste();
}

FicTexte::FicTexte( const QString &nmfic, QString *ptrligne )
{
    IniReste();
    NomDuFichier.append( nmfic );
    plignetmp =  ptrligne;
}

FicTexte::FicTexte( const QString &nmfic, QStringList *ptrlstligne )
{
    IniReste();
    NomDuFichier.append( nmfic );
    plstlignetmp =  ptrlstligne;
}

void FicTexte::IniReste()
{
    plignetmp=NULL;
    plstlignetmp=NULL;
    coefchaine = 2;
}

FicTexte::~FicTexte(){}

void FicTexte::ReInit( const QString &nmfic, QString *ptrligne )
{
    NomDuFichier.append( nmfic );
    plignetmp =  ptrligne;
}

bool FicTexte::OuvrirEnLecture()
{
    if( NomDuFichier.isEmpty() ) return false;
    fichiertraite.setFileName( NomDuFichier );
    return fichiertraite.open(QIODevice::ReadOnly | QIODevice::Text);
}

bool FicTexte::OuvrirEnAjoutEcriture()
{
    typerr = 100101;
    if( NomDuFichier.isEmpty() ) return 100130;
    if(( plignetmp == NULL )&&( plstlignetmp == NULL )) return 100102;
    fichiertraite.setFileName( NomDuFichier );
    if(fichiertraite.open( QIODevice::Append | QIODevice::Text))
       typerr=0;
    return typerr==0;
}

bool FicTexte::LireEnContinu()
{
    if(plignetmp==NULL) return false;
    if(fichiertraite.atEnd()) return false;
    *plignetmp = fichiertraite.readLine();
    *plignetmp = plignetmp->simplified();
    return true;
}

bool FicTexte::PointerLigne(ulong noligne)
{// ligne commence à 1, pas à 0
    ulong i = 1;
    do{
        if(fichiertraite.atEnd()) return false;
        *plignetmp = fichiertraite.readLine();
        i++;
    }while(i<noligne);
    *plignetmp = plignetmp->simplified();
    return true;
}

int FicTexte::Lire(ulong noligne)
{
    if(!OuvrirEnLecture()) return 100101;
    if(plignetmp==NULL) return 100102;
    if(!PointerLigne(noligne)) return 100210;
    FermerFichierContinu();
    return 0;
}

int FicTexte::Lire()
{
    int typerr = 100101;
    if(( plignetmp == NULL )&&( plstlignetmp == NULL )) return 100102;
    if(!OuvrirEnLecture()) return 100101;
    if(fichiertraite.atEnd()) return 100131;
    if(plignetmp != NULL)
    {
        typerr = 0;
        nboretour = fichiertraite.readLine( tampon, VALEURTAMPON );
        FermerFichierContinu();
        if(nboretour==0) return 100132;
        plignetmp->clear();
        plignetmp->append(QString((QChar *)&tampon));
    }
    if(plstlignetmp != NULL)
    {
        typerr = 0;
        while(!fichiertraite.atEnd())
        {
            memset(&tampon,0,VALEURTAMPON);
            nboretour = fichiertraite.readLine( tampon, VALEURTAMPON );
            plstlignetmp->append(QString((QChar *)&tampon).simplified());
        }
        FermerFichierContinu();
        if(plstlignetmp->isEmpty()) typerr = 100133;
    }
    return typerr;
}

int FicTexte::REcrireChaine()
{
    typerr = 100101;
    if(( plignetmp == NULL )&&( plstlignetmp == NULL )) return 100102;
    fichiertraite.setFileName( NomDuFichier );
    if(fichiertraite.open( QIODevice::WriteOnly | QIODevice::Text))
        EcrireValeur();

    fichiertraite.close();
    return typerr;
}

int FicTexte::EcrireChaine()
{
    typerr = 100101;
    if(( plignetmp == NULL )&&( plstlignetmp == NULL )) return 100102;
    fichiertraite.setFileName( NomDuFichier );
    if(fichiertraite.open( QIODevice::Append | QIODevice::Text))
        EcrireValeur();

    fichiertraite.close();
    return typerr;
}

bool FicTexte::EcrireEnContinu()
{
    typerr = 100101;
    if(( plignetmp == NULL )&&( plstlignetmp == NULL ))
        typerr = 100102;
    else
        EcrireValeur();
    return typerr==0;
}

void FicTexte::EcrireValeur()
{
    char fdl = 10;
    if(plignetmp != NULL)
    {
        nboretour = fichiertraite.write((char *) plignetmp->data(), plignetmp->length()*coefchaine );
        if( nboretour!=0 ) typerr = 0;
    }
    if(plstlignetmp != NULL)
    {
        for(int i=0;i<plstlignetmp->length();i++)
        {
            plignetmp = &plstlignetmp->operator [](i);
            nboretour = fichiertraite.write((char *) plignetmp->data(), plignetmp->length()*coefchaine );
            fichiertraite.putChar(fdl);
            if( nboretour!=0 ) typerr = 0;
        }
    }
}

