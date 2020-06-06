cmake_minimum_required(VERSION 3.14)

project(dss_exercise)

if(APPLE)
    set(OPENSSL_ROOT_DIR /usr/local/opt/openssl/)
    set(OPENSSL_LIBRARIES /usr/local/opt/openssl/lib)
endif()

find_package(cpprestsdk REQUIRED)
find_package(SDL2       REQUIRED)
find_package(spdlog     REQUIRED)

if(WIN32)
    add_executable(dss_exercise WIN32)
else()
    add_executable(dss_exercise)
endif()

target_sources(dss_exercise
    PRIVATE
        "src/main.cpp"
        "src/mlb/Game.cpp"
        "src/utility/string.cpp"
)

target_include_directories(dss_exercise
    PRIVATE
        "src/"
)

target_link_libraries(dss_exercise
    PRIVATE
        cpprestsdk::cpprest
        SDL2::SDL2
        SDL2::SDL2main
        spdlog::spdlog
)

target_compile_features(dss_exercise
    PUBLIC
        cxx_std_11
)
