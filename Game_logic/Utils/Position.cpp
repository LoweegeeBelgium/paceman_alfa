#include "Position.h"
 

Position::Position(float x, float y) : _x{x}, _y{y} {};

float Position::getX() const{
    return _x;
}

float Position::getY() const{
    return _y;
}

bool operator==(const Position& lhs, const Position& rhs) {
    return (lhs._x == rhs._x) && (lhs._y == rhs._y);
}

Position operator+(const Position& lhs, const Position& rhs){
    return Position(lhs.getX() + rhs.getX(), lhs.getY() + rhs.getY());
}