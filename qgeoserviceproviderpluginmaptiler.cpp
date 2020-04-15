#include "qgeoserviceproviderpluginmaptiler.h"
#include "qgeotiledmappingmanagerenginemaptiler.h"


QGeoCodingManagerEngine *QGeoServiceProviderFactoryMapTiler::createGeocodingManagerEngine(
    const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString) const
{
    Q_UNUSED(parameters)
    Q_UNUSED(error)
    Q_UNUSED(errorString)
    return Q_NULLPTR;
}

QGeoRoutingManagerEngine *QGeoServiceProviderFactoryMapTiler::createRoutingManagerEngine(
    const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString) const
{
    Q_UNUSED(parameters)
    Q_UNUSED(error)
    Q_UNUSED(errorString)

    return Q_NULLPTR;
}

QPlaceManagerEngine *QGeoServiceProviderFactoryMapTiler::createPlaceManagerEngine(
    const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString) const
{
    Q_UNUSED(parameters)
    Q_UNUSED(error)
    Q_UNUSED(errorString)

    return Q_NULLPTR;
}

QGeoMappingManagerEngine *QGeoServiceProviderFactoryMapTiler::createMappingManagerEngine(
        const QVariantMap &parameters,
        QGeoServiceProvider::Error *error,
        QString *errorString) const
{
    return new QGeoTiledMappingManagerEngineMapTiler(parameters, error, errorString);
}
