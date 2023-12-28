#ifndef PACMANV0_WALL_H
#define PACMANV0_WALL_H
#include "../EntityModel.h"

class Wall : public EntityModel {
public:
    Wall() = default;  // Default constructor

    int getType() override;
private:
    int _type = 5;
};


#endif //PACMANV0_WALL_H
