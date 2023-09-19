add_definitions(-DTRANSLATION_DOMAIN="svgpart")

add_library(svgpart MODULE)

target_sources(svgpart PRIVATE
    svgview.cpp svgview.h
    svgbrowserextension.cpp svgbrowserextension.h
    svgpart.cpp svgpart.h

    svgpart.qrc
)

configure_file(svgpart.json.in ${CMAKE_CURRENT_BINARY_DIR}/svgpart.json @ONLY)

target_link_libraries(svgpart
    KF6::CoreAddons
    KF6::Parts
    KF6::I18n
    Qt6::Widgets
    Qt6::Svg
    Qt6::SvgWidgets
)

install(TARGETS svgpart DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/parts)

install(
    FILES org.kde.svgpart.metainfo.xml
    DESTINATION ${KDE_INSTALL_METAINFODIR}
)
