#pragma once

#include "QtLocation/private/qgeotiledmap_p.h"
#include <QtGui/QImage>
#include <QtCore/QPointer>

QT_BEGIN_NAMESPACE

class QGeoTiledMappingManagerEngineMapTiler;

class QGeoTiledMapMapTiler: public QGeoTiledMap
{
Q_OBJECT
public:
    QGeoTiledMapMapTiler(QGeoTiledMappingManagerEngineMapTiler *engine, QObject *parent = 0);
    ~QGeoTiledMapMapTiler();

    QString getViewCopyright();
    void evaluateCopyrights(const QSet<QGeoTileSpec> &visibleTiles);

private:
    //QImage m_logo;
    QImage m_copyrightsSlab;
    QString m_lastCopyrightsString;
    QPointer<QGeoTiledMappingManagerEngineMapTiler> m_engine;

    Q_DISABLE_COPY(QGeoTiledMapMapTiler)
};

QT_END_NAMESPACE

