#include "World.h"
#include <chrono>
#include <thread>
#include "Utils/Stopwatch.h"
#include <cmath>


bool is_in_the_right_position(float n, float m){
    float error = 0.000005;
    if ((n > m - error) && (n < m + error)){
        return true;
    } else {
        return false;
    }
}

void World::ghost_decision(std::shared_ptr<Ghost> g, std::vector<Direction> directions){
    auto &random = Random::instance();
    int p = random.get_random_in_range(0,1);

    if (p == 1){
        Direction new_direction = random.get_random_direction(directions);
        g->setDirection(new_direction);
    } else {
        ghost_manhattan_distance(g);
    }

}

//SE è APPROSSIMATO A INTERO ALLORA ENTRA NEL GHOSTB CHOSICE MA PRIMA AGGIORNA LA POSIZIONE
bool is_approximated_to_integer(float number) {
    // Round the number to the 4th digit
    double roundedNumber = roundf(number * 1000.0) / 1000.0;
    float tolerance = 0.00001;
    //0.00001
    // Check if the rounded number is within the specified tolerance of an integer
    if (fabs(roundedNumber - roundf(roundedNumber)) <= tolerance) {
        return true;
    } else {
        return false;
    }
}

bool World::is_on_a_corner(int directions_size, std::shared_ptr<Ghost> g){
    float x,y;
    x = g->getPosition().getX();
    y = g->getPosition().getY();

    float supp_x = std::ceil(x);
    float supp_y = std::ceil(y);

    if ( (directions_size == 2) && (!is_available_direction(g)) &&
           (is_approximated_to_integer(x)) && (is_approximated_to_integer(y)) ){

        return true;
    }

    return false;
}

bool World::is_on_an_intersection(int directions_size, std::shared_ptr<Ghost> g){
    float x,y;
    x = g->getPosition().getX();
    y = g->getPosition().getY();

    float supp_x = std::ceil(x);
    float supp_y = std::ceil(y);

    if ( (directions_size >= 3) &&
    (is_approximated_to_integer(x)) &&
    (is_approximated_to_integer(y)) ){
        /*
        if (supp_x - x <= 0.999){
            g->setPosition(roundf(x), y);
        }
        if (supp_y - y <= 0.999){
            g->setPosition(x, roundf(y));
        }
         */
        return true;
    }

    return false;
}

const std::chrono::seconds interval(1);

std::vector<std::vector<std::shared_ptr<EntityModel>>> World::getPositionalIndex() {
    return _positional_index;
}

Position World::get_pacman_position(const std::shared_ptr<PacMan> pacman) {
    return pacman->getPosition();
}

std::vector<std::shared_ptr<EntityModel>> World::get_ghosts() {
    return _ghosts;
}


bool World::matrixisation(std::string &filtered_map, std::vector<std::vector<int>>& matrix) {

    json jsonArray = json::parse("[" + filtered_map + "]");

    if (jsonArray.is_array()) {
        // Create a 2D vector to store the matrix
        ;

        // Iterate through each array in the outer array
        for (const auto& rowArray : jsonArray) {
            // Check if the inner array is also an array
            if (rowArray.is_array()) {
                // Create a vector to store the current row
                std::vector<int> row;

                // Iterate through each element in the inner array
                for (const auto& element : rowArray) {
                    // Assuming the matrix elements are integers
                    row.push_back(element.get<int>());
                }

                // Add the current row to the matrix
                matrix.push_back(row);
            } else {
                std::cerr << "Invalid format for inner array!" << std::endl;
                return false; // Return an error code
            }
        }

        //std::cout << matrix[5][10]; it was a test
        // Now 'matrix' contains the parsed matrix data
        // You can use 'matrix' for further processing or analysis
    } else {
        std::cerr << "Invalid format for outer array!" << std::endl;
        return false; // Return an error code
    }
    return false;
}


//using a matrix to redefinite the string and a matrix to store all the shared pointers



//the position of pacman is represented by the number 1
World::World(const std::string& string_map): _death{false}, _successed{false} {

    // Read the JSON file into a string

    std::string filtered_string_map = string_map.substr(8,461);

    std::vector<std::vector<int>> matrix(0, std::vector<int>(20, 0));
    matrixisation(filtered_string_map, matrix);

    GhostFactory ghostFactory;
    CoinFactory coinFactory;
    FruitFactory fruitFactory;
    PacManFactory pacManFactory;
    WallFactory wallFactory;


    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t z = 0; z < matrix[i].size(); ++z) {


            if (matrix[i][z] == 1){
                auto entity = pacManFactory.createEntity(i, z);
                if (entity){
                    entity->setPosition(i,z);
                    _entities.push_back(entity);
                    _pacman = entity;
                }
            }

            if (matrix[i][z] == 2){
                auto entity = coinFactory.createEntity(i,z);
                if (entity){
                    entity->setPosition(i,z);
                    _entities.push_back(entity);
                }
            }

            if (matrix[i][z] == 3){
                auto entity = ghostFactory.createEntity(i,z);
                if (entity){
                    entity->setPosition(i,z);
                    _entities.push_back(entity);
                    _ghosts.push_back(entity);
                }
            }

            if (matrix[i][z] == 4){
                auto entity = fruitFactory.createEntity(i,z);
                if (entity){
                    entity->setPosition(i,z);
                    _entities.push_back(entity);
                }
            }

            if (matrix[i][z] == 5){
                auto entity = wallFactory.createEntity(i,z);
                if (entity){
                    entity->setPosition(i,z);
                    _entities.push_back(entity);
                }
            }

        }
    }

    _pacman->setSpeed(0.2);



    //_entities[0]->print_position();
    // printa le posizioni nel main e checka se funiona

    //here you create the positional index matrix
    std::vector<std::vector<std::shared_ptr<EntityModel>>> positional_index(
            matrix.size(), std::vector<std::shared_ptr<EntityModel>>(matrix[0].size(), nullptr));

    // Populate the positional index matrix with entities
    for (const auto& entity : _entities) {
        auto row = entity->getPosition().getX();
        auto col = entity->getPosition().getY();
        positional_index[row][col] = entity;
    }

    _positional_index = positional_index;

}


