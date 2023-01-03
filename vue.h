#ifndef VUE_H
#define VUE_H

#include <QtGui>
#include <QFrame>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QGridLayout>

QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QSlider)
QT_FORWARD_DECLARE_CLASS(QToolButton)

class CadreZoneGraphique;

class ZonePartieDeScene : public QGraphicsView
{
    Q_OBJECT
public:
    ZonePartieDeScene(CadreZoneGraphique *v) : QGraphicsView(), cadredessin(v) { }

protected:
    void wheelEvent(QWheelEvent *);

private:
    CadreZoneGraphique *cadredessin;
};

class CadreZoneGraphique : public QFrame
{
    Q_OBJECT
public:
    CadreZoneGraphique(const QString &, QWidget *parent = 0);
    ~CadreZoneGraphique();

    QGraphicsView *PtrZonePartieDeScene() const;

private slots:
    void setupMatrix();

private:
    QGridLayout         *celluledaffichage;
    ZonePartieDeScene   *pzonepartiedescene;
    QColor              couleurfond;

};

#endif
