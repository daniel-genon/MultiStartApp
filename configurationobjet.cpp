#include "configurationobjet.h"
#include "dialogue/dialogconfiggenerale.h"
#include <QtAlgorithms>

ConfigurationObjet::ConfigurationObjet()
{
    fichierconfiguration.InitPointeur( &confgene, &confconnex, &lstlogiciel, &lstgrhlogiciel, &lstgrhficlie );
}
ConfigurationObjet::~ConfigurationObjet()
{
    if(!lvarmsa.isEmpty())
    {
        for(int i=0;i<lvarmsa.length();i++) delete lvarmsa[i];
        lvarmsa.clear();
    }
}

ptrenrglogiciel  ConfigurationObjet::PointeurLo(){ return lstlogiciel.at(indexlogiciel); }
ptrenrgraphique  ConfigurationObjet::PointeurGr(){ return lstgrhlogiciel.at(indexgrhlogiciel); }
EnrgConfig      *ConfigurationObjet::PointeurGe(){ return &confgene; }
EnrgConnexion   *ConfigurationObjet::PointeurCo(){ return &confconnex; }
ptrenrgraphique  ConfigurationObjet::PointeurFi(){ return lstgrhficlie.at(indexgrhficlie); }

/*

EnrgGraph      *ConfigurationObjet::PointeurFa(){return ptrFamille;}
EnrgGraphCFG   *ConfigurationObjet::PointeurCf(){return ptrFiclie;}
EnrgAncre      *ConfigurationObjet::PointeurAn(){return &confconnex.Ancrage;}
*/

bool ConfigurationObjet::InitialiserConfiguration( QString *pchemin, const QString &nomcfg )
{
    if(!fichierconfiguration.Initialiser( pchemin ))
    {
        ConfigParDefaut();
        fichierconfiguration.CreerConfigurationStandard();
        return false;
    }
    else
    {
        if(!fichierconfiguration.LireConfiguration(nomcfg))
        {
            if(!fichierconfiguration.LirePremiereConfig())
                ConfigParDefaut();
            return false;
        }
    }
    return true;
}

QString ConfigurationObjet::ConfigurationEnCours() const
{
    return confgene.Nom();
}


bool ConfigurationObjet::GestionConfiguration()
{
    bool okvaleur=false;
    DialogConfigGenerale *dlg = new DialogConfigGenerale;
    dlg->setModal(true);
    dlg->IniBoite( &fichierconfiguration, &lvarmsa );
    if(dlg->exec()==QDialog::Accepted)
    {
        fichierconfiguration.LireConfiguration(ConfigurationEnCours());
        okvaleur=true;
    }
    delete dlg;
    return okvaleur;
}
/*
bool ConfigurationObjet::PointerConfigGraphique( quint16 nofamille )
{
    if(nofamille>=lstgraphique.length()) return false;
    indexgraphique = nofamille;
    ptrFamille = &lstgraphique.operator [](indexgraphique);
    return true;
}
*/


//****************   GRAPHIQUE/PRIORITE   ************************************
bool ConfigurationObjet::PointerPriorite( const QString &nom )
{
    indexgrhlogiciel = 0;
    for(int i=0; i<lstgrhlogiciel.length(); i++ )
    {
        if(QString::compare(nom,lstgrhlogiciel.at(i)->Nom(),Qt::CaseInsensitive)==0)
        {
            indexgrhlogiciel = i;
            return true;
        }
    }
    return false;
}
bool ConfigurationObjet::PointerPriorite( quint8 valeur )
{
    indexgrhlogiciel = 0;
    for(int i=0; i<lstgrhlogiciel.length(); i++ )
    {
        if( lstgrhlogiciel.at(i)->Priorite()==valeur)
        {
            indexgrhlogiciel = i;
            return true;
        }
    }
    return false;
}
quint8 ConfigurationObjet::PointerPrioriteMinimum()
{
    indexgrhlogiciel = 0;
    quint8 valmin = 255;
    for(int i=0; i<lstgrhlogiciel.length(); i++ )
    {
        quint8 vtest = lstgrhlogiciel.at(i)->Priorite();
        if(vtest<valmin)
        {
            valmin=vtest;
            indexgrhlogiciel = i;
        }
    }
    if(valmin==255)
        return 1;
    else
        return valmin;
}
quint8 ConfigurationObjet::LireValeurPriorite( const QString &nom )
{
    for(int i=0; i<lstgrhlogiciel.length(); i++ )
    {
        if(QString::compare(nom,lstgrhlogiciel.at(i)->Nom(),Qt::CaseInsensitive)==0)
         return lstgrhlogiciel.at(i)->Priorite();
    }
    return 1;
}
bool ConfigurationObjet::ListeDesPriorites( QStringList &listelabel, QList<quint8> &Listevaleur )
{
    listelabel.clear();
    Listevaleur.clear();
    for(int i=0; i<lstgrhlogiciel.length(); i++ )
    {
        listelabel.append(lstgrhlogiciel.at(i)->Nom());
        Listevaleur.append(lstgrhlogiciel.at(i)->Priorite());
    }
    return !listelabel.isEmpty();
}

