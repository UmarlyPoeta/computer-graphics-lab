cmake_minimum_required(VERSION 3.15)
project(ComputerGraphicsLabs CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ─── Paths ────────────────────────────────────────────────────────────────────
# Put GLFW and GLAD under deps/ (see deps/README.md)
set(DEPS_DIR "${CMAKE_SOURCE_DIR}/deps")

# GLFW
set(GLFW_INCLUDE "${DEPS_DIR}/GLFW/include")
set(GLFW_LIB_DIR "${DEPS_DIR}/GLFW/lib")

# GLAD  (drop glad.c + include/glad/ here)
set(GLAD_SRC "${DEPS_DIR}/GLAD/src/gl.c")
set(GLAD_INCLUDE "${DEPS_DIR}/GLAD/include")

# ─── GLAD as a small library ──────────────────────────────────────────────────
add_library(glad STATIC ${GLAD_SRC})
target_include_directories(glad PUBLIC ${GLAD_INCLUDE})

# ─── Find system OpenGL ───────────────────────────────────────────────────────
find_package(OpenGL REQUIRED)

# ─── Helper macro ─────────────────────────────────────────────────────────────
macro(add_lab TARGET SRC)
    add_executable(${TARGET} ${SRC})
    target_include_directories(${TARGET} PRIVATE ${GLFW_INCLUDE} ${GLAD_INCLUDE})
    target_link_directories(${TARGET} PRIVATE ${GLFW_LIB_DIR})
    target_link_libraries(${TARGET} PRIVATE glad OpenGL::GL glfw3)
    if(WIN32)
        target_link_libraries(${TARGET} PRIVATE gdi32 user32 shell32)
    endif()
endmacro()

# ─── Labs ─────────────────────────────────────────────────────────────────────
add_subdirectory(lab1)
add_subdirectory(lab2)
add_subdirectory(lab3)
