#ifndef PACMANV0_COIN_H
#define PACMANV0_COIN_H
#include "Collectable.h"

class Coin : public Collectable {
public:
    Coin() = default;  // Default constructor

    int getType() override;
private:
    int _type = 2;
};


#endif //PACMANV0_COIN_H
