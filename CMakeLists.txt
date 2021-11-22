cmake_minimum_required(VERSION 3.0.0)
project(OpenGL_Start VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

include(CTest)
enable_testing()
set(GLAD_H ${PROJECT_SOURCE_DIR}/include)
set(GLFW_H /usr/local/include)
set(UTILS ${PROJECT_SOURCE_DIR}/utils)

include_directories(${GLAD_H} ${GLFW_H} ${UTILS})

set(GLFW_LINK /usr/local/lib/libglfw.3.3.dylib)
LINK_LIBRARIES(${GLFW_LINK})

set(SOURCES glad.c main.cpp ${UTILS}/glutils.cpp ${UTILS}/shapeutils.cpp ${UTILS}/shader.cpp)
add_executable(output ${SOURCES})

if (APPLE)
    target_link_libraries(output "-framework OpenGL")
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
