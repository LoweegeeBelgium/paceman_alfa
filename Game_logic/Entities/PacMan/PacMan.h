#ifndef PACMANV0_PACMAN_H
#define PACMANV0_PACMAN_H
#include "../EntityModel.h"

class PacMan : public EntityModel {
public:
    PacMan(float speed);
    PacMan() = default;

    void eat();
    void die();
    int getType() override;
    //void setSpeed(float speed) override;
private:
    int _life;
    int _type = 1;
};


#endif //PACMANV0_PACMAN_H
