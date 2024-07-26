cmake_minimum_required(VERSION 3.15)

project(OpenGL)
find_package(OpenGL REQUIRED)


add_executable(l1 ${PROJECT_SOURCE_DIR}/src/l1.cpp 
                  ${PROJECT_SOURCE_DIR}/include/callback/callback.cpp 
                  ${PROJECT_SOURCE_DIR}/include/util/util.cpp 
                  ${PROJECT_SOURCE_DIR}/include/util/Shader.cpp
                  ${PROJECT_SOURCE_DIR}/libs/image-reader/stb_image.cpp
            )

option(GLEW_STATIC "Use the static version of the gluw" ON)
if (GLEW_STATIC)
    target_compile_definitions(l1 PRIVATE "GLEW_STATIC")
endif()

target_include_directories(l1 PUBLIC ${PROJECT_SOURCE_DIR}/libs PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(l1 PUBLIC "D:/trungdung/LIBS/glfw-3.4.bin.WIN64/glfw-3.4.bin.WIN64/lib-mingw-w64/libglfw3.a"
                          PUBLIC "D:/trungdung/LIBS/glew-2.1.0-win32/glew-2.1.0/lib/Release/x64/glew32s.lib"
                          PUBLIC OpenGL::GL)