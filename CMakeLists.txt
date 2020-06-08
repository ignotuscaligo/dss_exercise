cmake_minimum_required(VERSION 3.14)

project(dss_exercise)

if(APPLE)
    set(OPENSSL_ROOT_DIR /usr/local/opt/openssl/)
    set(OPENSSL_LIBRARIES /usr/local/opt/openssl/lib)
endif()

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(cpprestsdk REQUIRED)
find_package(SDL2       REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx   REQUIRED)
find_package(SDL2_ttf   REQUIRED)
find_package(spdlog     REQUIRED)

if(WIN32)
    add_executable(dss_exercise WIN32)
elseif(APPLE)
    add_executable(dss_exercise MACOSX_BUNDLE)
else()
    add_executable(dss_exercise)
endif()

target_sources(dss_exercise
    PRIVATE
        "src/main.cpp"
        "src/Application.cpp"
        "src/mlb/Game.cpp"
        "src/mlb/Stats.cpp"
        "src/utility/string.cpp"
        "src/utility/logging.cpp"
        "src/render/Window.cpp"
        "src/render/Renderer.cpp"
        "src/render/Texture.cpp"
        "src/render/ImageTexture.cpp"
        "src/render/TextTexture.cpp"
        "src/render/Context.cpp"
        "src/render/Font.cpp"
        "src/rest/Tasks.cpp"
        "src/ui/Vector2.cpp"
        "src/ui/Rect.cpp"
        "src/ui/Item.cpp"
        "src/ui/ImageItem.cpp"
        "src/ui/TextItem.cpp"
        "src/ui/RectangleItem.cpp"
        "src/ui/RowLayout.cpp"
        "src/ui/GameItem.cpp"
        "src/ui/ViewController.cpp"
        "src/input/State.cpp"
        "src/resources/Roboto-Medium.ttf"
)

if(WIN32)
    target_sources(dss_exercise
        PRIVATE
            "src/utility/logging_WIN32.cpp"
    )
else()
    target_sources(dss_exercise
        PRIVATE
            "src/utility/logging_DEFAULT.cpp"
    )
endif()

target_include_directories(dss_exercise
    PRIVATE
        "src/"
)

target_link_libraries(dss_exercise
    PRIVATE
        cpprestsdk::cpprest
        spdlog::spdlog
        SDL2::SDL2
        SDL2::SDL2_image
        SDL2::SDL2_gfx
        SDL2::SDL2_ttf
)

target_compile_features(dss_exercise
    PUBLIC
        cxx_std_11
)

if(APPLE)
    set_target_properties(dss_exercise
        PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST  "${CMAKE_CURRENT_SOURCE_DIR}/src/resources/Info.plist.in"
            MACOSX_BUNDLE_BUNDLE_NAME "dss_exercise"
            RESOURCE                  "src/resources/Roboto-Medium.ttf"
    )
else()
    add_custom_command(
        TARGET dss_exercise POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/src/resources/Roboto-Medium.ttf" "${CMAKE_CURRENT_BINARY_DIR}/Roboto-Medium.ttf"
    )
endif()
