cmake_minimum_required(VERSION 3.26)
project(pacmanv0)

set(CMAKE_CXX_STANDARD 17)

add_executable(pacmanv0
        main.cpp
        Game_logic/World.h
        Game_logic/World.cpp
        Game_logic/Utils/Random.h
        Game_logic/Entities/Subject.h
        Game_logic/Entities/EntityModel.h
        Game_logic/Entities/EntityModel.cpp
        Game_logic/Entities/Collectable/Collectable.h
        Game_logic/Entities/Collectable/Collectable.cpp
        Game_logic/Entities/Collectable/Coin.h
        Game_logic/Entities/Collectable/Coin.cpp
        Game_logic/Entities/Collectable/Fruit.h
        Game_logic/Entities/Collectable/Fruit.cpp
        Game_logic/Observer.h
        Game_representation/EntityView.h
        Game_representation/EntityView.cpp
        Game_logic/Entities/PacMan/PacMan.h
        Game_logic/Entities/PacMan/PacMan.cpp
        Game_logic/Entities/Wall/Wall.h
        Game_logic/Entities/Wall/Wall.cpp
        Game_logic/Factory/EntityFactory.h
        Game_logic/Factory/EntityFactory.cpp
        Game_logic/Entities/Ghost/Ghost.h
        Game_logic/Entities/Ghost/Ghost.cpp
        Game_logic/Utils/Position.h
        Game_logic/Utils/Position.cpp
        Game_logic/Utils/Stopwatch.h
)
