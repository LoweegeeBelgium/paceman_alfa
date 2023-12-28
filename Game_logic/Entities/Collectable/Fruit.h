#ifndef PACMANV0_FRUIT_H
#define PACMANV0_FRUIT_H
#include "Collectable.h"

class Fruit : public Collectable{
public:
    Fruit() = default;  // Default constructor

    int getType() override;
private:
    int _type = 4;
};


#endif //PACMANV0_FRUIT_H
