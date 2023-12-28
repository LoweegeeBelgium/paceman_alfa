#include "EntityFactory.h"

std::shared_ptr<EntityModel> GhostFactory::createEntity(int x, int y) const {
    return std::make_shared<Ghost>();
}

std::shared_ptr<EntityModel> PacManFactory::createEntity(int x, int y) const {
    return std::make_shared<PacMan>();
}

std::shared_ptr<EntityModel> FruitFactory::createEntity(int x, int y) const {
    return std::make_shared<Fruit>();
}

std::shared_ptr<EntityModel> CoinFactory::createEntity(int x, int y) const {
    return std::make_shared<Coin>();
}

std::shared_ptr<EntityModel> WallFactory::createEntity(int x, int y) const {
    return std::make_shared<Wall>();
}
