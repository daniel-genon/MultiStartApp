#ifndef MESSAGEMSA_H
#define MESSAGEMSA_H

#include <QMessageBox>

class MessageMSA : public QMessageBox
{
public:
    MessageMSA();
    MessageMSA( QWidget *parent );

    void FichierInexistant();
    void FichierNestPasCreer();
    void SauvegardeDonnees();
    bool QuitterLogiciel();
    void ObjetInconnu();
    void PasDeLogicielsDemarres();
    bool ArretDesLogiciels();

    int QuestionGestionFichier(const QString &phrtmp);
    int QuestionTroisReponse(const QString &phrtitre, const QString &phrtexte,
                             const QString &libbtn1,const QString &libbtn2,const QString &libbtn3);
    bool QuestionSuppression(const QString &phrtmp);
    bool QuestionMSA(const QString &phrtitre, const QString &phrtmp);

    static void AlerteMessage(const QString &phrttmp);
    void AlerteMessage(const QString &phrtitre, const QString &phrttmp);
    void AlerteErreur(const QString &phrtmp);
private:
    QWidget *fenetreparent;
};

#endif // MESSAGEMSA_H
