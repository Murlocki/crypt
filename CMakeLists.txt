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
        src/library/basic_math/base_operations.cpp
        src/library/extra_functions/convertions.cpp
        src/library/polynoms/PolynomialSolver.cpp
        src/library/basic_math/numbers.cpp
        src/library/codes/DES.cpp
        src/library/basic_math/chinese_lefts.cpp
        src/library/basic_math/linear_congruence.cpp
        src/library/basic_math/diofant_equasion.cpp
        src/library/basic_math/quadratic_congruence.cpp
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
    get_filename_component(Python_SITEARCH ${Python_EXECUTABLE}/../../Lib/site-packages ABSOLUTE)
    message(STATUS "Python site-packages: ${Python_SITEARCH}")

    # Настройка pybind11 (добавлено здесь, чтобы было доступно для всех целей)
    find_package(pybind11 REQUIRED)
    find_package(Python REQUIRED COMPONENTS Development)
    pybind11_add_module(crypto_learn
            src/python/module.cpp
    )
    add_library(convertions src/python/convertions.cpp)
    target_link_libraries(crypto_learn PRIVATE
            gmp_utils
            convertions
    )
    include_directories(
            ${Python_INCLUDE_DIRS}
    )

    execute_process(
            COMMAND ${Python_EXECUTABLE} -c "import site; print(site.getsitepackages()[0])"
            OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # Установка модуля
    install(TARGETS crypto_learn
            LIBRARY DESTINATION ${PYTHON_SITE_PACKAGES}
            RUNTIME DESTINATION ${PYTHON_SITE_PACKAGES}
    )

    # Установка зависимых DLL (для Windows)
    if(WIN32)
        install(FILES
                ${CMAKE_BINARY_DIR}/gmp-10.dll
                ${CMAKE_BINARY_DIR}/gmpxx-4.dll
                DESTINATION ${PYTHON_SITE_PACKAGES}
        )
    endif()

    message(STATUS "Python модуль будет установлен в: ${PYTHON_SITE_PACKAGES}")
    # "C:\Program Files\JetBrains\CLion 2024.3.5\bin\cmake\win\x64\bin\cmake.exe" --install . --config Release
endif()