cmake_minimum_required(VERSION 3.25)
project(BabySmasherGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)
find_package(SDL2_ttf REQUIRED CONFIG)
find_package(SDL2_mixer REQUIRED CONFIG)

file(GLOB_RECURSE GAME_SOURCES
    "${CMAKE_SOURCE_DIR}/BabySmasherGame/src/*.cpp"
)
file(GLOB_RECURSE GAME_HEADERS
    "${CMAKE_SOURCE_DIR}/BabySmasherGame/src/*.h"
)

if(APPLE)
    add_executable(BabySmasherGame MACOSX_BUNDLE
        ${GAME_SOURCES}
        ${GAME_HEADERS}
    )

    set_target_properties(BabySmasherGame PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.ergun.babysmasher"
        MACOSX_BUNDLE_BUNDLE_NAME "BabySmasherGame"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/BabySmasherGame/Info.plist"
    )

    if(APPLE)
    set_target_properties(BabySmasherGame PROPERTIES
        MACOSX_BUNDLE_ICON_FILE "AppIcon.icns"
    )

    add_custom_command(TARGET BabySmasherGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_SOURCE_DIR}/BabySmasherGame/assets/AppIcon.icns"
            "$<TARGET_BUNDLE_CONTENT_DIR:BabySmasherGame>/Resources/AppIcon.icns"
    )
endif()

else()
    add_executable(BabySmasherGame
        ${GAME_SOURCES}
        ${GAME_HEADERS}
    )
endif()


target_include_directories(BabySmasherGame PRIVATE
    ${CMAKE_SOURCE_DIR}/BabySmasherGame/src
)


target_link_libraries(BabySmasherGame PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
)

if(APPLE)
    message(STATUS "Building for macOS")
    target_compile_definitions(BabySmasherGame PRIVATE PLATFORM_MACOS=1)
elseif(WIN32)
    message(STATUS "Building for Windows")
    target_compile_definitions(BabySmasherGame PRIVATE PLATFORM_WINDOWS=1)
elseif(UNIX)
    message(STATUS "Building for Linux")
    target_compile_definitions(BabySmasherGame PRIVATE PLATFORM_LINUX=1)
endif()


set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/BabySmasherGame/assets")

if(APPLE)
    add_custom_command(TARGET BabySmasherGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${ASSETS_DIR}"
            "$<TARGET_BUNDLE_CONTENT_DIR:BabySmasherGame>/Resources/assets"
    )
else()
    add_custom_command(TARGET BabySmasherGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${ASSETS_DIR}"
            "$<TARGET_FILE_DIR:BabySmasherGame>/assets"
    )
endif()