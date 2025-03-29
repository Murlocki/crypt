cmake_minimum_required(VERSION 3.20)
project(crypto)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TOOLCHAIN_FILE "C:/Users/kirill/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake")


# Настройка GMP
find_package(PkgConfig REQUIRED)
pkg_check_modules(gmp REQUIRED IMPORTED_TARGET gmp)
pkg_check_modules(gmpxx REQUIRED IMPORTED_TARGET gmpxx)
#include_directories("C:/Users/kirill/.vcpkg-clion/vcpkg/installed/x64-windows/include")

# Общая библиотека
add_library(gmp_utils STATIC
        src/library/basic_math/gmp_utils.cpp
        src/library/basic_math/base_operations.cpp
)

target_link_libraries(gmp_utils PRIVATE
        PkgConfig::gmp
        PkgConfig::gmpxx
)
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include  # Для #include "basic_math/..."
        ${CMAKE_CURRENT_SOURCE_DIR}/src      # Для внутренних включений
        ${gmp_INCLUDE_DIRS}
        ${gmpxx_INCLUDE_DIRS}
)

# Консольное приложение
add_executable(main_test
        src/main.cpp
)
target_link_libraries(main_test PRIVATE gmp_utils)

# Python модуль (опционально)
option(BUILD_PYTHON_MODULE "Build Python module" ON)

if(BUILD_PYTHON_MODULE)
    # Настройка pybind11 (добавлено здесь, чтобы было доступно для всех целей)
    find_package(pybind11 REQUIRED)
    find_package(Python REQUIRED COMPONENTS Development)
    pybind11_add_module(my_module
            src/python/module.cpp
    )

    target_link_libraries(my_module PRIVATE
            gmp_utils
    )
endif()