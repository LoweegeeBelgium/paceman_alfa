#ifndef PACMANV0_WORLD_H
#define PACMANV0_WORLD_H
#include "Entities/PacMan/PacMan.h"
#include "Entities/Wall/Wall.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Utils/json.hpp"
#include "Factory/EntityFactory.h"
#include "Utils/Random.h"

using namespace nlohmann;

class World {
public:
    //non filtered map in input
    World(const std::string& map);
    World() = default;

    void reset();

    //implement collision
    void pacman_handle_collision(std::shared_ptr<PacMan> pacMan);
    void handle_wall_collision(std::shared_ptr<EntityModel> e);
    void ghost_AI(std::shared_ptr<Ghost> g);
    void ghost_random(std::shared_ptr<Ghost> g);
    void ghost_manhattan_distance(std::shared_ptr<Ghost> g);
    //void spawnEntity();
    void update_index();

    //Getters and Setters

    bool isDeath() const;
    bool isSuccessed() const;
    std::vector<std::shared_ptr<EntityModel>> getEntities() const;
    bool matrixisation(std::string& filtered_map, std::vector<std::vector<int>>& matrix);

    std::vector<std::vector<std::shared_ptr<EntityModel>>> getPositionalIndex();

    Direction getDirectionFromPositionDifference(const Position& diff);

    Position getPositionDifferenceFromDirection(Direction dir);

    bool is_available_direction(std::shared_ptr<Ghost> g);

    std::vector<Direction> available_directions(std::shared_ptr<Ghost> g);

    float manhattan_distance(Position& p1, Position& p2);

    Position get_pacman_position(std::shared_ptr<PacMan> pacman);

    std::vector<std::shared_ptr<EntityModel>> get_ghosts();

    void ghost_out_of_the_spawner(std::shared_ptr<Ghost> g, double deltatime);

    bool is_on_a_corner(int directions_size, std::shared_ptr<Ghost> g);
    bool is_on_an_intersection(int directions_size, std::shared_ptr<Ghost> g);
    void ghost_decision(std::shared_ptr<Ghost> g,  std::vector<Direction> directions);

private:
    bool _successed;
    bool _death;

    std::vector<std::shared_ptr<EntityModel>> _entities;
    std::vector<std::vector<std::shared_ptr<EntityModel>>> _positional_index;
    std::vector<std::shared_ptr<EntityModel>> _ghosts;
    std::shared_ptr<EntityModel> _pacman;


};


#endif //PACMANV0_WORLD_H
