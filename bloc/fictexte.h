#ifndef fictexte_H
#define fictexte_H

#include "ficbinbase.h"

class FicTexte : public ficbinbase
{
public:

    QString  *plignetmp;
    QStringList  *plstlignetmp;

    FicTexte();
    FicTexte( const QString &nmfic, QString *ptrligne );
    FicTexte( const QString &nmfic, QStringList *ptrlstligne );
    virtual ~FicTexte();

// reinitialisation
    void ReInit( const QString &nmfic, QString *ptrligne );
//    Ouvrir fichier
    virtual bool  OuvrirEnLecture();
    virtual bool  OuvrirEnAjoutEcriture();

// opération de lecture
    virtual bool LireEnContinu();
    virtual int Lire();

    int Lire(ulong noligne);
// opération écriture
    int REcrireChaine();
    int EcrireChaine();
    virtual bool EcrireEnContinu();

protected:
    int coefchaine;//pour modifier nb car (unicode)


private:

    bool PointerLigne(ulong noligne);
    void IniReste();
    void EcrireValeur();


};

#endif // fictexte_H
