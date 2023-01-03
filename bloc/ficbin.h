//-------------------------------------------------
// Project created by QtCreator
// Classe pour gestion de fichiers binaires séquentiels
// Daniel Génon mars 2010 Revin
// version : 2
//-------------------------------------------------
#ifndef FICBIN_H
#define FICBIN_H
#include <QFile>
#include <QString>
class ficbin
{
public:

    int	typerr;
    qint64  nboretour;

    ficbin();
    ficbin( const QString &nmfic, char* aenrg, ulong lgenrg );
    ficbin( const QString &nmfic );
    virtual ~ficbin();

// Réinitialisation
    void ReinitEnrg( char* aenrg, ulong lgenrg );

// opération d'écriture
    int Ecrire();// écrire à la suite
    int REcrire();// nouveau fichier
    int CollerDerriere( const QString &nomdurajout );// abouter un fichier à la suite

// opération de lecture
    int Lire();

// autres operations
    bool    Statistique();
    bool    FichierExiste();
    qint64  TailleFichier();

private:
    bool        fichierexiste;
    qint64      taille;
    QString     NomDuFichier;
    ulong		NBOCTET;
    ulong		LgCopie;
    char*		adrenrg;
};

#endif // FICBIN_H
