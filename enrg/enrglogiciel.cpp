#include "enrglogiciel.h"

/*
    Structure de données pour logiciel
*/
EnrgLogiciel::EnrgLogiciel(){}
EnrgLogiciel::EnrgLogiciel( const EnrgLogiciel &autre ){Valeur( autre );}
EnrgLogiciel::EnrgLogiciel(const QString &vnom,
              const QString &vcla,
              const QString &vopt,
              const QString &vaid,
              const QString &vdos,
              const QString &vico,
              const QString &vdep, quint8 vdelai, quint8 vuni , quint8 vclas,
              const QString &vstcfg, const QString &vsttrv,
              const QString &opcfg, const QString &optrv  )
{
    Valeur(vnom,vcla,vopt,vaid,vdos,vico,vdep, vdelai, vuni, vclas, vstcfg, vsttrv, opcfg, optrv);
}

void EnrgLogiciel::Valeur( const EnrgLogiciel *pautre )
{
    nomprocessus    = pautre->NomProcessus();
    nomclair        = pautre->NomClair();
    options         = pautre->Options();
    phraide         = pautre->Aide();
    dosproc         = pautre->Dossier();
    imicone         = pautre->Icone();
    stdcfg          = pautre->StdCFG();
    stdtrv          = pautre->StdTRV();
    delai           = pautre->Delai();
    unique          = pautre->Unique();
    dependance      = pautre->Dependance();
    classe          = pautre->Classe();
    optcfg          = pautre->OptCFG();
    opttrv          = pautre->OptTRV();
}
void EnrgLogiciel::Valeur( const EnrgLogiciel &autre )
{
    nomprocessus    = autre.NomProcessus();
    nomclair        = autre.NomClair();
    options         = autre.Options();
    phraide         = autre.Aide();
    dosproc         = autre.Dossier();
    imicone         = autre.Icone();
    stdcfg          = autre.StdCFG();
    stdtrv          = autre.StdTRV();
    delai           = autre.Delai();
    unique          = autre.Unique();
    dependance      = autre.Dependance();
    classe          = autre.Classe();
    optcfg          = autre.OptCFG();
    opttrv          = autre.OptTRV();
}
void EnrgLogiciel::Valeur(const QString &vnom,
              const QString &vcla,
              const QString &vopt,
              const QString &vaid,
              const QString &vdos,
              const QString &vico,
              const QString &vdep,
              quint8  vdelai,
              quint8  vuni, quint8 vclas,
              const QString &vstcfg,
              const QString &vsttrv ,
              const QString &opcfg,
              const QString &optrv)
{
    if(!vcla.isEmpty())
        nomclair = vcla;
    nomprocessus    = vnom;
    options         = vopt;
    phraide         = vaid;
    dosproc         = vdos;
    imicone         = vico;
    stdcfg          = vstcfg;
    stdtrv          = vsttrv;
    delai           = vdelai;
    unique          = vuni;
    dependance      = vdep;
    classe          = vclas;
    optcfg          = opcfg;
    opttrv          = optrv;

}

void EnrgLogiciel::NomProcessus( const QString &valeur){nomprocessus= valeur;}
void EnrgLogiciel::NomClair( const QString &valeur){nomclair= valeur;}
void EnrgLogiciel::Options( const QString &valeur){options= valeur;}
void EnrgLogiciel::Aide( const QString &valeur){phraide= valeur;}
void EnrgLogiciel::Dossier( const QString &valeur){dosproc= valeur;}
void EnrgLogiciel::Icone( const QString &valeur){imicone= valeur;}
void EnrgLogiciel::StdCFG( const QString &valeur){stdcfg = valeur;}
void EnrgLogiciel::StdTRV( const QString &valeur){stdtrv = valeur;}
void EnrgLogiciel::OptCFG( const QString &valeur){optcfg = valeur;}
void EnrgLogiciel::OptTRV( const QString &valeur){opttrv = valeur;}
void EnrgLogiciel::Dependance( const QString &valeur){dependance= valeur;}
void EnrgLogiciel::Delai( quint8 valeur){delai= valeur;}
void EnrgLogiciel::Unique( quint8 valeur){unique= valeur;}
void EnrgLogiciel::Classe( quint8 valeur){classe= valeur;}
void EnrgLogiciel::Unique( bool valeur){ if(valeur) unique=1; else unique=0;}

