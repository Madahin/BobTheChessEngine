cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0069 NEW)
include(CheckIPOSupported)

project(BobTheChessEngine
    VERSION 0.0.1
    LANGUAGES C CXX
)

##############################
#      External options      #
##############################

option(CHESS_BUILD_TEST "Build tests" ON)


##############################
#      Internal options      #
##############################

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)
set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> -crD <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_APPEND "<CMAKE_AR> -rD <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_FINISH "<CMAKE_RANLIB> -D <TARGET>")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PLATFORM_ARCH "64bit")
    add_compile_definitions(ARCH64)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(PLATFORM_ARCH "32bit")
    add_compile_definitions(ARCH32)
else()
    message(FATAL_ERROR "Invalide architecture")
endif()

if(WIN32)
    set(PLATFORM_NAME "Windows")
else()
    set(PLATFORM_NAME "Linux")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
endif()

string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_NAME)

message(STATUS "platorm name: ${PLATFORM_NAME}")
message(STATUS "platorm arch: ${PLATFORM_ARCH}")
message(STATUS "build type: ${BUILD_TYPE_NAME}")

# SOURCE_DATE_EPOCH should be set to the last commit timestamp, preferably with `git log -1 --pretty=%ct`
if (NOT DEFINED ENV{SOURCE_DATE_EPOCH})
    execute_process(
            COMMAND git log -1 --pretty=%ct
            OUTPUT_VARIABLE SOURCE_DATE_EPOCH_TMP
            OUTPUT_STRIP_TRAILING_WHITESPACE
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    set(ENV{SOURCE_DATE_EPOCH} ${SOURCE_DATE_EPOCH_TMP})
endif()
string(TIMESTAMP C_TIME "%Y-%m-%dT%H:%M:%SZ" UTC)
message(STATUS "Build date: ${C_TIME}")


check_ipo_supported(RESULT ipo_supported OUTPUT ipo_error)
if( ipo_supported )
    message(STATUS "IPO / LTO enabled")
else()
    message(STATUS "IPO / LTO not supported: <${ipo_error}>")
endif()

##############################
#        Dependencies        #
##############################

include(${CMAKE_SOURCE_DIR}/cmake/scripts/utilities.cmake)
add_subdirectory(dependencies)

##############################
#         Executables        #
##############################

add_subdirectory(Engine)

if (CHESS_BUILD_TEST)
    add_subdirectory(test)
endif()
