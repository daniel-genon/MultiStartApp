#include "enrggraph.h"

EnrgGraph::EnrgGraph(){}
EnrgGraph::EnrgGraph(const QString &vnom,
           const QString &vcf,
           const QString &vcb,
           const EnrgPolice &vpol,
           quint8 vlar, quint8 vhau, quint8 vprio)
{
    Valeur( vnom, vcf, vcb, vpol,vlar, vhau, vprio) ;
}

void EnrgGraph::Valeur( const QString &vnom,
                   const QString &vcf,
                   const QString &vcb,
                   const EnrgPolice &vpol,
                   quint8 vlar, quint8 vhau, quint8 vprio )
{
    if(!vnom.isEmpty())
        Nom( vnom );
    CouleurFond(vcf);
    CouleurBandeau( vcb );
    police.Valeur(vpol);
    DimSymbole( vhau, vlar );
    Priorite(vprio);
}

void EnrgGraph::Valeur( const EnrgGraph &autre )
{
    Nom(autre.Nom());
    CouleurFond(autre.CouleurFond());
    CouleurBandeau( autre.CouleurBandeau());
    Hauteur(autre.Hauteur());
    Largeur(autre.Largeur());
    Priorite(autre.Priorite());
    police.Valeur(autre.Police());
}

void EnrgGraph::Valeur( const EnrgGraph *autre )
{
    Nom(autre->Nom());
    CouleurFond(autre->CouleurFond());
    CouleurBandeau( autre->CouleurBandeau());
    Hauteur(autre->Hauteur());
    Largeur(autre->Largeur());
    Priorite(autre->Priorite());
    police.Valeur(autre->Police());
}

void EnrgGraph::Nom( const QString &valeur){libelle = valeur;}
void EnrgGraph::Priorite( quint8 valeur ){priorite = valeur;}
void EnrgGraph::Hauteur( quint8 valeur ){htsymbole = valeur;}
void EnrgGraph::Largeur( quint8 valeur ){lgsymbole = valeur;}
void EnrgGraph::DimSymbole( quint8 htr, quint8 lgr ){Hauteur(htr);Largeur(lgr);}
void EnrgGraph::CouleurFond( const QString &valeur){coulfond = valeur;}
void EnrgGraph::CouleurBandeau( const QString &valeur){coulband = valeur;}
void EnrgGraph::Police( const EnrgPolice &valeur ){police.Valeur(valeur);}

QString EnrgGraph::Nom() const  {return libelle;}
QString EnrgGraph::CouleurFond() const{return coulfond;}
QString EnrgGraph::CouleurBandeau() const{return coulband;}
quint8  EnrgGraph::Hauteur() const {return htsymbole;}
quint8  EnrgGraph::Largeur() const {return lgsymbole;}
quint8  EnrgGraph::Priorite() const {return priorite;}
EnrgPolice EnrgGraph::Police() const {return police;}

EnrgPolice *EnrgGraph::PPolice(){    return &police;}
QString *EnrgGraph::PtrCouleurFond(){return &coulfond;}
QString *EnrgGraph::PtrCouleurBandeau(){return &coulband;}

