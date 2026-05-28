# lab10/CMakeLists.txt

file(GLOB LAB10_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_lab(lab10 "${LAB10_SRC}")

target_include_directories(lab10 PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${GLM_INCLUDE}"
)

# Shadery i tekstury obok binarki
add_custom_command(TARGET lab10 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:lab10>/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/textures"
        "$<TARGET_FILE_DIR:lab10>/textures"
    COMMENT "Copying shaders/textures for lab10..."
)
