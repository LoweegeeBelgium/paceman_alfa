#ifndef PACMANV0_COLLECTABLE_H
#define PACMANV0_COLLECTABLE_H
#include "../EntityModel.h"

class Collectable : public EntityModel{
public :
    Collectable() = default;
    void set_is_eaten();
    bool get_is_eaten();
private:
    bool _is_eaten;
};


#endif //PACMANV0_COLLECTABLE_H
