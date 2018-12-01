cmake_minimum_required (VERSION 3.3.0)

SET(pwd ${CMAKE_CURRENT_LIST_DIR})

UNSET(src)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_PREFIX_PATH "/lusr/opt/bullet-2.86/;${CMAKE_PREFIX_PATH}")
set(CMAKE_PREFIX_PATH "${PWD}/ogre-imgui/;${CMAKE_PREFIX_PATH}")
set(CMAKE_MODULE_PATH "/lusr/opt/ogre-1.11;${CMAKE_MODULE_PATH}")
set(CMAKE_MODULE_PATH "/lusr/opt/bullet-2.86;${CMAKE_MODULE_PATH}")
set(OGRE_DIR /lusr/opt/ogre-1.11/lib/OGRE/cmake)
set(BULLET_DIR /lusr/opt/bullet-2.86/lib/cmake/bullet)

project(Game)

## [discover_ogre]
# specify which version and components you need
find_package(Freetype)
find_package(OGRE 1.11 REQUIRED COMPONENTS Bites RTShaderSystem)
find_package(Bullet 2.86)

# copy resource.cfg next to our binaries where OGRE looks for it
file(COPY ${OGRE_CONFIG_DIR}/resources.cfg DESTINATION "${CMAKE_BINARY_DIR}")
## [discover_ogre]

include_directories(${BULLET_INCLUDE_DIR})


set(IMGUI_SRCS ${pwd}/ogre-imgui/imgui/imgui.cpp ${pwd}/ogre-imgui/imgui/imgui_draw.cpp ${pwd}/ogre-imgui/imgui/imgui_demo.cpp)
set(OGRE_IMGUI_SRCS ${pwd}/ogre-imgui/ImguiManager.cpp ${pwd}/ogre-imgui/ImguiRenderable.cpp)
if(FREETYPE_FOUND)
    include_directories(${pwd}/ogre-imgui/imgui/misc/freetype/)
    list(APPEND IMGUI_SRCS ${pwd}/ogre-imgui/imgui/misc/freetype/imgui_freetype.cpp)
endif()


include_directories(${pwd}/ogre-imgui/ ${pwd}/ogre-imgui/imgui/)
add_library(OgreImgui ${IMGUI_SRCS} ${OGRE_IMGUI_SRCS})
target_link_libraries(OgreImgui PUBLIC ${OGRE_LIBRARIES})

if(FREETYPE_FOUND)
    target_compile_definitions(OgreImgui PRIVATE -DUSE_FREETYPE)
    target_include_directories(OgreImgui PRIVATE ${FREETYPE_INCLUDE_DIRS})
    target_link_libraries(OgreImgui PRIVATE ${FREETYPE_LIBRARIES})
endif()

# add files from this dir 
AUX_SOURCE_DIRECTORY(${pwd} src)
add_executable(${PROJECT_NAME} ${src})


message(STATUS "${PROJECT_NAME} added, files ${src}")

## [link sdl for sound]
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
## [link sdl for sound]

target_link_libraries(${PROJECT_NAME} ${OGRE_LIBRARIES} ${BULLET_LIBRARIES} ${SDL2_LIBRARIES} OgreImgui)


# found on stack overflow in order to add a simple "make run" command that builds and executes the project
add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
