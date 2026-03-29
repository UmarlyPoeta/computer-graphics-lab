# lab6/CMakeLists.txt

file(GLOB LAB6_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_lab(lab6 "${LAB6_SRC}")

target_include_directories(lab6 PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${GLM_INCLUDE}"
)

# Shadery obok binarki
add_custom_command(TARGET lab6 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:lab6>/shaders"
    COMMENT "Copying shaders for lab6..."
)