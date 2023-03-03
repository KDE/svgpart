add_definitions(-DTRANSLATION_DOMAIN="svgpart")

configure_file(svgpart.json.in ${CMAKE_CURRENT_BINARY_DIR}/svgpart.json @ONLY)

kcoreaddons_add_plugin(svgpart INSTALL_NAMESPACE "kf${QT_MAJOR_VERSION}/parts")

target_sources(svgpart PRIVATE
    svgview.cpp svgview.h
    svgbrowserextension.cpp svgbrowserextension.h
    svgpart.cpp svgpart.h

    svgpart.qrc
)

target_link_libraries(svgpart
    KF5::CoreAddons
    KF5::Parts
    KF5::I18n
    Qt${QT_MAJOR_VERSION}::Widgets
    Qt${QT_MAJOR_VERSION}::Svg
)

if (QT_MAJOR_VERSION STREQUAL "6")
    target_link_libraries(svgpart Qt6::SvgWidgets)
endif()


install(
    FILES org.kde.svgpart.metainfo.xml
    DESTINATION ${KDE_INSTALL_METAINFODIR}
)
