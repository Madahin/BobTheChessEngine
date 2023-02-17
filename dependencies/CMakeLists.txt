include(FetchContent)

option(USE_SYSTEM_DEPS CACHE OFF)
option(LINK_DEPS_STATIC CACHE ON)

# Don't build shared libs if we want to link to deps statically
if(LINK_DEPS_STATIC)
  set(BUILD_SHARED_LIBS OFF)
else()
  set(BUILD_SHARED_LIBS ON)
endif()

message(STATUS "Fetching third party libraries")
#======================================

set(GTEST_VERSION release-1.12.1)
set(SPDLOG_VERSION v1.11.0)

FetchContent_Declare(
  gtest
  URL           https://github.com/google/googletest/archive/refs/tags/${GTEST_VERSION}.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

FetchContent_Declare(
  spdlog
  URL           https://github.com/gabime/spdlog/archive/refs/tags/${SPDLOG_VERSION}.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

add_subdirectory(gtest)
add_subdirectory(spdlog)

#======================================
message(STATUS "Fetching thirdparty libraries done")
