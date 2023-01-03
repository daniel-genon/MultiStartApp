#ifndef LOGICIEL_H
#define LOGICIEL_H

#include "graphobjetactif.h"
#include "fichierconfiguration.h"
#include "fichiertravail.h"

class  Logiciel : public GraphObjetActif
{
public:

    bool okvalide;

    Logiciel();
    Logiciel(ConfigurationObjet *ptrconf, QGraphicsScene *ptrscene);
    Logiciel(ConfigurationObjet *ptrconf, QGraphicsScene *ptrscene, quint8 noprio);

    void CollationnerDescripteur( EnrgObjetCtx *enrgtmp );

    FichierTravail *PtrFicTrv();
    FichierConfiguration *PtrFicCfg();

    virtual QString libelle() const;
    quint8  Priorite() const;

    bool VerifierExistenceSurScene();
    bool EstLeProcessus( const QString &nomtest );

    bool AUnStdTRV();
    bool AUnStdCFG();
    QString NomStdCFG() const;
    QString NomStdTRV() const;

    QString ListeOptions() const;
    QString OptCFG() const;
    QString OptTRV() const;
    QString NomDuProcess() const;
    QString CheminProcess() const;
    QString Dependance() const;
    quint8  DelaiApresDemarrage();
    QString NomFicStdTRV() const;
    QString NomFicStdCFG() const;
    bool    UnSeulAutorise();


protected :


    virtual void EcrireTitre();
    virtual void EcrireNom();

private:

    void InitLogiciel();
    bool ChoisirLaPriorite();

    EnrgLogiciel    donneelogiciel;

    quint8  priorite;
};


#endif // LOGICIEL_H