std::vector<std::shared_ptr<EntityModel>> World::getEntities() const {
    return _entities;
}


void World::handle_wall_collision(std::shared_ptr<EntityModel> e) {
    Position next_position = e->calculate_next_position();

    std::shared_ptr<EntityModel> supp1 = getPositionalIndex()[next_position.getX()][next_position.getY()];

    //if exist a non-null pointer in the same position
    if (supp1) {
        std::shared_ptr<Wall> wallPtr = std::dynamic_pointer_cast<Wall>(supp1);
        if (wallPtr) {
            //if direction is equals to none Tick doesn't move the obj any longer
            //e->setDirection(Direction::None);
            // make it not available
        }
    }

}

//magari faccio un pacman collision e un ghost collision
void World::pacman_handle_collision(std::shared_ptr<PacMan> pacMan){

    handle_wall_collision(pacMan);

    Position actual_position = pacMan->getPosition();

    std::shared_ptr<EntityModel> supp2 = getPositionalIndex()[actual_position.getX()][actual_position.getY()];

    if (supp2){
        std::shared_ptr<Coin> coinPtr = std::dynamic_pointer_cast<Coin>(supp2);
        if (coinPtr) {
            coinPtr->set_is_eaten();
        } else {
            std::shared_ptr<Fruit> fruitPtr = std::dynamic_pointer_cast<Fruit>(supp2);
            if (fruitPtr){
                coinPtr->set_is_eaten();
            } else {
                std::shared_ptr<Ghost> ghostPtr = std::dynamic_pointer_cast<Ghost>(supp2);
                if (ghostPtr){
                    pacMan->die();
                }
            }
        }
    }
}

void World::update_index() {
    //every time either pacman or ghosts move there is an update of the World

}

Direction World::getDirectionFromPositionDifference(const Position& diff) {
    if (diff.getX() == -1) return Direction::Up;
    if (diff.getX() == 1) return Direction::Down;
    if (diff.getY() == -1) return Direction::Left;
    if (diff.getY() == 1) return Direction::Right;

    return Direction::None;
}

Position World::getPositionDifferenceFromDirection(Direction dir) {
    switch (dir) {
        case Direction::Left:
            return { 0, -1 };
        case Direction::Right:
            return { 0, +1 };
        case Direction::Up:
            return { -1, 0 };
        case Direction::Down:
            return { +1, 0 };
        default:
            return { 0, 0 };
    }
}

std::vector<Direction> World::available_directions(std::shared_ptr<Ghost> g) {
    std::vector<Position> adjancent_positions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    std::vector<Direction> directions;


    // Use iterator to remove directions that satisfy the condition
    adjancent_positions.erase(
            std::remove_if(
                    adjancent_positions.begin(),
                    adjancent_positions.end(),
                    [&](const Position& pos) {
                        Position nextPosition =
                                {roundf(g->getPosition().getX() + pos.getX()),
                                 roundf(g->getPosition().getY() + pos.getY())};
                        std::shared_ptr<EntityModel> neighbor =
                                getPositionalIndex()[nextPosition.getX()][nextPosition.getY()];
                        return (neighbor->getType() == 5);
                    }),
            adjancent_positions.end());

    //here I need to translate the positions into the adjacent_position vector into Direction
    for (const Position& pos : adjancent_positions) {
        Direction dir = getDirectionFromPositionDifference(pos);
        directions.push_back(dir);
    }
    return directions;
}

bool World::is_available_direction(std::shared_ptr<Ghost> g) {
    std::vector<Direction> directions = available_directions(g);
    Direction actual_direction = g->getDirection();

    for (const Direction& dir : directions){
        if (dir == actual_direction){
            return true;
        }
    }
    return false;
}

