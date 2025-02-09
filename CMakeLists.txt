find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(GOBJECT REQUIRED gobject-2.0)
pkg_check_modules(GST REQUIRED gstreamer-1.0)

include_directories(${GLIB_INCLUDE_DIRS} ${GOBJECT_INCLUDE_DIRS} ${GST_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS} ${GOBJECT_LIBRARY_DIRS} ${GST_LIBRARY_DIRS})
add_definitions(${GLIB_CFLAGS_OTHER} ${GOBJECT_CFLAGS_OTHER} ${GST_CFLAGS_OTHER})

find_package(GStreamerPluginsBase REQUIRED COMPONENTS tag pbutils)
include_directories(${GSTREAMER_TAG_INCLUDE_DIR} ${GSTREAMER_PBUTILS_INCLUDE_DIR})
link_directories(${GSTREAMER_TAG_LIBRARY_DIR} ${GSTREAMER_PBUTILS_LIBRARY_DIR})

add_ezinject_library(gstpipeexport
    USE_LH
    SOURCES libgstpipeexport.c
)

target_compile_options(gstpipeexport PUBLIC -D__USE_MINGW_ANSI_STDIO=0)
target_link_libraries(gstpipeexport ${GST_LIBRARIES}
                                     ${GSTREAMER_TAG_LIBRARY}
                                     ${GSTREAMER_PBUTILS_LIBRARY}
                                     ${GLIB_LIBRARIES}
                                     ${GOBJECT_LIBRARIES}
                                     dl)
