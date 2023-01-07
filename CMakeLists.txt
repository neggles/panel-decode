cmake_minimum_required(VERSION 3.16.0)
project(panel-decoder VERSION 0.1.0 LANGUAGES C)

# Set build type if not specified
if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# CMake Options
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_SKIP_INSTALL_RULES ON)

# Toolchain Binaries
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_COMPILER    clang   CACHE FILEPATH "C Compiler")
set(CMAKE_CXX_COMPILER  clang++ CACHE FILEPATH "C++ Compiler")
set(CMAKE_ASM_COMPILER  clang   CACHE FILEPATH "ASM Compiler")
set(CMAKE_LINKER        ld.lld  CACHE FILEPATH "Linker Binary")
# use LLVM binutils
set(_CMAKE_TOOLCHAIN_PREFIX llvm-)

# Toolchain Flags
list(APPEND LLVM_CLANG_FLAGS "-funsigned-char")
list(JOIN LLVM_CLANG_FLAGS " " LLVM_CLANG_FLAGS)

# Common
set(CMAKE_ASM_FLAGS "${LLVM_CLANG_FLAGS}" CACHE INTERNAL "ASM Compiler options")
set(CMAKE_C_FLAGS "${LLVM_CLANG_FLAGS}" CACHE INTERNAL "C Compiler options")

# Ninja monkey patch. Should be fixed in cmake 3.18
# Defaults to "-MD -MT <OBJECT> -MF <DEPFILE>" ('as' no likey).
set(CMAKE_DEPFILE_FLAGS_ASM "")

file(GLOB srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_executable(panel-decoder ${srcs})
target_include_directories(panel-decoder PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
