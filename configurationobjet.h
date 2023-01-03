#ifndef CONFIGURATIONOBJET_H
#define CONFIGURATIONOBJET_H

#include "bloc/fblocconfig.h"
#include "bloc/fblocobjetcontexte.h"
#include "enrg/enrgconnexion.h"
#include "enrg/enrgvariablemsa.h"

class ConfigurationObjet
{

public:
    ConfigurationObjet();
    ~ConfigurationObjet();

    bool InitialiserConfiguration( QString *pchemin, const QString &nomcfg );
    bool GestionConfiguration();

    bool PointerLogiciel( int indexlog );
    bool PointerLogiciel( const QString &nomclairlog );
    ptrenrglogiciel PointerLogiciel( quint8 noclasse, quint8 indexlog );
    ptrenrglogiciel LireLogiciel( bool debut=false );
    bool ListeDesClassesLogiciels( QList<quint8> &listclasse, bool trier=false );
    ptrenrglogiciel PointerClasseLogiciel( quint8 noclasse );
    ptrenrglogiciel LireLogicielParClasse();


    bool PointerPriorite( const QString &nom );
    bool PointerPriorite( quint8 valeur );
    quint8 PointerPrioriteMinimum();
    bool ListeDesPriorites(QStringList &listelabel, QList<quint8> &Listevaleur );
    quint8 LireValeurPriorite( const QString &nom );

    bool PointerTravail();
    bool PointerCfg();

    QString ConfigurationEnCours() const;
    quint8 HtrIcoLog();
    quint8 HtrIcoGes();
    quint8 HtrIcoDessous();
    ptrenrglogiciel PointeurLo();
    ptrenrgraphique PointeurGr();
    ptrenrgraphique PointeurFi();
    EnrgConfig      *PointeurGe();
    EnrgConnexion   *PointeurCo();

    LstVarMSA       lvarmsa;

protected:

private:

    QString phtmp;// zone texte fourretout

    qint16  indexlogiciel;
    qint16  indexgrhlogiciel;
    qint16  indexgrhficlie;
    quint16 noprioritetraite;// ancien nofamilletraite;

    FBlocConfig     fichierconfiguration;
    EnrgConfig      confgene;
    LstEnrgLogiciel lstlogiciel;
    LstEnrgGrLog    lstgrhlogiciel;
    LstEnrgGrFic    lstgrhficlie;
    EnrgConnexion   confconnex;


    void ConfigParDefaut();
    bool PointerFichierLie( quint8 valeur );

    /*

    EnrgGraph      *ptrFamille;
    EnrgGraphCFG   *ptrFiclie;
*/


};

#endif // CONFIGURATIONOBJET_H
