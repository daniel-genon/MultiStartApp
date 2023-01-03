#include "enrgfichier.h"
#include <qdir.h>

EnrgFichier::EnrgFichier()
{
    extension = "gla";
    nom = "nouveauftr";
    chemin = QDir::currentPath();
    maison = QDir::homePath();
    maison.append("/");
    ExclureCheminHome();
}

EnrgFichier::EnrgFichier( const QString &valeur )
{
    EntrerConvertir( valeur );
}

void EnrgFichier::Entrer( const EnrgFichier &valeur )
{
    extension = valeur.Extension();
    nom = valeur.Libelle();
    chemin = valeur.Chemin();
    ExclureCheminHome();
}

void EnrgFichier::EntrerConvertir( const QString &valeur )
{
    QFileInfo tmp(valeur);
        Extension( tmp.suffix() );
        Chemin( tmp.path() );
        Libelle( tmp.baseName());
}

QString EnrgFichier::Libelle() const{    return nom;}

QString EnrgFichier::Extension() const{    return extension;}

QString EnrgFichier::Chemin() const
{
    return (maison+chemin);
}

void EnrgFichier::Libelle( const QString &valeur ){    nom = valeur;}

void EnrgFichier::Extension( const QString &valeur ){    extension = valeur;}

void EnrgFichier::Chemin( const QString &valeur )
{
    chemin = valeur;
    ExclureCheminHome();
}

QString EnrgFichier::NomEtendu() const
{
    QString phrtmp = Libelle();
    phrtmp.append(".");
    phrtmp.append(Extension());
    return phrtmp;
}

QString EnrgFichier::NomComplet(bool maison) const
{
    QString phrtmp;
        if(maison)
            phrtmp = Chemin();
        else
            phrtmp = chemin;
    phrtmp.append("/");
    phrtmp.append(NomEtendu());
    return phrtmp;
}

void EnrgFichier::CreerUnNom()
{
    QFileInfo recfic;
    QString nomprovisoire( Chemin() );
    nomprovisoire.append( Libelle() );
    nomprovisoire.append( "%1" );
    nomprovisoire.append( "." );
    nomprovisoire.append( Extension() );
    QString nomtest;
    int increment=0;
    do{
        nomtest = QString(nomprovisoire).arg(increment++);
        recfic.setFile(nomtest);
    }while( recfic.exists() );
    Libelle(recfic.baseName());
}

void EnrgFichier::ExclureCheminHome()
{
    if(chemin.contains(maison))
        chemin = chemin.remove(0,(maison.length()));
}
