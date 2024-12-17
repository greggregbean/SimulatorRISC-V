cmake_minimum_required(VERSION 3.10)
project(SIMULATOR_RISC)

add_compile_options(
    -O3
    -flto
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(SIMULATOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCE_DIR "${SIMULATOR_DIR}/source")
set(INCLUDE_DIR "${SIMULATOR_DIR}/include")

if (LIBELF_LIBRARIES AND LIBELF_INCLUDE_DIRS)
  set (LibElf_FIND_QUIETLY TRUE)
endif (LIBELF_LIBRARIES AND LIBELF_INCLUDE_DIRS)

find_path (LIBELF_INCLUDE_DIRS
  NAMES
    libelf.h
  PATHS
    /usr/include
    /usr/include/libelf
    /usr/local/include
    /usr/local/include/libelf
    /opt/local/include
    /opt/local/include/libelf
    /sw/include
    /sw/include/libelf
    ENV CPATH)

find_library (LIBELF_LIBRARIES
  NAMES
    elf
  PATHS
    /usr/lib
    /usr/local/lib
    /opt/local/lib
    /sw/lib
    ENV LIBRARY_PATH
    ENV LD_LIBRARY_PATH)

<<<<<<< HEAD
include (FindPackageHandleStandardArgs)


# handle the QUIETLY and REQUIRED arguments and set LIBELF_FOUND to TRUE if all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibElf DEFAULT_MSG
  LIBELF_LIBRARIES
  LIBELF_INCLUDE_DIRS)

SET(CMAKE_REQUIRED_LIBRARIES elf)
INCLUDE(CheckCXXSourceCompiles)

mark_as_advanced(LIBELF_INCLUDE_DIRS LIBELF_LIBRARIES ELF_GETSHDRSTRNDX)

add_library(
    simulator
    source/decoder.cpp
    source/elf_loader.cpp
    source/executor.cpp
    source/hart.cpp
    source/memory.cpp
)

target_link_libraries(
    simulator
    PUBLIC
        ${LIBELF_LIBRARIES}
)

target_include_directories(
    simulator
    PUBLIC
        ${LIBELF_INCLUDE_DIRS}
)

target_include_directories(
    simulator
    PUBLIC
        ${INCLUDE_DIR}
)

add_library(SIMULATOR::Lib ALIAS simulator)
add_executable(simulate source/main.cpp)

target_link_libraries(simulate
  PRIVATE
  SIMULATOR::Lib
)
=======
add_executable(simulator ${SOURCES})

target_include_directories(simulator PRIVATE ${INCLUDE_DIR})

target_link_libraries(simulator PRIVATE ${ELF_LIBRARIES})
>>>>>>> a0ddc79 (made instruction cache)
