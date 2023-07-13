add_definitions(-DTRANSLATION_DOMAIN="svgpart")

configure_file(svgpart.desktop.in ${CMAKE_CURRENT_BINARY_DIR}/svgpart.desktop @ONLY)

add_library(svgpart MODULE)

target_sources(svgpart PRIVATE
    svgview.cpp svgview.h
    svgbrowserextension.cpp svgbrowserextension.h
    svgpart.cpp svgpart.h

    svgpart.qrc
)

kcoreaddons_desktop_to_json(svgpart ${CMAKE_CURRENT_BINARY_DIR}/svgpart.desktop)

target_link_libraries(svgpart
    KF${QT_MAJOR_VERSION}::CoreAddons
    KF${QT_MAJOR_VERSION}::Parts
    KF${QT_MAJOR_VERSION}::I18n
    Qt${QT_MAJOR_VERSION}::Widgets
    Qt${QT_MAJOR_VERSION}::Svg
)

if (QT_MAJOR_VERSION STREQUAL "6")
    target_link_libraries(svgpart Qt6::SvgWidgets)
endif()


install(TARGETS svgpart DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf${QT_MAJOR_VERSION}/parts)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/svgpart.desktop DESTINATION ${KDE_INSTALL_KSERVICESDIR})

install(
    FILES org.kde.svgpart.metainfo.xml
    DESTINATION ${KDE_INSTALL_METAINFODIR}
)
