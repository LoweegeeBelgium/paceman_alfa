#ifndef PACMANV0_POSITION_H
#define PACMANV0_POSITION_H
#include <iostream>

class Position {
public:
    Position(float x, float y);

    float getX() const;
    float getY() const;

    friend bool operator==(const Position& lhs, const Position& rhs);

    friend Position operator+(const Position& rhs, const Position& lhs);

private:
    float _x;
    float _y;
};

/*
std::ostream& operator<<(std::ostream& os, Position& position) {
    os << "(" << position.getX() << ", " << position.getY() << ")";
    return os;
}
*/

#endif //PACMANV0_POSITION_H
