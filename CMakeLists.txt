cmake_minimum_required(VERSION 3.14)

project(dss_exercise)

if(APPLE)
    set(OPENSSL_ROOT_DIR /usr/local/opt/openssl/)
    set(OPENSSL_LIBRARIES /usr/local/opt/openssl/lib)
endif()

add_executable(dss_exercise)

target_sources(dss_exercise
    PRIVATE
        "src/main.cpp"
)

target_compile_features(dss_exercise
    PUBLIC
        cxx_std_11
)
