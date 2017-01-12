
cmake_minimum_required (VERSION 3.5)

project (CubicGL)

# test console
add_executable (cubic main_test.cc Cube.cc)

# openGL
add_executable (cubic_gl main.cc Cube.cc CubeGL.cc)

find_package (OpenGL REQUIRED)
find_package (GLUT REQUIRED)

include_directories ( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )

target_link_libraries (cubic_gl ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})




