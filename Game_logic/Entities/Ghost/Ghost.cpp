#include "Ghost.h"

int Ghost::getType() {
    return _type;
}

void Ghost::print_position()  {
    std::cout << _position.getX() << ", " << _position.getY() << std::endl;
}
