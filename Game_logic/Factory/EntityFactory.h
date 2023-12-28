#ifndef PACMANV0_ENTITYFACTORY_H
#define PACMANV0_ENTITYFACTORY_H
#include "../Entities/EntityModel.h"
#include "../Entities/Ghost/Ghost.h"
#include "../Entities/PacMan/PacMan.h"
#include "../Entities/Collectable/Coin.h"
#include "../Entities/Collectable/Fruit.h"
#include "../Entities/Wall/Wall.h"

class EntityFactory {
public:
    virtual std::shared_ptr<EntityModel> createEntity(int x, int y) const = 0;
};

class GhostFactory : public EntityFactory {
public:
    std::shared_ptr<EntityModel> createEntity(int x, int y) const override;
};

class PacManFactory : public EntityFactory{
public:
    std::shared_ptr<EntityModel> createEntity(int x, int y) const override;
};

class WallFactory : public EntityFactory {
public:
    std::shared_ptr<EntityModel> createEntity(int x, int y) const override;
};

class CoinFactory : public EntityFactory{
public:
    std::shared_ptr<EntityModel> createEntity(int x, int y) const override;
};

class FruitFactory : public EntityFactory{
public:
    std::shared_ptr<EntityModel> createEntity(int x, int y) const override;
};





#endif //PACMANV0_ENTITYFACTORY_H
