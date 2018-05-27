cmake_minimum_required(VERSION 3.8.2)
project(raw_gl)

set(CMAKE_C_STANDARD 99)

add_definitions(-DDEV)

include_directories(deps/include;src/)
add_executable(raw_gl src/main.c src/common.h src/graphics.h src/file.h src/file.c src/graphics.c src/glmc/ src/math/maths.h src/math/vec3.iln src/math/vec2.iln src/math/vec4.iln src/math/quat.iln src/math/mat4.iln src/math/transform.iln src/math/test.h src/stb_image.h src/string_helper.c src/string_helper.h src/resources.h src/resources.c)
target_link_libraries(raw_gl "-L${CMAKE_SOURCE_DIR}/deps/lib -lopengl32 -lkernel32 -lgdi32 -lglfw3dll -luser32 -lglew32")

#file(COPY deps/bin/ DESTINATION .)
file(COPY run_tree/data DESTINATION .)