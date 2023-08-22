cmake_minimum_required(VERSION 3.25)
project(3DViewer C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -rdynamic")

set(SRC_GUI_C
        src/gui/main_window.c
        src/gui/buttons_change_display.c
        src/gui/open_file.c
        src/gui/change_work_mode.c
        src/gui/close_app.c
        src/gui/change_input_mode.c
        src/gui/entrys_change_display.c
        )

set(SRC_LIB_C
        src/lib/affine_transformations.c
        src/lib/parse_file.c
        src/lib/render.c)

set(TEST_C
        src/tests/tests.c
        src/tests/affine_transformation_suite.c
        src/tests/parse_file_suite.c)

add_executable(3DViewer src/s21_3dviewer.h ${SRC_GUI_C} ${SRC_LIB_C})
add_executable(tests src/s21_3dviewer.h src/tests/tests.h ${SRC_LIB_C} ${TEST_C})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

target_link_libraries(3DViewer ${GTK3_LIBRARIES})
target_link_libraries(tests ${GTK3_LIBRARIES} check)

if (UNIX)
    target_link_libraries(3DViewer subunit m)
    target_link_libraries(tests subunit m)
endif ()

add_definitions(${GTK3_CFLAGS_OTHER})
include_directories(${GTK3_INCLUDE_DIRS})