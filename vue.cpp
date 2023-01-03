#include "vue.h"
#include <qmath.h>
#include <QtWidgets>

void ZonePartieDeScene::wheelEvent(QWheelEvent *){}

CadreZoneGraphique::CadreZoneGraphique(const QString &, QWidget *parent): QFrame(parent)
{
    setFrameStyle(Sunken | StyledPanel);
    pzonepartiedescene = new ZonePartieDeScene(this);
    pzonepartiedescene->setRenderHint(QPainter::Antialiasing, false);
    pzonepartiedescene->setDragMode(QGraphicsView::ScrollHandDrag);
    pzonepartiedescene->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    pzonepartiedescene->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    pzonepartiedescene->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    couleurfond.setNamedColor("#3c6483");
    QBrush pinceau;
        pinceau.setStyle(Qt::SolidPattern);
        pinceau.setColor(couleurfond);

    pzonepartiedescene->setBackgroundBrush(pinceau);
    pzonepartiedescene->setCacheMode(QGraphicsView::CacheBackground);

    celluledaffichage = new QGridLayout;
    celluledaffichage->addWidget(pzonepartiedescene, 0, 0);

    setLayout(celluledaffichage);

    setupMatrix();
}

CadreZoneGraphique::~CadreZoneGraphique()
{
    delete pzonepartiedescene;
    delete celluledaffichage;
}

QGraphicsView *CadreZoneGraphique::PtrZonePartieDeScene() const
{
    return static_cast<QGraphicsView *>(pzonepartiedescene);
}

void CadreZoneGraphique::setupMatrix()
{
    qreal scale = 1.0;
    QTransform matrix;
    matrix.scale(scale, scale);
    pzonepartiedescene->setTransform(matrix);
}
