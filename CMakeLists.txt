cmake_minimum_required(VERSION 3.10)

project(XmpMetadataEditor)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)
pkg_check_modules(LIBEXIV2 REQUIRED exiv2)

include_directories(${GTK3_INCLUDE_DIRS} ${JSONCPP_INCLUDE_DIRS} ${LIBEXIV2_INCLUDE_DIR})
link_directories(${GTK3_LIBRARY_DIRS} ${JSONCPP_LIBRARY_DIRS} ${LIBEXIV2_LIBRARY_DIRS})

add_executable(kyodo-meta kyodo-meta.cpp)

target_link_libraries(kyodo-meta ${GTK3_LIBRARIES} ${JSONCPP_LIBRARIES} ${LIBEXIV2_LIBRARIES})
