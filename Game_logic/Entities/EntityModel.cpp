#include "EntityModel.h"
#include "../Observer.h"


EntityModel::EntityModel(float speed) : _speed{speed} {};

void EntityModel::setPosition(float x, float y) {
    _position = {x,y};
}

Position EntityModel::getPosition() {
    return _position;
}

void EntityModel::setDirection(Direction dir){
    _dir = dir;
}

Direction EntityModel::getDirection() {
    return _dir;
}

void EntityModel::setSpeed(float speed) {
    _speed = speed;
}

float EntityModel::getSpeed() {
    return _speed;
}

int EntityModel::getType() {
    return _type;
}


void EntityModel::print_position() {
    std::cout << '(' << _position.getX() << ", " << _position.getY() << ')';
}



void EntityModel::Attach(std::shared_ptr<Observer> observer) {
    _list_observers.push_back(observer);
}

void EntityModel::Detach(std::shared_ptr<Observer> observer) {
    _list_observers.remove(observer);
}

void EntityModel::Notify() {
    std::list<std::shared_ptr<Observer>>::iterator iterator = _list_observers.begin();
    while (iterator != _list_observers.end()){
        (*iterator) -> Update(_message);
        ++iterator;
    }
}


void EntityModel::tick(double deltatime) {
    if(_dir == Direction::None)
        return;

    move(deltatime);
}

void EntityModel::move(double deltatime){
    float pixels_per_second = _speed * deltatime;

    if (_dir == Direction::Left){
        this->setPosition(this->_position.getX(),this->_position.getY() - pixels_per_second);
    } else if (_dir == Direction::Right){
        this->setPosition(this->_position.getX(),this->_position.getY() + pixels_per_second);
    } else if (_dir == Direction::Up){
        this->setPosition(this->_position.getX() - pixels_per_second,this->_position.getY());
    } else if (_dir == Direction::Down){
        this->setPosition(this->_position.getX() + pixels_per_second,this->_position.getY());
    }

    std::cout << _position.getX() << ", " << _position.getY() << std::endl;
}

bool EntityModel::checkCollision(std::shared_ptr<EntityModel> entity) {
    if(this->_position == entity->_position){
        return true;
    }
    return false;
}

//problem is here, sometimes next position is equals to actual position
Position EntityModel::calculate_next_position() {
    if (_dir == Direction::Right){
        Position p(_position.getX(),roundf(_position.getY()) + 1);
        return p;
    }
    if (_dir == Direction::Left){
        Position p(_position.getX(),roundf(_position.getY()) - 1);
        return p;
    }
    if (_dir == Direction::Up){
        Position p(roundf(_position.getX()) - 1,_position.getY());
        return p;
    }
    if (_dir == Direction::Down){
        Position p(roundf(_position.getX()) + 1,_position.getY());
        return p;
    }
}

Direction EntityModel::opposite_dir() {
    if (_dir == Direction::Up)
        return Direction::Down;

    if (_dir == Direction::Down)
        return Direction::Up;

    if (_dir == Direction::Left)
        return Direction::Right;

    if (_dir == Direction::Right)
        return Direction::Left;

    if (_dir == Direction::None)
        return _dir;
}