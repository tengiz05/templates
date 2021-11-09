struct Vector {
    int x, y;
    Vector(int x = 0, int y = 0) : x(x), y(y) {}
    Vector(const Vector &a, const Vector &b) : x(b.x - a.x), y(b.y - a.y) {}
    int operator*(const Vector &b) const {
        return x * b.y - b.x * y;
    }
};
