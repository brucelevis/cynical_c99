cmake_minimum_required(VERSION 3.8.2)
project(raw_gl)

set(CMAKE_C_STANDARD 99)

add_definitions(-DDEV)

include_directories(deps/include;src/)
add_executable(raw_gl src/main.c src/common.h src/graphics.h src/file.h src/file.c src/graphics.c src/glmc/ src/math/maths.h src/math/vec3.c src/math/vec2.c src/math/vec4.c src/math/quat.c src/math/mat4.c)
target_link_libraries(raw_gl "-L${CMAKE_SOURCE_DIR}/deps/lib -lopengl32 -lkernel32 -lgdi32 -lglfw3dll -luser32 -lglew32")

file(COPY deps/bin/ DESTINATION .)
file(COPY data DESTINATION .)