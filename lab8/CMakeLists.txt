# lab8/CMakeLists.txt

file(GLOB LAB8_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_lab(lab8 "${LAB8_SRC}")

target_include_directories(lab8 PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${GLM_INCLUDE}"
)

# Shadery i tekstury obok binarki
add_custom_command(TARGET lab8 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:lab8>/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/textures"
        "$<TARGET_FILE_DIR:lab8>/textures"
    COMMENT "Copying shaders/textures for lab8..."
)
