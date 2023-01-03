#ifndef ENRGGRAPH_H
#define ENRGGRAPH_H

#include "../structuredemarreur.h"
#include "enrgpolice.h"

class EnrgGraph
{
public:

    EnrgGraph();
    EnrgGraph( const QString &vnom,
               const QString &vcf,
               const QString &vcb,
               const EnrgPolice &vpol,
               quint8 vlar, quint8 vhau, quint8 vprio );

    void Valeur(const QString &vnom,
                       const QString &vcf,
                       const QString &vcb,
                       const EnrgPolice &vpol,
                       quint8 vlar, quint8 vhau, quint8 vprio);

    void Valeur( const EnrgGraph &autre );
    void Valeur( const EnrgGraph *autre );

    void Nom( const QString &valeur);
    void Priorite( quint8 valeur );
    void Hauteur( quint8 valeur );
    void Largeur( quint8 valeur );
    void DimSymbole( quint8 htr, quint8 lgr );
    void CouleurFond( const QString &valeur);
    void CouleurBandeau( const QString &valeur);
    void Police( const EnrgPolice &valeur );


    QString Nom() const;
    QString CouleurFond() const;
    QString CouleurBandeau() const;
    quint8  Hauteur() const;
    quint8  Largeur() const;
    quint8  Priorite() const;
    EnrgPolice Police() const;

    QString *PtrCouleurFond();
    QString *PtrCouleurBandeau();
    EnrgPolice *PPolice();

    bool EgaleA(const EnrgGraph *autre , bool testnom=true);
    void CopierVersBloc( BlocGraph &cible );
    void CopierDepuisBloc( const BlocGraph &source );

private :

    QString libelle;
    quint8  priorite;
    quint8  htsymbole;
    quint8  lgsymbole;
    QString coulfond;
    QString coulband;
    EnrgPolice police;


};

typedef EnrgGraph *ptrenrgraphique;

class LstEnrgGraph : public QList<ptrenrgraphique>
{
public:

    LstEnrgGraph();
    LstEnrgGraph( ptrenrgraphique nouveau);
    ~LstEnrgGraph();

    void Ajouter( const QString &vlibelle,
                const QString &vcoulfond,
                const QString &vcoulband,
                const EnrgPolice &vpolice,
                quint8 vlg, quint8 vht, quint8 vprio );

    void Ajouter( const BlocGraph &source );
    void CopierSimple(const LstEnrgGraph &source); // les pointeurs sont inchangés, toute modif
                                                    // affecte les valeurs de l'enrg
    void Copier(const LstEnrgGraph &source);   // De nouveaux objets sont copiés sur les pointeurs
                                                // les modifs n'influent pas sur l'objet original
    bool EgaleA(const LstEnrgGraph &autre, bool testnom=true);

    void Nettoyer();

    virtual void Standard();

};




class LstEnrgGrLog : public LstEnrgGraph
{
public:
    LstEnrgGrLog();
    virtual void Standard();
};


class LstEnrgGrFic : public LstEnrgGraph
{
public:
    LstEnrgGrFic();
    virtual void Standard();
};















#endif // ENRGGRAPH_H
