cmake_minimum_required(VERSION 3.25)
project(3DViewer C)

set(CMAKE_C_STANDARD 11)

SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -rdynamic")

add_executable(3DViewer src/gui/main_window.c
                        src/gui/change_display.c
                        src/gui/open_file.c

                        src/lib/affine_transformations.c
                        src/lib/parse_file.c
                        src/lib/render.c
        src/gui/change_work_mode.c)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

target_link_libraries(3DViewer ${GTK3_LIBRARIES} check subunit m)
#target_link_libraries(calculation_test ${GTK3_LIBRARIES} check subunit m)

add_definitions(${GTK3_CFLAGS_OTHER})
include_directories(${GTK3_INCLUDE_DIRS})