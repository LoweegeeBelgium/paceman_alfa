#include "Game_logic/World.h"
#include "iostream"
#include "Game_logic/Utils/json.hpp"
#include <fstream>
#include "Game_logic/Entities/Ghost/Ghost.h"
#include <chrono>
#include <thread>
#include "Game_logic/Utils/Random.h"
#include "Game_logic/Utils/Stopwatch.h"

int main() {


    const std::chrono::seconds interval(1);


    std::ifstream file("../Game_logic/Utils/Map.json");
    if (!file.is_open()) {
        std::cerr << "Error opening file 'Map.json'" << std::endl;
        return 1;
    }

    json j;
    file >> j;
    std::string string_map = j.dump();
    World w(string_map);

    std::vector<std::shared_ptr<EntityModel>> entities = w.getEntities();

    const auto& positionalIndexMatrix = w.getPositionalIndex();


    //print the object based on their position
    for (const auto& row : positionalIndexMatrix) {
        for (const auto& element : row) {
            if (element) {
                std::cout << element->getType();
            } else {
                std::cout << "0 "; // Placeholder for an empty position
            }
        }
        std::cout << std::endl;
    }


    std::cout << std::endl;


    auto supp = w.getPositionalIndex()[1][1];
    std::cout << supp->getType() << std::endl;

    //std::cout<<"( "<<supp->getPosition().getX()<<", "<<supp->getPosition().getY()<<" )"<<std::endl;

    //supp->print_position();

    GhostFactory ghostFactory;
    std::shared_ptr<EntityModel> g = w.get_ghosts()[0];

    std::shared_ptr<Ghost> GhostPtr = std::dynamic_pointer_cast<Ghost>(g);
    g->setDirection(Direction::Right);
    //g->setPosition(3,18);


    //error because I'm considering a new ghost that has not been initialized, i need to retrive a relal ghost from the map
/*
    while ( ((GhostPtr->getPosition().getX() != 5) || (GhostPtr->getPosition().getY() != 6)) &&
        ((GhostPtr->getPosition().getX() != 5) || (GhostPtr->getPosition().getY() != 13)) ){
        w.ghost_out_of_the_spawner(GhostPtr);
        GhostPtr->tick();

        GhostPtr->print_position();
        std::this_thread::sleep_for(interval);
    }
*/

    GhostPtr->setSpeed(18);

    auto deltatime = Stopwatch::get_instance().deltatime();

    w.ghost_out_of_the_spawner(GhostPtr, deltatime);
    std::cout << "----------------------------------" << std::endl;
    //GhostPtr->setDirection(Direction::Right);
    //GhostPtr->setPosition(5,1);
    GhostPtr->setSpeed(400);

    //GhostPtr->setSpeed(300);
    while (true){
        //!!!!!!!!!!!!!!!!!!!!!!!! IL DELTA TIME QUI è SBALLATO


       // w.handle_wall_collision(GhostPtr);
        //DON'T USE handle_collision here
        w.ghost_AI(GhostPtr);
        GhostPtr->tick(deltatime);
        //w.ghost_AI(GhostPtr);
        //why it doesn't print the position ?
       // GhostPtr->print_position();
        //std::this_thread::sleep_for(interval);
    }


float n = 5.8;
std::cout<< (int) n << std::endl;

    /*
    Random& randoma = Random::instance();

    std::vector<Direction> pippi;
    pippi.push_back(Direction::Up);
    pippi.push_back(Direction::Down);
    pippi.push_back(Direction::Right);

    Direction cazzo = randoma.get_random_direction(pippi);
    //w.ghost_AI(g);

    std::shared_ptr<EntityModel> gargarozzo = ghostFactory.createEntity(3,4);
    std::shared_ptr<Ghost> ghostarozzo = std::dynamic_pointer_cast<Ghost>(gargarozzo);
    ghostarozzo->setDirection(cazzo);


    std::cout << ghostarozzo->getDirection();
    */

/*
    entities[0]->print_position();
    entities[0]->setDirection(Direction::Up);
    entities[0]->move();
    entities[0]->print_position();
*/

/*
    entities[0]->print_position();
    entities[1]->print_position();
    entities[2]->print_position();
    entities[12]->print_position();
    entities[19]->print_position();
    entities[20]->print_position();
    entities[219]->print_position();
*/


}