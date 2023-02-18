enable_testing()
include(GoogleTest)

##############################
#          Variables         #
##############################

glob_file(
    OUTPUT
    Test_src
    INPUT_FILES
    *.cpp
    *.h
    ${CMAKE_SOURCE_DIR}/Engine/*.cpp
    ${CMAKE_SOURCE_DIR}/Engine/*.h
)

list(REMOVE_ITEM Test_src ${CMAKE_SOURCE_DIR}/Engine/src/main.cpp)

set (Test_link
    gtest
    gtest_main
    spdlog::spdlog
)

##############################
#           Binary           #
##############################

add_executable(${PROJECT_NAME}_test ${Test_src})

target_include_directories(${PROJECT_NAME}_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME}_test PRIVATE ${CMAKE_SOURCE_DIR}/Engine/include)

##############################
#             Link           #
##############################

target_link_libraries(${PROJECT_NAME}_test
    PUBLIC
    ${Test_link}
)

##############################
#             Misc           #
##############################

# Replace the project path to '.' when using __FILE__
target_compile_options(${PROJECT_NAME}_test PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")

# Generate CTest targets
gtest_discover_tests(${PROJECT_NAME}_test)