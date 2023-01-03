#include "ficbinbase.h"

ficbinbase::ficbinbase()
{
    adrenrg = NULL;
    NBOCTET = 0;
    posoctetadebutfic = 0;
}

ficbinbase::ficbinbase( const QString &nmfic, char* aenrg, ulong lgenrg )
{
    NomDuFichier.append( nmfic );
    adrenrg = aenrg;
    NBOCTET = lgenrg;
}

ficbinbase::ficbinbase( const QString &nmfic )// créer un fichier vide
{
    NomDuFichier.append( nmfic );
    QFile fichierencours;
    fichierencours.setFileName( NomDuFichier );
    fichierencours.open( QIODevice::WriteOnly );
    fichierencours.close();
}

ficbinbase::~ficbinbase(){}

qint64 ficbinbase::TailleFichier()
{
    QFile fichierencours;
    fichierencours.setFileName( NomDuFichier );
    qint64 taille=-1;
    if(fichierencours.exists())
        taille = fichierencours.size();
    fichierencours.close();
    return taille;
}

void ficbinbase::ReinitEnrg( const QString &nmfic,char* aenrg, ulong lgenrg )
{
    NomDuFichier = nmfic;
    ReinitEnrg( aenrg, lgenrg );
}

void ficbinbase::ReinitEnrg( char* aenrg, ulong lgenrg )
{
    adrenrg = aenrg;
    NBOCTET = lgenrg;
}


int ficbinbase::Ecrire()
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

int ficbinbase::REcrire()
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

bool ficbinbase::EcrireEnContinu()
{
    nboretour = fichiertraite.write( adrenrg, NBOCTET );
    return nboretour!=0;
}

bool ficbinbase::Existe()
{
        QFile fichierencours;
        fichierencours.setFileName( NomDuFichier );
        return fichierencours.exists();
}

int ficbinbase::Lire()
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

bool ficbinbase::OuvrirEnREcriture()
{
    if( NomDuFichier.isEmpty() ) return false;
    if( adrenrg == NULL ) return false;
    if( NBOCTET == 0 ) return false;
    fichiertraite.setFileName( NomDuFichier );
    return fichiertraite.open( QIODevice::WriteOnly );
}

bool ficbinbase::OuvrirEnAjoutEcriture()
{
    if( NomDuFichier.isEmpty() ) return false;
    if( adrenrg == NULL ) return false;
    if( NBOCTET == 0 ) return false;
    fichiertraite.setFileName( NomDuFichier );
    return fichiertraite.open( QIODevice::Append );
}

bool ficbinbase::OuvrirEnLecture()
{
    if( adrenrg == NULL ) return false;
    fichiertraite.setFileName( NomDuFichier );
    return fichiertraite.open( QIODevice::ReadOnly );
}

bool ficbinbase::LireEnContinu()
{
    nboretour = fichiertraite.read( adrenrg, NBOCTET );
    return nboretour!=0;
}
bool ficbinbase::LireOctetPointer()
{
    if(!PointerOctetCible()) return false;
    return LireEnContinu();
}
bool ficbinbase::LireEnrgNo(qint64 noenrg)
{
// le premier enregistrement est à la position octet 1
// noenrg est le numéro enrg est commence à 1
    if(noenrg==0) return false;
    noenrg--;
    OuvrirEnLecture();
    posoctetadebutfic = (noenrg*NBOCTET);
    bool toto = LireOctetPointer();
    FermerFichierContinu();
    return toto;
}
void ficbinbase::FermerFichierContinu(){    fichiertraite.close();}
bool ficbinbase::RePositionnerpointage( qint32 valeur )
{
    posoctetadebutfic = fichiertraite.pos()+valeur;
    if(posoctetadebutfic<0)
        posoctetadebutfic=0;

    return PointerOctetCible();
}
bool ficbinbase::PointerOctetCible(){    return fichiertraite.seek( posoctetadebutfic );}
int ficbinbase::ChercherChaine( const QString &valeur, qint64 debcherche, qint64& cptenr )
{
// cptenr : numéro d'enregistrement lu : de 1 à .....
    int typerr = 100104;
    ulong lgoct = 0;
    char* departlu = NULL;
    bool OkLecture = true;
    bool camarche = false;
    if( OuvrirEnLecture() )
    {
        departlu = adrenrg + debcherche;
        lgoct = valeur.size()+1;
        cptenr = 0;
        while (OkLecture)
        {
            if(fichiertraite.read( adrenrg, NBOCTET )!=0)
            {
                cptenr++;
                for ( ulong i=0; i<lgoct ; i++)
                {
                    if ( *(departlu+(i*2)) == *(valeur.data()+i) )
                        camarche = true;
                    else
                    {
                        camarche = false;
                        break;
                    }
                }
                if (camarche)
                    OkLecture = false;
            }
            else
                OkLecture = false;
        }
        FermerFichierContinu();
        if (camarche)
            typerr = 0;
        else
            typerr = -1;
    }
    else typerr = 100103;
    return typerr;
}

