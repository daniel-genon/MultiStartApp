#include "mainwindow.h"
#include <QApplication>
//#include <QLocale>
//#include <QTranslator>

QString         *pCHRacine;
QString         *pCHRdateversionMSA;
QVersionNumber  *pversionMSA;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    Q_INIT_RESOURCE(images); //qt 5.15
#endif
    QLocale         regionMSA(QLocale::French,QLocale::LatinScript,QLocale::France);
    QVersionNumber  versionMSA(5,4,0);
    QDate           dateversionMSA(2022, 12, 19);
    pversionMSA     = &versionMSA;
    QString  CHRdateversionMSA  = regionMSA.toString(dateversionMSA,QLocale::LongFormat);
    pCHRdateversionMSA = &CHRdateversionMSA;

//    QTranslator translator;
//    const QStringList uiLanguages = QLocale::system().uiLanguages();
//    for (const QString &locale : uiLanguages) {
//        const QString baseName = "multistartapp_" + QLocale(locale).name();
//        if (translator.load(":/i18n/" + baseName)) {
//            a.installTranslator(&translator);
//            break;
//        }
//    }

    MainWindow fenetre;
    fenetre.show();
    return a.exec();
}
