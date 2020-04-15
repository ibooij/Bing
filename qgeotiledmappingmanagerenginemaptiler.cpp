#include "QtLocation/private/qgeocameracapabilities_p.h"
#include "qgeotiledmappingmanagerenginemaptiler.h"
#include "qgeotiledmapmaptiler.h"
#include "qgeotilefetchermaptiler.h"
#include "QtLocation/private/qgeotilespec_p.h"
#include "QtLocation/private/qgeofiletilecache_p.h"

#include <QDebug>
#include <QDir>
#include <QVariant>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/qmath.h>
#include <QtCore/qstandardpaths.h>

QT_BEGIN_NAMESPACE

QGeoTiledMappingManagerEngineMapTiler::QGeoTiledMappingManagerEngineMapTiler(const QVariantMap &parameters,
    QGeoServiceProvider::Error *error,
    QString *errorString)
    : QGeoTiledMappingManagerEngine()
{
    Q_UNUSED(error);
    Q_UNUSED(errorString);

    QGeoCameraCapabilities capabilities;

    capabilities.setMinimumZoomLevel(0.0);
    capabilities.setMaximumZoomLevel(21.0);

    setCameraCapabilities(capabilities);

    setTileSize(QSize(512, 512));

    QList<QGeoMapType> types;
//#if QT_VERSION < QT_VERSION_CHECK(5,9,0)
//    types << QGeoMapType(QGeoMapType::StreetMap,"Bing Street Map", "Bing street map", false, false, 1);
//    types << QGeoMapType(QGeoMapType::SatelliteMapDay, "Bing Satellite Map", "Bing satellite map", false, false, 2);
//    types << QGeoMapType(QGeoMapType::HybridMap, "Bing Hybrid Map", "Bing hybrid map", false, false, 3);
//#elif QT_VERSION < QT_VERSION_CHECK(5,10,0)
//    types << QGeoMapType(QGeoMapType::StreetMap,"Bing Street Map", "Bing street map", false, false, 1, "bingmaps");
//    types << QGeoMapType(QGeoMapType::SatelliteMapDay, "Bing Satellite Map", "Bing satellite map", false, false, 2, "bingmaps");
//    types << QGeoMapType(QGeoMapType::HybridMap, "Bing Hybrid Map", "Bing hybrid map", false, false, 3, "bingmaps");
//#else
    types << QGeoMapType(QGeoMapType::TerrainMap, "MapTiler Topo map", "MapTiler Topo map", false, false, 1, "maptiler", capabilities, parameters);
//    types << QGeoMapType(QGeoMapType::SatelliteMapDay, "Bing Satellite Map", "Bing satellite map", false, false, 2, "bingmaps", capabilities, parameters);
//    types << QGeoMapType(QGeoMapType::HybridMap, "Bing Hybrid Map", "Bing hybrid map", false, false, 3, "bingmaps", capabilities, parameters);
//#endif

    setSupportedMapTypes(types);

    QGeoTileFetcherMapTiler *fetcher = new QGeoTileFetcherMapTiler(parameters, this, tileSize());
    setTileFetcher(fetcher);

    if (parameters.contains(QStringLiteral("maptiler.cachefolder")))
        m_cacheDirectory = parameters.value(QStringLiteral("maptiler.cachefolder")).toString().toLatin1();
    else
        m_cacheDirectory = QAbstractGeoTileCache::baseCacheDirectory() + QLatin1String("maptiler");

    QAbstractGeoTileCache *tileCache = new QGeoFileTileCache(m_cacheDirectory);
    setTileCache(tileCache);

    populateMapSchemes();
}

QGeoTiledMappingManagerEngineMapTiler::~QGeoTiledMappingManagerEngineMapTiler()
{
}

void QGeoTiledMappingManagerEngineMapTiler::populateMapSchemes()
{
    m_mapSchemes[0] = QStringLiteral("topo");
//    m_mapSchemes[1] = QStringLiteral("roadmap");
//    m_mapSchemes[2] = QStringLiteral("satellite");
//    m_mapSchemes[3] = QStringLiteral("hybrid");
}

QString QGeoTiledMappingManagerEngineMapTiler::getScheme(int mapId)
{
    return m_mapSchemes[mapId];
}

QGeoMap *QGeoTiledMappingManagerEngineMapTiler::createMap()
{
    return new QGeoTiledMapMapTiler(this);
}

QT_END_NAMESPACE

