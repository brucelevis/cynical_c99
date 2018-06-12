cmake_minimum_required(VERSION 3.8.2)
project(raw_gl)

set(CMAKE_C_STANDARD 99)

add_compile_options(-w)
add_definitions(-DDEV)

include_directories(deps/include;src/)
add_executable(raw_gl src/main.c src/common.h src/graphics.h src/file.h src/file.c src/graphics.c src/glmc/ src/math/maths.h src/math/vec3.h src/math/vec2.h src/math/vec4.h src/math/quat.h src/math/mat4.h src/math/transform.h src/math/test.h src/stb_image.h src/string_helper.c src/string_helper.h src/resources.h src/resources.c src/hot_reloader.h src/hot_reloader.c src/engine.h src/resource_manager.h src/resource_manager.c src/_TRASH/test_resource_manager.h src/memory.h src/memory.c src/input.h src/input.c src/_TRASH/test_memory.h src/test_games/pong.c src/engine.c src/test_games/asteroids.c src/stb_truetype.h src/text.c src/text.h)
target_link_libraries(raw_gl "-L${CMAKE_SOURCE_DIR}/deps/lib -lopengl32 -lkernel32 -lgdi32 -lglfw3dll -luser32 -lglew32")

#file(COPY deps/bin/ DESTINATION .)
file(COPY run_tree/data DESTINATION .)