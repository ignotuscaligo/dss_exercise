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
        "src/Application.cpp"
        "src/mlb/Game.cpp"
        "src/utility/string.cpp"
        "src/utility/logging.cpp"
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
)

if(UNIX AND NOT APPLE)
    # In order to have consistent #include directives across platforms,
    # use the "<SDL2>/include" directory as the root rather than "<SDL2>/include/SDL2"
    # that would be included by using SDL2_INCLUDE_DIRECTORIES
    target_include_directories(dss_exercise
        PRIVATE
            ${SDL2_EXEC_PREFIX}/include
    )

    # When libsdl2-dev is installed on Ubuntu via apt, the package does not create the
    # SDL2:: targets, so the library needs to be linked using an older method
    target_link_libraries(dss_exercise
        PRIVATE
            ${SDL2_LIBRARIES}
    )
else()
    target_link_libraries(dss_exercise
        PRIVATE
            SDL2::SDL2
            SDL2::SDL2main
    )
endif()

target_compile_features(dss_exercise
    PUBLIC
        cxx_std_11
)