int ficbinbase::ChercherChaine( QChar *valeur, int taille, qint64 debcherche, qint64& cptenr )
{
    int typerr = 100104;
    ulong lgoct = 0;
    char* departlu = NULL;
    bool OkLecture = true;
    bool camarche = false;
    if( OuvrirEnLecture() )
    {
        departlu = adrenrg + debcherche;
        lgoct = taille+1;
        cptenr = 0;
        while (OkLecture)
        {
            if(fichiertraite.read( adrenrg, NBOCTET )!=0)
            {
                cptenr++;
                for ( ulong i=0; i<lgoct ; i++)
                {
                    if ( *(departlu+(i*2)) == *(valeur+i) )
                        camarche = true;
                    else
                    {
                        camarche = false;
                        break;
                    }
                }
                if (camarche)
                    OkLecture = false;
            }
            else
                OkLecture = false;
        }
        FermerFichierContinu();
        if (camarche)
            typerr = 0;
        else
            typerr = -1;
    }
    else typerr = 100103;
    return typerr;
}
bool ficbinbase::Etendre()
{
    if(volumeexpansion>0)
    {
        if(fichiertraite.open( QIODevice::Append ))
        {
            memset(&tampon[0],0,VALEURTAMPON);
            int nbpaquet = volumeexpansion/VALEURTAMPON;
            qint64 restepaquet = volumeexpansion - (nbpaquet*VALEURTAMPON);
            for(int i=0; i<nbpaquet;i++ )
                fichiertraite.write((char *)&tampon[0], VALEURTAMPON );
            if (restepaquet>0)
                fichiertraite.write((char *)&tampon[0], restepaquet );
            fichiertraite.close();
            return true;
        }
    }
    return false;
}
void ficbinbase::Decaler()
{
    if(posoctetadebutfic>0)
    {
        if(Etendre())
        {
            qint64 total = fichiertraite.size();
            if(fichiertraite.open( QIODevice::ReadWrite ))
            {
                int paquet      = total-posoctetadebutfic-volumeexpansion;
                int nbpaquet    = paquet/VALEURTAMPON;
                qint64 restepaquet = paquet-(nbpaquet*VALEURTAMPON);
                qint64  curseur = total-volumeexpansion;
                for(int i=0; i<nbpaquet;i++ )
                {
                    curseur -= VALEURTAMPON;
                    fichiertraite.seek(curseur);
                    NBOCTET = fichiertraite.read((char *)&tampon[0], VALEURTAMPON );
                    fichiertraite.seek(curseur+volumeexpansion);
                    fichiertraite.write((char *)&tampon[0], NBOCTET );
                }
                if(restepaquet>0)
                {
                    curseur -= restepaquet;
                    fichiertraite.seek(curseur);
                    NBOCTET = fichiertraite.read((char *)&tampon[0], restepaquet );
                    fichiertraite.seek(curseur+volumeexpansion);
                    fichiertraite.write((char *)&tampon[0], NBOCTET );
                }
                fichiertraite.close();
            }
        }
    }
}
qint64 ficbinbase::NboRetour(){return nboretour;}
