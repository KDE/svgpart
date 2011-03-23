project(svgpart)
find_package(KDE4 REQUIRED)
include(KDE4Defaults)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories (${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})

set(svgpart_SRCS
	svgpart.cpp
	)

kde4_add_plugin(svgpart ${svgpart_SRCS})

target_link_libraries(svgpart ${KDE4_KPARTS_LIBS})

install(TARGETS svgpart DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES svgpart.desktop DESTINATION ${SERVICES_INSTALL_DIR})
install(FILES svgpart.rc DESTINATION ${DATA_INSTALL_DIR}/svgpart)
