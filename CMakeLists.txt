cmake_minimum_required(VERSION 2.8.9)
project(svgpart)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set(QT_MIN_VERSION "5.2.0")

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Widgets Svg)
find_package(KF5 REQUIRED COMPONENTS CoreAddons Parts)

add_definitions(-DTRANSLATION_DOMAIN="svgpart")

set(svgpart_SRCS
	svgpart.cpp
	)

add_library(svgpart MODULE ${svgpart_SRCS})

target_link_libraries(svgpart Qt5::Widgets Qt5::Svg KF5::CoreAddons KF5::Parts)

install(TARGETS svgpart DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES svgpart.desktop DESTINATION ${SERVICES_INSTALL_DIR})
install(FILES svgpart.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/svgpart)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
