project(svgpart)

set(svgpart_SRCS
	svgpart.cpp
	)

kde4_add_plugin(svgpart ${svgpart_SRCS})

target_link_libraries(svgpart ${KDE4_KPARTS_LIBS})

install(TARGETS svgpart DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES svgpart.desktop DESTINATION ${SERVICES_INSTALL_DIR})
install(FILES svgpart.rc DESTINATION ${DATA_INSTALL_DIR}/svgpart)
