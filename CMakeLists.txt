cmake_minimum_required (VERSION 3.5)


list(APPEND CMAKE_MODULE_PATH 
    ${CMAKE_SOURCE_DIR}/modules
)


include(compiler-config)
include(folders)




project(app LANGUAGES CXX)
basic_project(APP)

include_directories(${PROJECT_NAME} ${INC_DIR})
add_executable(${PROJECT_NAME} ${SRC_FILES})

# set compile options for the main executable
target_compile_options(${PROJECT_NAME} PRIVATE ${CXX_FLAGS}
     "$<$<CONFIG:Debug>:${CXX_FLAGS_DEBUG}>"
     "$<$<CONFIG:Release>:${CXX_FLAGS_RELEASE}>")