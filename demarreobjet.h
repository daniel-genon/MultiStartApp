#ifndef DEMARREOBJET_H
#define DEMARREOBJET_H

#include <QtGui>
#include <QList>
#include "gerersession.h"
#include "logiciel.h"

class DemarreObjet
{
public:

    DemarreObjet();

    void InitSession( GererSession *valeur, QGraphicsScene *pvalscene );
    bool ReinitialiserLaScene();
    void DemarrerLaSession(  );
    void ArreterLesProcessus();
    bool DesProcessusSontDemarres();

private:

    QGraphicsScene  *pscene;
    GererSession    *psession;
    Logiciel        *plogi;

    quint64 paquet;

    QStringList lstprocessus;

    QString nomdulogiciel;
    QString phrasededemarreur;
    QStringList nomfichiercfgobjet;
    QStringList nomfichiertrvobjet;
    QStringList phrasepouroptions;
    QStringList lstdependance;

    QList<QGraphicsItem *> tabitem;
    QList<Logiciel *> tabdemarrage;

    int  AjouterATable( Logiciel *plogi );
    void ClasserObjets();
    bool LancerProcessus();

    void PhraseFichierCFG();
    void PhraseFichierTRV();
    QStringList PhraseFichier( const QString &nmfic, const QString &opfic );
    void IntegrerLesDependances();
    void IntegrerDansListeDesDemarres();

    bool ProcessusExistant();
    void Attendre(int valeur);
};

#endif // DEMARREOBJET_H
