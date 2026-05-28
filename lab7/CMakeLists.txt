# lab7/CMakeLists.txt

file(GLOB LAB7_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_lab(lab7 "${LAB7_SRC}")

target_include_directories(lab7 PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${GLM_INCLUDE}"
)

# Shadery obok binarki
add_custom_command(TARGET lab7 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:lab7>/shaders"
    COMMENT "Copying shaders for lab7..."
)
