#include "Collectable.h"


bool Collectable::get_is_eaten() {
    return _is_eaten;
}

void Collectable::set_is_eaten() {
    _is_eaten = true;
}