FIND_PACKAGE(OpenGL)
cmake_minimum_required(VERSION 3.25)
project(canvas_clion)

set(CMAKE_CXX_STANDARD 11)

set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

add_executable(
        canvas_clion
        include/GL/freeglut.h
        include/GL/freeglut_ext.h
        include/GL/freeglut_std.h
        include/GL/glut.h
        src/main.cpp
        src/Vector2.h
        src/gl_canvas2d.cpp src/gl_canvas2d.h src/base/interfaces/IRender.h src/base/vectors/Vector2D.h src/base/interfaces/IMouse.h src/base/interfaces/IEntity.h src/SceneManager.h src/SceneManager.cpp src/base/interfaces/IKeyboard.h src/base/Utils.h src/actors/Spaceship.cpp src/actors/Spaceship.h src/actors/Bullet.cpp src/actors/Bullet.h src/actors/Monster.cpp src/actors/Monster.h)

target_link_libraries(canvas_clion ${OpenGlLinkers})