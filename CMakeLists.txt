cmake_minimum_required(VERSION 3.6)
project(3DViewer C)
set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -rdynamic")

file(GLOB_RECURSE SRC_GUI_C src/gui/*.c)
file(GLOB_RECURSE SRC_LIB_C src/lib/*.c)
file(GLOB_RECURSE TEST_C    src/tests/*.c)

add_executable(3DViewer ${SRC_GUI_C} ${SRC_LIB_C})
add_executable(tests    ${SRC_LIB_C} ${TEST_C})

# GTK
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
add_definitions(${GTK3_CFLAGS_OTHER})
include_directories(${GTK3_INCLUDE_DIRS})
target_link_libraries(tests )

# ImageMagick
find_package(ImageMagick REQUIRED COMPONENTS MagickWand)
include_directories(${ImageMagick_INCLUDE_DIRS})
add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )

target_link_libraries(3DViewer ${GTK3_LIBRARIES} ${ImageMagick_LIBRARIES})
target_link_libraries(tests ${GTK3_LIBRARIES} check)

if (UNIX)
    target_link_libraries(3DViewer m)
    target_link_libraries(tests subunit m)
endif ()

