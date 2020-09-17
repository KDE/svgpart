cmake_minimum_required(VERSION 3.5)

# Release Service version, managed by release script
set (RELEASE_SERVICE_VERSION_MAJOR "20")
set (RELEASE_SERVICE_VERSION_MINOR "11")
set (RELEASE_SERVICE_VERSION_MICRO "70")
set (RELEASE_SERVICE_COMPACT_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}${RELEASE_SERVICE_VERSION_MINOR}${RELEASE_SERVICE_VERSION_MICRO}")

# Bump SVGPART_BASE_VERSION once new features are added
set(SVGPART_BASE_VERSION "1.1")
set(SVGPART_VERSION "${SVGPART_BASE_VERSION}.${RELEASE_SERVICE_COMPACT_VERSION}")

project(svgpart VERSION ${SVGPART_VERSION})

set(QT_MIN_VERSION "5.9.0")
set(KF_MIN_VERSION "5.53.0")

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMSetupVersion)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Widgets Svg)
find_package(KF5 ${KF_MIN_VERSION} REQUIRED COMPONENTS CoreAddons Parts)

add_definitions(
    -DQT_NO_URL_CAST_FROM_STRING
)


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

ki18n_install(po)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
