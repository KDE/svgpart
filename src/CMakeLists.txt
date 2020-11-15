add_definitions(-DTRANSLATION_DOMAIN="svgpart")

ecm_setup_version(${SVGPART_VERSION}
    VARIABLE_PREFIX SVGPART
    VERSION_HEADER svgpart_version.h
)

set(svgpart_SRCS
    svgbrowserextension.cpp
    svgpart.cpp
)

qt5_add_resources(svgpart_SRCS
    svgpart.qrc
)

add_library(svgpart MODULE ${svgpart_SRCS})
kcoreaddons_desktop_to_json(svgpart svgpart.desktop)

target_link_libraries(svgpart Qt5::Widgets Qt5::Svg KF5::CoreAddons KF5::Parts)

install(TARGETS svgpart DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf5/parts)
install(FILES svgpart.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
