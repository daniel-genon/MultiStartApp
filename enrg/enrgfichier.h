#ifndef ENRGFICHIER_H
#define ENRGFICHIER_H

#include <QString>

class EnrgFichier
{
public:

    EnrgFichier();
    EnrgFichier( const QString &valeur );

    void Entrer( const EnrgFichier &valeur );
    void EntrerConvertir( const QString &valeur );

    QString Libelle() const;
    QString Extension() const;
    QString Chemin() const;
    QString NomEtendu() const;
    QString NomComplet( bool maison ) const;

    void CreerUnNom();

    void Libelle( const QString &valeur );
    void Chemin( const QString &valeur );
    void Extension( const QString &valeur );

private:

    QString nom;
    QString extension;
    QString chemin;
    QString maison;

    void ExclureCheminHome();

};

#endif // ENRGFICHIER_H
