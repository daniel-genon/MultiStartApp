//-------------------------------------------------
// Project created by QtCreator
// Classe pour gestion de fichiers binaires accès direct et continu
// Daniel Génon avril 2010 Revin
// version : 5
//-------------------------------------------------
#ifndef FICBINBASE_H
#define FICBINBASE_H
#include <QFile>
#include <QStringList>

#ifndef VALEURTAMPON
 #define VALEURTAMPON 512
#endif

class ficbinbase
{
public:

    int	typerr;
    qint64  nboretour;
    qint64  posoctetadebutfic;//pointeur pour seek
    qint64  volumeexpansion;//taille pour expansion/retractation

    ficbinbase();
    ficbinbase( const QString &nmfic, char* aenrg, ulong lgenrg );
    ficbinbase( const QString &nmfic );// créer un fichier vide

    virtual ~ficbinbase();

//    Ouvrir/fermer fichier
    virtual bool OuvrirEnLecture();
    virtual bool OuvrirEnREcriture();
    virtual bool OuvrirEnAjoutEcriture();

    void FermerFichierContinu();

// Réinitialisation
    void ReinitEnrg( char* aenrg, ulong lgenrg );
    void ReinitEnrg( const QString &nmfic,char* aenrg, ulong lgenrg );

// opération d'écriture
    int Ecrire();// écrire à la suite
    int REcrire();// nouveau fichier
    virtual bool EcrireEnContinu();// ecrire dans un fichier ouvert

// opération de lecture
    int Lire();
    virtual bool LireEnContinu();
    bool LireOctetPointer();
    bool LireEnrgNo( qint64 noenrg );
    qint64  NboRetour();

// autres operations
    bool    Existe();
    bool    PointerOctetCible();
    bool    RePositionnerpointage( qint32 valeur );//replacer le curseur par rapport à sa position +-valeur

    bool Etendre();// ajoute "volumeexpansion" octets à la fin d'un fichier
    void Decaler();// décale des octets dans un fichier
                   // posoctetadebutfic et le point fixe et volumeexpansion estla valeur de décalage des infos

    qint64  TailleFichier();

// opération de positionnement
    int ChercherChaine( const QString &valeur, qint64 debcherche, qint64 &cptenr );
    int ChercherChaine( QChar *valeur, int taille, qint64 debcherche, qint64 &cptenr );

protected:

    QFile       fichiertraite;
    QString     NomDuFichier;
    char        tampon[VALEURTAMPON];

private:
    ulong		NBOCTET;
    char*		adrenrg;

};

#endif // FICBINBASE_H
