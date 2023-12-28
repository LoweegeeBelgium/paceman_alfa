#ifndef PACMANV0_ENTITYMODEL_H
#define PACMANV0_ENTITYMODEL_H
#include "Subject.h"
#include <iostream>
#include <list>
#include "../Utils/Position.h"

enum class Direction{ None, Up, Down, Left, Right };


class EntityModel : public Subject {
public:
    EntityModel(float speed);
    EntityModel() = default;


    void Attach(std::shared_ptr<Observer> observer) override;
    void Detach(std::shared_ptr<Observer> observer) override;
    void Notify() override;

    void setPosition(float x, float y);
    Position getPosition();
    void setDirection(Direction dir);
    Direction getDirection();
    float getSpeed();
    void setSpeed(float speed);
    virtual int getType();

    virtual void print_position();

    //maybe you need to override move both for pacman and ghosts
    void move(double deltatime);
    void tick(double deltatime);
    bool checkCollision(std::shared_ptr<EntityModel> entity);

    Position calculate_next_position();

    //idk if this one is necessary
    void reset();

    Direction opposite_dir();


private:
    std::list<std::shared_ptr<Observer>> _list_observers;
    std::string _message;

    Direction _dir;
    int _type;
    float _speed = 0;

protected:
    Position _position = Position(0,0); // Provide a default constructor for _position



};


#endif //PACMANV0_ENTITYMODEL_H
