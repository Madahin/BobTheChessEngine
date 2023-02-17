set(CMAKE_SYSTEM_NAME Linux)

# cross compilers to use for C and C++
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

# message(STATUS ${CMAKE_CXX_COMPILER})

# target environment on the build host system
#   set 1st to dir with the cross compiler's C/C++ headers/libs
set(CMAKE_FIND_ROOT_PATH /usr/bin)

include(${CMAKE_CURRENT_LIST_DIR}/Toolchain-common-flags.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-z,relro -Wl,-z,now")
