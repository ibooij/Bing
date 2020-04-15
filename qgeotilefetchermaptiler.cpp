#include "qgeotilefetchermaptiler.h"
#include "qgeomapreplymaptiler.h"
#include "qgeotiledmapmaptiler.h"
#include "qgeotiledmappingmanagerenginemaptiler.h"
#include <QtLocation/private/qgeotilespec_p.h>

#include <QDebug>
#include <QSize>
#include <QDir>
#include <QUrl>
#include <QUrlQuery>
#include <QTime>
#include <QNetworkProxy>

#include <math.h>

#include <map>

QT_BEGIN_NAMESPACE

QGeoTileFetcherMapTiler::QGeoTileFetcherMapTiler(const QVariantMap &parameters,
                                                 QGeoTiledMappingManagerEngineMapTiler *engine,
                                                 const QSize &tileSize)
    :   QGeoTileFetcher(engine),
      m_networkManager(new QNetworkAccessManager(this)),
      m_engineMapTiler(engine),
      m_tileSize(tileSize)
{
    _apiKey = parameters.value(QStringLiteral("maptiler.apikey"), "").toString().toLatin1();

    if (parameters.contains(QStringLiteral("maptiler.useragent")))
        _userAgent = parameters.value(QStringLiteral("maptiler.useragent")).toString().toLatin1();
    else
        _userAgent = "Mozilla/5.0 (X11; Linux i586; rv:31.0) Gecko/20100101 Firefox/31.0";

    QStringList langs = QLocale::system().uiLanguages();
    if (langs.length() > 0) {
        _language = langs[0];
    }

    // Google version strings
    _versionMapTiler = "563";

    netRequest.setRawHeader("Referrer", "https://www.bing.com/maps/");
    netRequest.setRawHeader("Accept", "*/*");
    netRequest.setRawHeader("User-Agent", _userAgent);

}

QGeoTileFetcherMapTiler::~QGeoTileFetcherMapTiler()
{
}

QGeoTiledMapReply *QGeoTileFetcherMapTiler::getTileImage(const QGeoTileSpec &spec)
{
    QString surl = createUrl(spec.mapId(), spec.x(), spec.y(), spec.zoom());
    QUrl url(surl);

    netRequest.setUrl(url);

    QNetworkReply *netReply = m_networkManager->get(netRequest);

    QGeoTiledMapReply *mapReply = new QGeoMapReplyMapTiler(netReply, spec);

    return mapReply;
}


QString QGeoTileFetcherMapTiler::createUrl(int, int x, int y, int zoom)
{
    return QString("https://api.maptiler.com/maps/topo/%1/%2/%3@2x.png?key=%4")
        .arg(zoom)
        .arg(x)
        .arg(y)
        .arg(_apiKey);
}

void QGeoTileFetcherMapTiler::_networkReplyError(QNetworkReply::NetworkError error)
{
    qWarning() << "Could not connect to MapTiler maps. Error:" << error;
    if(_mapTilerReply)
    {
        _mapTilerReply->deleteLater();
        _mapTilerReply = NULL;
    }
}

void QGeoTileFetcherMapTiler::_replyDestroyed()
{
    _mapTilerReply = NULL;
}

QT_END_NAMESPACE
