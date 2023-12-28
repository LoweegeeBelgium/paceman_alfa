#include "PacMan.h"

PacMan::PacMan(float speed) : EntityModel(speed) {};

void PacMan::die() {
    _life--;
    this->setPosition(9,9);//starting position of pacman
}

void PacMan::eat() {

}

int PacMan::getType() {
    return _type;
}

