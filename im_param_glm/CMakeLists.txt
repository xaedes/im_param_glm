cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME im_param_glm)
project( ${PROJECT_NAME} )

include("compiler_options.cmake")

add_library(
    ${PROJECT_NAME} 
    INTERFACE
)

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
find_package(glm REQUIRED)    # glm::glm
target_link_libraries(${PROJECT_NAME} INTERFACE glm::glm)
target_link_libraries(${PROJECT_NAME} INTERFACE im_param)
