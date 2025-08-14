
add_executable(app main.cpp utils.cpp)

if (UNIX)
set_target_properties(app PROPERTIES
    BUILD_RPATH "\$ORIGIN"
)

endif()


target_link_libraries(app PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)