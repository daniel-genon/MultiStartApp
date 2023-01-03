#ifndef GERERSESSION_H
#define GERERSESSION_H

#include <QProcessEnvironment>
#include "bloc/fblocsessionmultiapp.h"
#include "bloc/fblocprojetmapp.h"
#include <QRect>

class GererSession
{
public:
    int noerreur;

    GererSession();

    QString NomDuProjet() const;
    QString NomDuContexte() const;
    QString NomUtilisateur() const;
    QString NomConfiguration() const;

    QString CheminRacine() const;
    QString CheminStandard() const;
    QString *ptrCheminRacine();
    QString CheminProjet() const;
    QString CheminContexte() const;

    QString LibelleErreur() const;


    bool oksession();
    bool okboite();
    void Enregistrer();
    int  ChargerPremierProjetEtContexte();
    void ChangerConfiguration( const QString &valeur );


    void OuvrirUnContexte();
    void CreerNouveauProjet();
    void CreerNouveauContexte();

    void SauverEnrgProjet();
    void RestaurerEnrgProjet();
    void ReserverEnrgProjet();
    void RetablirEnrgProjet();

//    QRect *LireDimFenetre();
//    void EcrireDimFenetre(const QRect &valeur);
    FBlocContexte *pFichierContexte();

private:

    QString phrtmp;
    QString cheminhome;// chemin du home de l'utilisateur
    QString cheminracine;// chemin du repertoire de multiapp

    EnrgSessionProjet Enrsesproj;
    EnrgSessionProjet SVDEnrsesproj;
    EnrgSessionProjet RESEnrsesproj;

    FBlocSessionMultiApp    fichiersession;
    FBlocProjetMApp         fichierprojet;


    bool ChargerSession();
    void CreerRepertoire();
    void CreerCheminParDefaut();
    void VerifierRepertoire();
    void CreerEnvironnementProjet();
    void DetruireProjet();
};

#endif // GERERSESSION_H
