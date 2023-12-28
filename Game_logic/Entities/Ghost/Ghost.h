#ifndef PACMANV0_GHOST_H
#define PACMANV0_GHOST_H
#include "../EntityModel.h"
#include "../../Utils/Random.h"

class Ghost : public EntityModel {
public:
    Ghost() = default;  // Default constructor
    int getType() override;

    void print_position() override;

private:
    bool _chasing_mode;
    bool _fear_mode;
    int _type = 3;

};


#endif //PACMANV0_GHOST_H
