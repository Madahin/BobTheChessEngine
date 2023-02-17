##############################
#          Variables         #
##############################

glob_file(
        OUTPUT
        Engine_src
        INPUT_FILES
        *.cpp
        *.h
)

set (Engine_link
    spdlog::spdlog
)

##############################
#           Binary           #
##############################

add_executable(${PROJECT_NAME} ${Engine_src})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

##############################
#             Link           #
##############################

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${Engine_link}
)

##############################
#             Misc           #
##############################

# Replace the project path to '.' when using __FILE__
target_compile_options(${PROJECT_NAME} PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")