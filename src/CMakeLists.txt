add_definitions(-DTRANSLATION_DOMAIN="svgpart")

configure_file(svgpart.desktop.in ${CMAKE_CURRENT_BINARY_DIR}/svgpart.desktop @ONLY)

set(svgpart_SRCS
    svgbrowserextension.cpp
    svgpart.cpp
)

qt5_add_resources(svgpart_SRCS
    svgpart.qrc
)

add_library(svgpart MODULE ${svgpart_SRCS})
kcoreaddons_desktop_to_json(svgpart ${CMAKE_CURRENT_BINARY_DIR}/svgpart.desktop)

target_link_libraries(svgpart Qt5::Widgets Qt5::Svg KF5::CoreAddons KF5::Parts KF5::I18n)

install(TARGETS svgpart DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf5/parts)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/svgpart.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})

install(
    FILES org.kde.svgpart.metainfo.xml
    DESTINATION ${KDE_INSTALL_METAINFODIR}
)
