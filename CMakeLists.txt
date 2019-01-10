cmake_minimum_required(VERSION 3.0)
project(svgpart)

set(QT_MIN_VERSION "5.5.0")
set(KF_MIN_VERSION "5.18.0")

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Widgets Svg)
find_package(KF5 ${KF_MIN_VERSION} REQUIRED COMPONENTS CoreAddons Parts)

add_definitions(
    -DQT_DEPRECATED_WARNINGS
    -DQT_DISABLE_DEPRECATED_BEFORE=0x050500
    -DQT_NO_URL_CAST_FROM_STRING
)

add_definitions(-DTRANSLATION_DOMAIN="svgpart")

set(svgpart_SRCS
    svgbrowserextension.cpp
    svgpart.cpp
)

add_library(svgpart MODULE ${svgpart_SRCS})
kcoreaddons_desktop_to_json(svgpart svgpart.desktop)

target_link_libraries(svgpart Qt5::Widgets Qt5::Svg KF5::CoreAddons KF5::Parts)

install(TARGETS svgpart DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf5/parts)
install(FILES svgpart.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
install(FILES svgpart.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/svgpart)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
