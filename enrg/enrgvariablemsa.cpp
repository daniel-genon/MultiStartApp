#include "enrgvariablemsa.h"

EnrgVariableMSA::EnrgVariableMSA(){}
EnrgVariableMSA::EnrgVariableMSA(const QString &vvaleur,
                 const QString &vdefinition,
                 const QString &vcode_abrege)
{
    valeur.append(vvaleur);
    definition.append(vdefinition);
    code_abrege.append(vcode_abrege);
}
QString EnrgVariableMSA::Valeur() const { return valeur;}
QString EnrgVariableMSA::Definition() const { return definition;}
QString EnrgVariableMSA::Code_Abrege() const { return code_abrege; }

/*****************************************************************************

*****************************************************************************/

LstVarMSA::LstVarMSA()
{
    marqueav="$£$";
    marqueap="$§$";
    RazDonnees();
}
LstVarMSA::~LstVarMSA()
{
    for(qsizetype i=0;i<length();i++) delete (at(i));
}

void LstVarMSA::Ajouter( const QString &vvaleur,
                         const QString &vdefinition,
                         const QString &vcode_abrege )
{
    ptrenrgvariableMSA pnouveau = new EnrgVariableMSA( vvaleur, vdefinition, vcode_abrege );
    append(pnouveau);
}

bool LstVarMSA::VerifierVariableMSA( const QString &vphranalyse )
{
    RazDonnees();
    if(!vphranalyse.isEmpty())
    {
        phranalyse = vphranalyse;
        return TrouverCodeAbrege();
    }
    return false;
}

bool LstVarMSA::TrouverCodeAbrege()
{
    if(!phranalyse.isEmpty())
    {
    qsizetype deb, fin, nbcar;
    if((deb = phranalyse.indexOf(marqueav))!=-1)
      if((fin = phranalyse.indexOf(marqueap,deb+2))!=-1)
        {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
          deb += marqueav.size();
          nbcar = fin-deb;
          codeabregeencours = phranalyse.sliced(deb,nbcar);
#else
          deb += marqueav.count();
          nbcar = fin-deb;
          codeabregeencours = phranalyse.mid(deb,nbcar);
#endif
            return PointerEnrg();
        }
    }
    return false;
}

bool LstVarMSA::PointerEnrg()
{
    if(!codeabregeencours.isEmpty())
    {
        for( qsizetype i=0; i<count(); i++ )
        {
            if(at(i)->Code_Abrege() == codeabregeencours)
            {
                ptrenrgvar = at(i);
                return true;
            }
        }
    }
    return false;
}

void LstVarMSA::RazDonnees()
{
    phranalyse.clear();
    codeabregeencours.clear();
    ptrenrgvar  = nullptr;
}

ptrenrgvariableMSA LstVarMSA::RtPtrEnrg() const
{
    return ptrenrgvar;
}

bool LstVarMSA::PointerValeur(const QString &vcherche)
{
    if(!vcherche.isEmpty())
    {
        RazDonnees();
        for( qsizetype i=0; i<count(); i++ )
        {
            if(at(i)->Valeur() == vcherche)
            {
                ptrenrgvar = at(i);
                return true;
            }
        }
    }
    return false;
}
bool LstVarMSA::ConstruireInsertionCode( QString &insertion )
{
    insertion.clear();
    if( ptrenrgvar != nullptr )
    {
        insertion = marqueav+ptrenrgvar->Code_Abrege();
        insertion.append(marqueap);
    }
    return !insertion.isEmpty();
}
void LstVarMSA::RemplacerCode( QStringList &listevariablecode )
{
    RazDonnees();
    QString phrtmp;
    for( qsizetype i=0; i<count(); i++ )
    {
        ptrenrgvar=at(i);
        if(ConstruireInsertionCode( phrtmp ))
            listevariablecode.replaceInStrings(phrtmp,ptrenrgvar->Valeur());
    }
}
