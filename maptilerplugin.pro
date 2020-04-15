TARGET = qtgeoservices_maptiler
QT += location-private positioning-private network

PLUGIN_TYPE = geoservices
PLUGIN_CLASS_NAME = QGeoServiceProviderFactoryMapTiler
load(qt_plugin)

HEADERS += \
    qgeoserviceproviderpluginmaptiler.h \
    qgeomapreplymaptiler.h \
    qgeotiledmapmaptiler.h \
    qgeotiledmappingmanagerenginemaptiler.h \
    qgeotilefetchermaptiler.h

SOURCES += \
    qgeoserviceproviderpluginmaptiler.cpp \
    qgeomapreplymaptiler.cpp \
    qgeotiledmapmaptiler.cpp \
    qgeotiledmappingmanagerenginemaptiler.cpp \
    qgeotilefetchermaptiler.cpp


OTHER_FILES += \
    maptiler_plugin.json

