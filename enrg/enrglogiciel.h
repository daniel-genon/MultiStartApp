#ifndef ENRGLOGICIEL_H
#define ENRGLOGICIEL_H

#include "../structuredemarreur.h"
#include <QList>

class EnrgLogiciel
{
public:
    EnrgLogiciel();
    EnrgLogiciel( const EnrgLogiciel &autre );
    EnrgLogiciel( const QString &vnom,
                  const QString &vcla,
                  const QString &vopt,
                  const QString &vaid,
                  const QString &vdos,
                  const QString &vico,
                  const QString &vdep, quint8 vdelai, quint8 vuni, quint8 vclas ,
                  const QString &vstcfg, const QString &vsttrv,
                  const QString &opcfg, const QString &optrv  );

    void Valeur(  const EnrgLogiciel *pautre );
    void Valeur(  const EnrgLogiciel &autre );
    void Valeur(  const QString &vnom,
                  const QString &vcla,
                  const QString &vopt,
                  const QString &vaid,
                  const QString &vdos,
                  const QString &vico,
                  const QString &vdep, quint8 vdelai, quint8 vuni, quint8 vclas,
                  const QString &vstcfg, const QString &vsttrv,
                  const QString &opcfg, const QString &optrv );

    void NomProcessus( const QString &valeur);
    void NomClair( const QString &valeur);
    void Options( const QString &valeur);
    void Aide( const QString &valeur);
    void Dossier( const QString &valeur);
    void Icone( const QString &valeur);
    void Delai( quint8 valeur);
    void Unique( quint8 valeur);
    void Classe( quint8 valeur);
    void Unique( bool valeur);
    void Dependance( const QString &valeur);
    void StdCFG( const QString &valeur);
    void StdTRV( const QString &valeur);
    void OptCFG( const QString &valeur);
    void OptTRV( const QString &valeur);


        QString NomProcessus() const;
        QString NomClair() const;
        QString Options() const;
        QString Aide() const;
        QString Dossier() const;
        QString Icone() const;
        quint8  Delai() const;
        quint8  Unique() const;
        quint8  Classe() const;
        bool    UniqueB();
        QString Dependance() const;
        QString StdTRV() const;
        QString StdCFG() const;
        QString OptTRV() const;
        QString OptCFG() const;

        bool EgaleA( const EnrgLogiciel &autre );
        bool EgaleA(const EnrgLogiciel *autre , bool testnom=true);

    void CopierVersBloc( BlocLogiciel &cible );
    void CopierDepuisBloc( const BlocLogiciel &source );


private:

    QString    nomprocessus;// nom du programme ?? lancer ex:gedit
    QString    nomclair;// nom explicite du processus ex : ??diteur
    QString    options;// options de le ligne de commande (sans nom de fichier config ou travail
    QString    phraide;
    QString    dosproc;// dossier o?? se trouve le programme
    QString    dependance;// nom des "process" qui d??pendent de ce programme
    quint8     delai;// d??lai apr??s le lancement pour lancer un autre processus
    quint8     unique;// si "true" il n'existe qu'un process de ce programme

    QString    imicone;// nom de l'image icone stock??e dans un r??pertoire multiapp
    quint8     classe;// de 1 ?? 8 : d??fini la colonne menu o?? sera affich?? l'icone du logiciel

    QString    stdcfg;// nom du fichier standard pour la configuration
    QString    stdtrv;// nom du fichier standard pour le travail
    QString    optcfg;// option pour introduire fichier config
    QString    opttrv;// option pour introduire fichier travail


};

typedef EnrgLogiciel *ptrenrglogiciel;


class LstEnrgLogiciel : public QList<ptrenrglogiciel>
{
public:

    LstEnrgLogiciel();
    LstEnrgLogiciel( ptrenrglogiciel nouveau );
    ~LstEnrgLogiciel();

    void Ajouter(const QString &vnom,
                  const QString &vcla,
                  const QString &vopt,
                  const QString &vaid,
                  const QString &vdos,
                  const QString &vico,
                  const QString &vdep,
                  quint8 vdelai, quint8 vuni , quint8 vclas,
                 const QString &vstcfg, const QString &vsttrv,
                 const QString &opcfg, const QString &optrv );

    void Ajouter( const BlocLogiciel &source);
    void CopierSimple(const LstEnrgLogiciel &source);// les pointeurs sont inchang??s, toute modif
                                                    // affecte les valeurs de l'enrg
    void Copier(const LstEnrgLogiciel &source);// De nouveaux objets sont copi??s sur les pointeurs
                                                // les modifs n'influent pas sur l'objet original
    bool EgaleA( const LstEnrgLogiciel &autre, bool testnom=true);
    void Nettoyer();

    void Standard();

};

#endif // ENRGLOGICIEL_H