QString EnrgLogiciel::NomProcessus() const{    return nomprocessus;}
QString EnrgLogiciel::NomClair() const{    return nomclair;}
QString EnrgLogiciel::Options() const{    return options;}
QString EnrgLogiciel::Aide() const{    return phraide;}
QString EnrgLogiciel::Dossier() const{    return dosproc;}
QString EnrgLogiciel::Icone() const{    return imicone;}
QString EnrgLogiciel::StdCFG() const{    return stdcfg;}
QString EnrgLogiciel::StdTRV() const{    return stdtrv;}
QString EnrgLogiciel::OptCFG() const{    return optcfg;}
QString EnrgLogiciel::OptTRV() const{    return opttrv;}
QString EnrgLogiciel::Dependance() const{    return dependance;}
quint8  EnrgLogiciel::Delai() const{    return delai;}
quint8  EnrgLogiciel::Unique() const{    return unique;}
quint8  EnrgLogiciel::Classe() const{    return classe;}
bool    EnrgLogiciel::UniqueB(){    return unique==1;}

bool EnrgLogiciel::EgaleA( const EnrgLogiciel &autre )
{
    if(QString::compare(nomprocessus,autre.NomProcessus(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(nomclair,autre.NomClair(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(options,autre.Options(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(phraide,autre.Aide(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(dosproc,autre.Dossier(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(imicone,autre.Icone(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(stdcfg,autre.StdCFG(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(stdtrv,autre.StdTRV(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(optcfg,autre.OptCFG(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(opttrv,autre.OptTRV(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(dependance,autre.Dependance(),Qt::CaseInsensitive)!=0) return false;
/*
    if(nomprocessus.operator!=(autre.NomProcessus())) return false;
    if(nomclair.operator!=(autre.NomClair())) return false;
    if(options.operator!=(autre.Options())) return false;
    if(phraide.operator!=(autre.Aide())) return false;
    if(dosproc.operator!=(autre.Dossier())) return false;
    if(imicone.operator!=(autre.Icone())) return false;
    if(dosCFG.operator!=(autre.DossierCFG())) return false;
    if(dependance.operator!=(autre.Dependance())) return false;
*/
    if(delai!=autre.Delai()) return false;
    if(classe!=autre.Classe()) return false;
    return unique==autre.Unique();
}

bool EnrgLogiciel::EgaleA( const EnrgLogiciel *autre, bool testnom )
{
    if(testnom)
        if(QString::compare(nomprocessus,autre->NomProcessus(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(nomclair,autre->NomClair(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(options,autre->Options(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(phraide,autre->Aide(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(dosproc,autre->Dossier(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(imicone,autre->Icone(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(stdcfg,autre->StdCFG(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(stdtrv,autre->StdTRV(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(optcfg,autre->OptCFG(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(opttrv,autre->OptTRV(),Qt::CaseInsensitive)!=0) return false;
    if(QString::compare(dependance,autre->Dependance(),Qt::CaseInsensitive)!=0) return false;
    if(delai!=autre->Delai()) return false;
    if(classe!=autre->Classe()) return false;
    return unique==autre->Unique();
}

void EnrgLogiciel::CopierVersBloc( BlocLogiciel &cible )
{
        memset(&cible,0,sizeof(cible));
    TransQstrVersStr( nomprocessus, &cible.nomprocessus );
    TransQstrVersStr( nomclair, &cible.nomclair );
    TransQstrVersStr( options, &cible.options );
    TransQstrVersStr( phraide, &cible.phraide );
    TransQstrVersStr( dosproc, &cible.dosproc );
    TransQstrVersStr( imicone, &cible.imicone );
    TransQstrVersStr( stdcfg, &cible.stdcfg );
    TransQstrVersStr( stdtrv, &cible.stdtrv );
    TransQstrVersStr( optcfg, &cible.optcfg );
    TransQstrVersStr( opttrv, &cible.opttrv );
    TransQstrVersStr( dependance, &cible.dependance );
    cible.delai     = delai;
    cible.unique    = unique;
    cible.classe    = classe;
}
void EnrgLogiciel::CopierDepuisBloc( const BlocLogiciel &source )
{
    nomprocessus    = QString((QChar *)&source.nomprocessus);
    nomclair    = QString((QChar *)&source.nomclair);
    options     = QString((QChar *)&source.options);
    phraide     = QString((QChar *)&source.phraide);
    dosproc     = QString((QChar *)&source.dosproc);
    imicone     = QString((QChar *)&source.imicone);
    stdcfg      = QString((QChar *)&source.stdcfg);
    stdtrv      = QString((QChar *)&source.stdtrv);
    optcfg      = QString((QChar *)&source.optcfg);
    opttrv      = QString((QChar *)&source.opttrv);
    dependance  = QString((QChar *)&source.dependance);
    delai   = source.delai;
    unique  = source.unique;
    classe  = source.classe;
}




/*
    Liste d'enregistrement EnrgLogiciel
*/

LstEnrgLogiciel::LstEnrgLogiciel(){}
LstEnrgLogiciel::LstEnrgLogiciel( ptrenrglogiciel nouveau ){append(nouveau);}
LstEnrgLogiciel::~LstEnrgLogiciel()
{
    for(int i=0;i<length();i++) delete (at(i));
}

void LstEnrgLogiciel::Ajouter(const QString &vnom,
              const QString &vcla,
              const QString &vopt,
              const QString &vaid,
              const QString &vdos,
              const QString &vico,
              const QString &vdep,
              quint8 vdelai, quint8 vuni, quint8 vclas,
              const QString &vstcfg, const QString &vsttrv,
              const QString &opcfg, const QString &optrv )
{
    ptrenrglogiciel pnouveau = new EnrgLogiciel(vnom,vcla,vopt,vaid,vdos,vico,vdep,vdelai,vuni,vclas,vstcfg,vsttrv,opcfg,optrv);
    append(pnouveau);
}

void LstEnrgLogiciel::Ajouter( const BlocLogiciel &source)
{
    ptrenrglogiciel nouveau = new EnrgLogiciel();
    append(nouveau);
    nouveau->CopierDepuisBloc(source);
}

void LstEnrgLogiciel::CopierSimple( const LstEnrgLogiciel &source)
{
    clear();
    for(int i=0;i<source.length();i++)
        append(source.at(i));
}

void LstEnrgLogiciel::Copier(const LstEnrgLogiciel &source)
{
    clear();
    for(int i=0;i<source.length();i++)
    {
        ptrenrglogiciel nouveau = new EnrgLogiciel();
        append(nouveau);
        nouveau->Valeur( source.at(i) );
    }
}

bool LstEnrgLogiciel::EgaleA(const LstEnrgLogiciel &autre , bool testnom)
{
    if(autre.length() != length()) return false;
    for(int i=0;i<autre.length();i++)
    {
        if(!autre.value(i)->EgaleA(at(i),testnom)) return false;
    }
    return true;
}

void LstEnrgLogiciel::Nettoyer()
{
    for(int i=0;i<length();i++)  delete at(i);
    clear();
}

void LstEnrgLogiciel::Standard()
{
    Ajouter("gedit","Editeur de texte","","ouvrir un texte simple","/usr/bin/",":/icone/editeur.png","",5,0,1,"","","","");
}
