#ifndef ENRGVARIABLEMSA_H
#define ENRGVARIABLEMSA_H

#include <QString>
#include <QList>

class EnrgVariableMSA
{
public:
    EnrgVariableMSA();
    EnrgVariableMSA( const QString &vvaleur,
                     const QString &vdefinition,
                     const QString &vcode_abrege);

    QString Valeur() const;
    QString Definition() const;
    QString Code_Abrege() const;

private:
    QString valeur;
    QString definition;
    QString code_abrege;

};

typedef EnrgVariableMSA *ptrenrgvariableMSA;

class LstVarMSA : public QList<ptrenrgvariableMSA>
{
public:
    LstVarMSA();
    ~LstVarMSA();
    void Ajouter(const QString &vvaleur,
                 const QString &vdefinition,
                 const QString &vcode_abrege );
    void Marques(const QString &mavant,const QString &mapres);
    void RemplacerCode( QStringList &listevariablecode );


    bool VerifierVariableMSA(const QString &vphranalyse);
    bool PointerValeur(const QString &vcherche);
    bool ConstruireInsertionCode( QString &insertion );
    ptrenrgvariableMSA RtPtrEnrg() const;

private:

    QString phranalyse;
    QString marqueav;
    QString marqueap;
    QString codeabregeencours;

    ptrenrgvariableMSA ptrenrgvar;

    void RazDonnees();
    bool PointerEnrg();
    bool TrouverCodeAbrege();

};


#endif // ENRGVARIABLEMSA_H
