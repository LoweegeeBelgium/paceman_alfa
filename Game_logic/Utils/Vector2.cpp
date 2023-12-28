
struct Vector2{
    float _x,_y;

    Vector2(float x, float y):_x{x}, _y{y} {};

    Vector2 operator+(const Vector2& other) const {
        return {this->_x + other._x, this->_y + other._y};
    }
    
};