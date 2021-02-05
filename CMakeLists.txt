cmake_minimum_required(VERSION 3.17)
project(DigDugSFML)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Tile.cpp Tile.h Point.h Dimensions.h TileMap.cpp TileMap.h TileMapRenderer.cpp TileMapRenderer.h TileRenderer.cpp TileRenderer.h Character.cpp Character.h Player.cpp Player.h Enemy.cpp Enemy.h Direction.h Dragon.h)
add_executable(DigDugSFML ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(DigDugSFML sfml-system sfml-window sfml-graphics sfml-audio)