//****************   LOGICIELS   ************************************
bool ConfigurationObjet::PointerLogiciel(int indexlog )
{
    if((lstlogiciel.length()>0) && indexlog > -1 )
    {
        if(indexlog < lstlogiciel.length())
        {
            indexlogiciel=indexlog;
            return true;
        }
    }
    return false;
}
bool ConfigurationObjet::PointerLogiciel( const QString &nomclairlog )
{
    if(!nomclairlog.isEmpty())
    {
        for(int i=0;i<lstlogiciel.length();i++)
            if(nomclairlog.compare(lstlogiciel.at(i)->NomClair())==0)
            {
                indexlogiciel=i;
                return true;
            }
    }
    return false;
}
ptrenrglogiciel ConfigurationObjet::PointerLogiciel( quint8 noclasse, quint8 indexlog )
{
    ptrenrglogiciel valtmp = PointerClasseLogiciel( noclasse );
    if(valtmp!=NULL)
    {
        for(int i=0;i!=indexlog;i++)
            valtmp = LireLogicielParClasse();
        if(valtmp!=NULL) return valtmp;
    }
    return NULL;
}
ptrenrglogiciel ConfigurationObjet::PointerClasseLogiciel( quint8 noclasse )
{
    indexlogiciel       = 0;
    noprioritetraite    = noclasse;
    if(!lstlogiciel.isEmpty())
    {
        while(indexlogiciel<lstlogiciel.length())
        {
            if(lstlogiciel.at(indexlogiciel)->Classe()==noprioritetraite)
                return lstlogiciel.at(indexlogiciel);
            indexlogiciel++;
        }
    }
    return NULL;
}
ptrenrglogiciel ConfigurationObjet::LireLogicielParClasse()
{
    indexlogiciel++;
    while(indexlogiciel<lstlogiciel.length())
    {
        if(lstlogiciel.at(indexlogiciel)->Classe()==noprioritetraite )
            return lstlogiciel.at(indexlogiciel);
        indexlogiciel++;
    }
    return NULL;
}

ptrenrglogiciel ConfigurationObjet::LireLogiciel( bool debut )
{
    if(!lstlogiciel.isEmpty())
    {
        if(debut)
            indexlogiciel = 0;
        else
            indexlogiciel++;
        if(indexlogiciel<lstlogiciel.length())
             return lstlogiciel.at(indexlogiciel);
    }
    return NULL;
}

//****************   GRAPHIQUE/FICHIER LIE   ****************************

bool ConfigurationObjet::PointerTravail(){  return PointerFichierLie( 0 );}

bool ConfigurationObjet::PointerCfg(){  return PointerFichierLie( 1 );}

bool ConfigurationObjet::PointerFichierLie( quint8 valeur )
{
    indexgrhficlie = 0;
    if(valeur>=lstgrhficlie.length()) return false;
    indexgrhficlie = valeur;
    return true;
}





quint8 ConfigurationObjet::HtrIcoLog()
{
    return confgene.IconeSymbole();
}
quint8 ConfigurationObjet::HtrIcoGes()
{
    return confgene.IconeGestion();
}
quint8 ConfigurationObjet::HtrIcoDessous()
{
    return confgene.IconeDessous();
}

void ConfigurationObjet::ConfigParDefaut()
{
    confgene.Standard();
    confconnex.Standard();
    lstlogiciel.Standard();
//priorité (element graphique)
    lstgrhlogiciel.Standard();
//fichier cfg trv lié
    lstgrhficlie.Standard();
}

bool ConfigurationObjet::ListeDesClassesLogiciels( QList<quint8> &listclasse, bool trier )
{
    listclasse.clear();
    for(int i=0; i<lstlogiciel.length(); i++ )
    {
        quint8 inttmp = lstlogiciel.at(i)->Classe();
        if(!listclasse.contains(inttmp))
            listclasse.append(inttmp);
    }
    if(listclasse.isEmpty())
        return false;
    else
        if(trier)
            std::sort(listclasse.begin(),listclasse.end());
    return true;
}


