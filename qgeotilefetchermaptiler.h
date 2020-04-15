#pragma once

#include "qgeoserviceproviderpluginmaptiler.h"

#include <QtLocation/private/qgeotilefetcher_p.h>
#include <QMutex>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE

class QGeoTiledMapReply;
class QGeoTileSpec;
class QGeoTiledMappingManagerEngine;
class QGeoTiledMappingManagerEngineMapTiler;
class QNetworkAccessManager;

class QGeoTileFetcherMapTiler : public QGeoTileFetcher
{
    Q_OBJECT

public:
    QGeoTileFetcherMapTiler(const QVariantMap &parameters,
                         QGeoTiledMappingManagerEngineMapTiler *engine, const QSize &tileSize);
    ~QGeoTileFetcherMapTiler();

    QGeoTiledMapReply *getTileImage(const QGeoTileSpec &spec);

private:
    QString _getURL(int type, int x, int y, int zoom);

private slots:
    void _networkReplyError(QNetworkReply::NetworkError error);
    void _replyDestroyed();

private:
    Q_DISABLE_COPY(QGeoTileFetcherMapTiler)

    QNetworkAccessManager *m_networkManager;

    QPointer<QGeoTiledMappingManagerEngineMapTiler> m_engineMapTiler;
    QSize m_tileSize;

    int             _timeout;
    QNetworkReply*  _mapTilerReply;
    QByteArray      _userAgent;
    QString         _language;

    // Bing version strings
    QString         _versionMapTiler;

    QNetworkRequest netRequest;
};

QT_END_NAMESPACE

