
cmake_minimum_required(VERSION 3.10)
project(app_frustum_std3d LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(GLUT_ROOT "${CMAKE_SOURCE_DIR}/libs/glut")


include_directories(${GLUT_ROOT}/include)
link_directories(${GLUT_ROOT}/lib)


add_executable(app_frustum_std3d
   Main.cpp 
   AABox.cpp
   FrustumG.cpp
   Matrix.cpp
   Plane.cpp
   Render.cpp 
   Vec3.cpp
   View.cpp
   )


target_link_libraries(app_frustum_std3d 
    ${GLUT_ROOT}/lib/glut32.lib 
    # opengl32.lib 
    # glu32.lib
)

# Copy DLL-file to directory where execute file locates 
add_custom_command(TARGET app_frustum_std3d POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${GLUT_ROOT}/bin/glut32.dll
    $<TARGET_FILE_DIR:app_frustum_std3d>
)
