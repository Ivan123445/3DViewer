cmake_minimum_required(VERSION 3.25)
project(3DViewer C)
set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -rdynamic")

file(GLOB_RECURSE SRC_GUI_C src/gui/*.c)
file(GLOB_RECURSE SRC_LIB_C src/lib/*.c)
file(GLOB_RECURSE TEST_C    src/tests/*.c)

add_executable(3DViewer ${SRC_GUI_C} ${SRC_LIB_C})
add_executable(tests    ${SRC_LIB_C} ${TEST_C})

find_package(PkgConfig REQUIRED)
find_package(ImageMagick REQUIRED COMPONENTS MagickWand)


target_link_libraries(3DViewer ${ImageMagick_LIBRARIES})
include_directories(${ImageMagick_INCLUDE_DIRS})
target_link_libraries(3DViewer ${GTK3_LIBRARIES})
target_link_libraries(tests ${GTK3_LIBRARIES} check)


if (UNIX)
    target_link_libraries(3DViewer subunit m)
    target_link_libraries(tests subunit m)
endif ()

include_directories(${GTK3_INCLUDE_DIRS})
