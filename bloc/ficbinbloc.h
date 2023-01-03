#ifndef ficbinDGBLOC_H
#define ficbinDGBLOC_H

#include "ficbinbase.h"
#include <QStringList>

struct EnrgBalise
{
    quint32   balise;
    quint32   taille;
};

struct EnrgEntete
{
    quint32   typestructure;// BLOC   = #424C4F43
    quint32   taillefichier;
    quint32   typefichier;//   gmao   = #676D416F
};

class ficbinDGBLOC  : public ficbinbase
{
public:

    int noerreur;

    ficbinDGBLOC();

    bool okfichier();
    virtual bool Initialiser( QString *cheminracine );
    virtual bool Initialiser( const QString &cheminracine );

protected:

    QList<QChar> lstptrchaine;

//    quint32   tailledereference;// utiliser pour lecture des enrg balise

    qint8   typecodec;// coef pour texte en unicode;
    quint32   valeurtaille;
    quint32   tailledereference;
    ulong tailleblocdata;

    quint32   nomliste;
    quint32   nomtype;
    quint32   nombalise;

    void EcrireEntete();
    void OuvrirListe();
    void OuvrirBalise();
    void OuvrirBalise( quint32 valeur, quint32 taille );
    void OuvrirEnrg();
    void EcrireData( const QString &valeur );
    bool EcrireBlocParticulier();

    void OuvrirEnrgBalise( quint32 nomdebalise, char *adrenrg, quint16 taille, bool ecrire=true );
    bool EcrireEnrgBalise();

    bool PointerDebutListe();
    bool LireEnrg();
    bool LireBloc();
    bool LireBlocParticulier();
    bool LireDataChaine();
    bool LireListe();
    bool LireEnrgBalise( quint32 nomdebalise, char *adrenrg );
    bool LireEnrgBalise();

    void EcrireEnteteFichier( bool FACancien = false);
    void FermerFichierOuvert();

    bool PointerProchainEnrg();
    bool PointerProchainNomListe();
    bool PointerProchaineBalise();
    bool RetourPointageDeBloc();

    bool OkNomListe();

    quint32 TailleNomListe();
    quint32 TailleBlocData();

    bool Modifier();
    bool RemplacerBloc();
    bool ReEcrireBloc();

    QString ValeurChaine() const;
    void RecupererChaine( QString &cible, qint8 *psource );

    void InitBlocParticulier ( char *adrenrg );

    virtual void CreerNomFichier();
    virtual bool Ecrire( bool FACancien = false );
    virtual void EcrireLesBlocs();
    virtual void EcrirePreBalise();
    virtual bool PointerObjet();

    QString phrtest;

private:

    qint8 tamponchaine[2048];

    EnrgEntete  entete;
    EnrgBalise  baliselist;
    EnrgBalise  blocdata;
    EnrgBalise  blocenrg;
    EnrgBalise  blocnomlist;

    ulong taillebaliselist;

    quint32 nomriff;
    quint32 nombornelist;
    quint32 nomenrg;

    quint32 differencedetaille;


    char    *adrenrgparticulier;

    void    InitEnrgListe();
    void    InitEnrgNomListe();
    void    InitEnrgBloc();
    void    InitEnrgEnrg();
    void    InitTamponChaine();

    int     LireEntete();
    void    PasserListeSuivante();

    bool    Superposer();

};

#endif // ficbinDGBLOC_H
