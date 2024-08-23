cmake_minimum_required(VERSION 3.5)

project(snake VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Werror -fsanitize=address"
  )


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)



add_executable(
    snake 

    gui/desktop/desk.cpp 
    gui/desktop/mainwindow.cpp 
    controller/controller.cpp 
    brick_game/model.cpp 
    brick_game/snake/backend/apple.cpp
    brick_game/snake/backend/body.cpp 
    brick_game/snake/backend/map.cpp 
    brick_game/snake/backend/serv.cpp 
    brick_game/snake/backend/snakes.cpp 
    brick_game/tetris/backend/blocks.c
    brick_game/tetris/backend/fsm.c 
    brick_game/tetris/backend/lines.c 
    brick_game/tetris/backend/serv.c 
    brick_game.cpp
)

target_link_libraries(snake PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(snake PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(snake)
endif()