void World::ghost_out_of_the_spawner(std::shared_ptr<Ghost> g, double deltatime) {
    //auto deltatime = Stopwatch::get_instance().deltatime();

    float x, y;

    while (true) {
        x = g->getPosition().getX();
        y = g->getPosition().getY();

        if (is_in_the_right_position(x,5)) {

            if (is_in_the_right_position(y,8)) {
                g->setDirection(Direction::Right);
            } else if (is_in_the_right_position(y,11)) {
                g->setDirection(Direction::Left);
            } else if ( (is_in_the_right_position(y,9)) ||
                    (is_in_the_right_position(y,10)) ){
                g->setDirection(Direction::Up);
            }

        }

        if (is_in_the_right_position(x,3)) {
            if (is_in_the_right_position(y,9)) {
                g->setDirection(Direction::Left);
            } else if (is_in_the_right_position(y,10)) {
                g->setDirection(Direction::Right);
            } else if ( (is_in_the_right_position(y,6)) ||
            (is_in_the_right_position(y,13)) ) {
                g->setDirection(Direction::Down);
            }
        }

        if (  ((is_in_the_right_position(x,5)) && (is_in_the_right_position(y,6))) ||
            ((is_in_the_right_position(x,5)) && (is_in_the_right_position(y,13)))  ) {
            return;
        }

        g->tick(deltatime);
       // std::this_thread::sleep_for(interval);
        //std::cout <<" ( " <<   g->getPosition().getX() << ", " << g->getPosition().getY() << " ) " << std::endl;

    }
}
/*
void World::ghost_random(std::shared_ptr<Ghost> g) {

    float x,y;
    x = g->getPosition().getX();
    y = g->getPosition().getY();

    std::vector<Direction> directions = available_directions(g);
    auto &random = Random::instance();

    if (directions.size() == 1){
        g->setDirection(directions[0]);
    }

    //check if the ghost is actually on a corner position
    if ( (directions.size() == 2) && (!is_available_direction(g)) &&
    (is_approximated_to_integer(x)) && (is_approximated_to_integer(y)) ){
        Direction new_direction = random.get_random_direction(directions);
        g->setDirection(new_direction);
    }
    //check if the ghost is actually on a intersection position
    if ((directions.size() >= 3) && (is_approximated_to_integer(x)) && (is_approximated_to_integer(y))){
        Direction new_direction = random.get_random_direction(directions);
        g->setDirection(new_direction);
    }
}
*/
float World::manhattan_distance(Position &p1, Position &p2) {
    return (float) ( std::abs(p1.getX() - p2.getX()) + std::abs(p1.getY() - p2.getY()) );
}

void World::ghost_manhattan_distance(std::shared_ptr<Ghost> g) {
    std::vector<Direction> directions = available_directions(g);

    std::unordered_map<Direction, float> distances;

    // Calculate distances for each direction and store in the map
    for (const Direction& dir : directions) {
        Position supp = getPositionDifferenceFromDirection(dir);
        Position next = {(float)g->getPosition().getX() + supp.getX(), (float)g->getPosition().getY() + supp.getY()};

        std::shared_ptr<PacMan> pacmanptr = std::dynamic_pointer_cast<PacMan>(_pacman);
        Position actual_pacman_position = get_pacman_position(pacmanptr);

        float result = manhattan_distance(next, actual_pacman_position);
        distances[dir] = result;
    }

    auto minDistanceIterator = distances.begin();

    //scan the unordered map and find the minimum value
    for (auto it = distances.begin(); it != distances.end(); ++it) {
        if (it->second < minDistanceIterator->second) {
            minDistanceIterator = it;
        }
    }

    //find the direction associated to the minimum value
    Direction min_direction = minDistanceIterator->first;
    if (is_approximated_to_integer(g->getPosition().getX()) &&
    is_approximated_to_integer(g->getPosition().getY()))
    g->setDirection(min_direction);
}

void World::ghost_AI(std::shared_ptr<Ghost> g) {


    std::vector<Direction> directions = available_directions(g);



    if (directions.size() == 1){
        g->setDirection(directions[0]);
    }

    //check if the ghost's actual position is on a corner of the map
    if (is_on_a_corner(directions.size(), g)){
        float x, y;
        x = g->getPosition().getX();
        y = g->getPosition().getY();

        Direction precedent = g->getDirection();
        ghost_decision(g, directions);
        g->setPosition(roundf(g->getPosition().getX()), roundf(g->getPosition().getY()));
        Direction actual_direction = g->getDirection();
        auto supp =  getPositionDifferenceFromDirection(actual_direction);

        if (g->getDirection() == precedent){
            x = g->getPosition().getX();
            y = g->getPosition().getY();
            g->setPosition(x + (supp.getX() * 0.005), y + (supp.getY() * 0.005));
        }
    }

    //check if the ghost's actual position is on an intersection
    if (is_on_an_intersection(directions.size(), g)){

        float x, y;
        x = g->getPosition().getX();
        y = g->getPosition().getY();

        Direction precedent = g->getDirection();
        ghost_decision(g, directions);
        g->setPosition(roundf(g->getPosition().getX()), roundf(g->getPosition().getY()));
        Direction actual_direction = g->getDirection();
        auto supp =  getPositionDifferenceFromDirection(actual_direction);

        if (g->getDirection() == precedent){
            x = g->getPosition().getX();
            y = g->getPosition().getY();
            g->setPosition(x + (supp.getX() * 0.005), y + (supp.getY() * 0.005));
        }

    }

}