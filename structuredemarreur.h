#ifndef STRUCTUREDEMARREUR_H
#define STRUCTUREDEMARREUR_H

#define MTLIG  3 // nombre de ligne configurées dans enrgconnexion.h

#include "bloc/utilficbinbloc.h"
#include <QStringList>

typedef qint8 CouleurBloc[16];
typedef qint8 NomPolice[255];

struct EnrgDate{
    qint32 j;
    qint32 m;
    qint32 a;
};

struct EnrgProjet{
    QString     nom;
    EnrgDate    dcreation;
    QStringList lstcontexte;
    QString     commentaire;
};

struct EnrgSessionProjet{
    QString     utilisateur;
    QString     nom;
    EnrgDate    dcreation;
    EnrgDate    dmodifsession;
    EnrgDate    dmodifcontexte;
    EnrgProjet  projet;
    QString     configuration;
    QString     commentcontxt;
};

struct BlocPolice{
    NomPolice   nompol;
    CouleurBloc coulpol;
    quint8        hautpol;
};

struct BlocSymbole{
    BlocPolice  Bpolice;
    quint8        Bentier1;
    quint8        Bentier2;
    CouleurBloc Bcoulf;
    CouleurBloc Bcoulb;
};

struct BlocBaseGraph{
    BlocSymbole Bsymbole;
    qint8        Bchaine[80];
    CouleurBloc Bcouleur;
};

struct BlocGraph{
    qint8 libelle[40];
    quint8 priorite;
    quint8 htsymbole;
    quint8 lgsymbole;
    CouleurBloc coulfond;
    CouleurBloc coulband;
    BlocPolice Bpolice;
    qint8    imicone[254];
    qint8    phraide[160];
};

struct BlocConfig{
    qint8    nom[80];
    CouleurBloc     coulecrangraph;
    CouleurBloc     coulbarremenu;
    BlocPolice      Bpolice;
    quint8    hticodeo;
    quint8    hticodrt;
    quint8    hticogah;
};

struct BlocLogiciel{
    qint8    nomprocessus[80];
    qint8    nomclair[80];
    qint8    options[127];
    qint8    imicone[254];
    qint8    phraide[160];
    qint8    dosproc[254];
    qint8    dependance[127];
    quint8    delai;
    quint8    unique;
    quint8    classe;
    qint8    stdcfg[254];
    qint8    stdtrv[254];
    qint8    optcfg[15];
    qint8    opttrv[15];
};

struct BlocAncre{
    BlocSymbole Bsymbole;
    qint8    imicone[60];
};
struct Ligne{
    CouleurBloc coul;
    quint8        typlig;
    quint8        epr;
};
struct BlocConnexion{
    CouleurBloc cograf;
    BlocAncre   ancre;
    Ligne    tligne[MTLIG];
};
//struct EnrgDimFen{
//    int posx;
//    int posy;
//    int largeur;
//    int hauteur;
//};
#endif // STRUCTUREDEMARREUR_H
