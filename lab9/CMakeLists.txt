# lab9/CMakeLists.txt

file(GLOB LAB9_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_lab(lab9 "${LAB9_SRC}")

target_include_directories(lab9 PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${GLM_INCLUDE}"
)

# Shadery i tekstury obok binarki
add_custom_command(TARGET lab9 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:lab9>/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/textures"
        "$<TARGET_FILE_DIR:lab9>/textures"
    COMMENT "Copying shaders/textures for lab9..."
)
