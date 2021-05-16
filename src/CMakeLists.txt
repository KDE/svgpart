add_definitions(-DTRANSLATION_DOMAIN="svgpart")

configure_file(svgpart.desktop.in ${CMAKE_CURRENT_BINARY_DIR}/svgpart.desktop @ONLY)

add_library(svgpart MODULE)

target_sources(svgpart PRIVATE
    svgbrowserextension.cpp
    svgpart.cpp

    svgpart.qrc
)

kcoreaddons_desktop_to_json(svgpart ${CMAKE_CURRENT_BINARY_DIR}/svgpart.desktop)

target_link_libraries(svgpart
    KF5::CoreAddons
    KF5::Parts
    KF5::I18n
    Qt5::Widgets
    Qt5::Svg
)

install(TARGETS svgpart DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf5/parts)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/svgpart.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})

install(
    FILES org.kde.svgpart.metainfo.xml
    DESTINATION ${KDE_INSTALL_METAINFODIR}
)
