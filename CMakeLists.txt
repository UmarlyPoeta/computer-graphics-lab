cmake_minimum_required(VERSION 3.15)
project(ComputerGraphicsLabs C CXX)

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

set(GLM_INCLUDE "${DEPS_DIR}/GLM")

# ─── GLAD as a small library ──────────────────────────────────────────────────
add_library(glad STATIC ${GLAD_SRC})
target_include_directories(glad PUBLIC ${GLAD_INCLUDE})

# ─── Find system OpenGL ───────────────────────────────────────────────────────
find_package(OpenGL REQUIRED)

# ─── Helper macro ─────────────────────────────────────────────────────────────
macro(add_lab TARGET SRC)
    add_executable(${TARGET} ${SRC})
    target_include_directories(${TARGET} PRIVATE
        ${GLFW_INCLUDE}
        ${GLAD_INCLUDE}
        ${GLM_INCLUDE}          # ← dodaj tę linię
    )
    target_link_directories(${TARGET} PRIVATE ${GLFW_LIB_DIR})
    if(WIN32)
        target_link_libraries(${TARGET} PRIVATE glad OpenGL::GL glfw3 gdi32 user32 shell32)
    else()
        target_link_libraries(${TARGET} PRIVATE glad OpenGL::GL glfw)
    endif()
endmacro()

# ─── Labs ─────────────────────────────────────────────────────────────────────
add_subdirectory(lab1)
add_subdirectory(lab2)
add_subdirectory(lab3)
add_subdirectory(lab4)
add_subdirectory(lab5)
add_subdirectory(lab6)