bool EnrgGraph::EgaleA( const EnrgGraph *autre, bool testnom )
{
    if (testnom)
        if(QString::compare(libelle,autre->Nom(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(coulfond,autre->CouleurFond(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(coulband,autre->CouleurBandeau(),Qt::CaseInsensitive)!=0) return false;
    if(htsymbole!=autre->Hauteur()) return false;
    if(lgsymbole!=autre->Largeur()) return false;
    if(priorite!=autre->Priorite()) return false;
    return police.EgaleA( autre->Police() );
}

void EnrgGraph::CopierVersBloc( BlocGraph &cible )
{
    memset(&cible,0,sizeof(cible));

    cible.htsymbole = htsymbole;
    cible.lgsymbole = lgsymbole;
    cible.priorite  = priorite;
    TransQstrVersStr( libelle, &cible.libelle );
    TransQstrVersStr( coulfond, &cible.coulfond );
    TransQstrVersStr( coulband, &cible.coulband );
    police.CopierVersBloc(cible.Bpolice);
}

void EnrgGraph::CopierDepuisBloc( const BlocGraph &source )
{
    htsymbole   = source.htsymbole;
    lgsymbole   = source.lgsymbole;
    priorite    = source.priorite;
    libelle     = QString((QChar *)&source.libelle);
    coulfond    = QString((QChar *)&source.coulfond);
    coulband    = QString((QChar *)&source.coulband);
    police.CopierDepuisBloc(source.Bpolice);
}


/*
    Liste d'enregistrement EnrgGraph
*/

LstEnrgGraph::LstEnrgGraph(){}
LstEnrgGraph::LstEnrgGraph( ptrenrgraphique nouveau ){append(nouveau);}
LstEnrgGraph::~LstEnrgGraph()
{
    for(int i=0;i<length();i++) delete (at(i));
}

void LstEnrgGraph::Ajouter( const QString &vnom,
                            const QString &vcf,
                            const QString &vcb,
                            const EnrgPolice &vpol,
                            quint8 vlar, quint8 vhau, quint8 vprio  )
{
    ptrenrgraphique pnouveau = new EnrgGraph( vnom,vcf,vcb,vpol,vlar,vhau,vprio );
    append(pnouveau);
}

void LstEnrgGraph::Ajouter( const BlocGraph &source)
{
    ptrenrgraphique nouveau = new EnrgGraph();
    append(nouveau);
    nouveau->CopierDepuisBloc(source);
}

//void LstEnrgGraph::CopierSimple( const LstEnrgGraph *source)
//{
//    clear();
//    for(int i=0;i<source->length();i++)
//        append(source->at(i));
//}
void LstEnrgGraph::CopierSimple( const LstEnrgGraph &source)
{
    clear();
    for(int i=0;i<source.length();i++)
        append(source.at(i));
}

//void LstEnrgGraph::Copier( const LstEnrgGraph *source)
//{
//    clear();
//    for(int i=0;i<source->length();i++)
//    {
//        ptrenrgraphique nouveau = new EnrgGraph();
//        append(nouveau);
//        nouveau->Valeur(source->at(i));
//    }
//}
void LstEnrgGraph::Copier( const LstEnrgGraph &source)
{
    clear();
    for(int i=0;i<source.length();i++)
    {
        ptrenrgraphique nouveau = new EnrgGraph();
        append(nouveau);
        nouveau->Valeur(source.at(i));
    }
}

bool LstEnrgGraph::EgaleA( const LstEnrgGraph &autre, bool testnom )
{
    if(autre.length() != length()) return false;
    for(int i=0;i<autre.length();i++)
    {
        if(!autre.value(i)->EgaleA(at(i),testnom)) return false;
    }
    return true;
}

void LstEnrgGraph::Nettoyer()
{
    for(int i=0;i<length();i++)  delete at(i);
    clear();
}

void LstEnrgGraph::Standard()
{
}


/*
    Liste d'enregistrement pour graphique logiciel
*/

LstEnrgGrLog::LstEnrgGrLog(){}

void LstEnrgGrLog::Standard()
{
    EnrgPolice policetmp("Bitstream Charter","#000000",8);
    Ajouter("immédiat","#89fbfa","#ffff00",policetmp,160,50,255);
    Ajouter("normal","#fbae36","#ffff00",policetmp,150,50,126);
    Ajouter("finale","#eb7184","#ffff00",policetmp,140,50,1);
}

/*
    Liste d'enregistrement pour graphique fichier lié
*/

LstEnrgGrFic::LstEnrgGrFic(){}

void LstEnrgGrFic::Standard()
{
    EnrgPolice policetmp("Bitstream Charter","#000000",8);
    Ajouter("configuration","#89fbfa","#ffff00",policetmp,180,50,1);
    Ajouter("fichier travail","#fbae36","#ffff00",policetmp,180,50,1);
}
