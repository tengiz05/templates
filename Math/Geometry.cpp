constexpr double pi = acos(-1);
constexpr double EPS = 1E-12;

struct Vector {
    i64 x, y;
    Vector(i64 x = 0, i64 y = 0) : x(x), y(y) {}
    i64 operator*(const Vector &b) const {
        return x * b.x + y * b.y;
    }
    i64 operator%(const Vector &b) const {
        return x * b.y - b.x * y;
    }
    Vector operator*(i64 k) const {
        return Vector(x * k, y * k);
    }
    Vector operator-(const Vector &b) const {
        return Vector(x - b.x, y - b.y);
    }
    Vector orthogonal() {
        return Vector(-y, x);
    }
    double length() {
        return sqrt(x * x + y * y);
    }
    double angle(i64 x, i64 y) {
        double ans = atan2(y, x);
        if (ans < 0) {
            ans = 2 * pi + ans;  
        }
        return ans;
    }
    __int128 bigcross(const Vector &b) const {
        return __int128(x) * b.y - __int128(b.x) * y;
    }
    __int128 bigdot(const Vector &b) const {
        return __int128(x) * b.x + __int128(y) * b.y;
    }
};
void read(Vector &a) {
    std::cin >> a.x >> a.y;
}

struct Line {
    Vector n;
    i64 a, b, c;
    Line(i64 a = 0, i64 b = 0, i64 c = 0) : n(a, b), a(a), b(b), c(c) {}
    Line(Vector n, i64 c) : n(n), a(n.x), b(n.y), c(c) {}
    Line(const Vector &p1, const Vector &p2) {
        n = (p1 - p2).orthogonal();
        a = n.x;
        b = n.y;
        c = -a * p1.x - b * p1.y;
    }
    double dist(const Vector &p) {
        return (n * p + c) / sqrt(a * a + b * b);
    }
    bool contains(const Vector &p) {
        return n * p + c == 0;
    }
    bool intersect(const Line &k) {
        i64 d = n % k.n;
        return d != 0;
    }
    std::array<i64, 3> intersection(const Line &k) {
        i64 d = n % k.n;
        assert(d != 0);
        i64 x = (-c) * k.b - b * (-k.c);
        i64 y = a * (-k.c) - (-c) * k.a;
        return {x, y, d};
    }
};
void read(Line &k) {
    int a, b, c;
    std::cin >> a >> b >> c;
    k = Line(a, b, c);
}

struct Segment {
    Vector a, b;
    Line k;
    Segment() {}
    Segment(Vector a, Vector b) : a(a), b(b), k(a, b) {}
    Segment operator*(i64 k) {
        return Segment(a * k, b * k);
    }
    bool contains(const Vector &p) {
        auto ap = p - a;
        auto ab = b - a;
        
        auto bp = p - b;
        auto ba = a - b;
        
        if ((a - p).bigcross(b - p) == 0 && ap.bigdot(ab) >= 0 && bp.bigdot(ba) >= 0) {
            return true;
        }
        return false;
    }
    double dist(const Vector &p) {
        auto ap = p - a;
        auto ab = b - a;
        
        auto bp = p - b;
        auto ba = a - b;
        
        if (ap * ab >= 0 && bp * ba >= 0) {
            return std::abs(k.dist(p));
        } else {
            return std::min(ap.length(), bp.length());
        }
    }
    double dist(Segment &s) {
        if (k.intersect(s.k)) {
            auto [x, y, d] = k.intersection(s.k);
            if ((*this * d).contains(Vector(x, y)) && (s * d).contains(Vector(x, y))) {
                return 0;
            }
        }
        return std::min({dist(s.a), dist(s.b), s.dist(a), s.dist(b)});
    }
};
void read(Segment &a) {
    Vector A, B;
    read(A);
    read(B);
    a = Segment(A, B);
}
struct Ray {
    Vector a, b;
    Line k;
    Ray() {}
    Ray(Vector a, Vector b) : a(a), b(b), k(a, b) {}
    Ray operator*(i64 k) {
        return Ray(a * k, b * k);
    }
    bool contains(const Vector &p) {
        auto ap = p - a;
        auto ab = b - a;
        
        if ((a - p).bigcross(b - p) == 0 && ap.bigdot(ab) >= 0) {
            return true;
        }
        return false;
    }
    double dist(const Vector &p) {
        auto ap = p - a;
        auto ab = b - a;
        
        if (ap * ab >= 0) {
            return std::abs(k.dist(p));
        } else {
            return ap.length();
        }
    }
    double dist(Segment &s) {
        if (k.intersect(s.k)) {
            auto [x, y, d] = k.intersection(s.k);
            if ((*this * d).contains(Vector(x, y)) && (s * d).contains(Vector(x, y))) {
                return 0;
            }
        }
        return std::min({dist(s.a), dist(s.b), s.dist(a)});
    }
    double dist(Ray &s) {
        if (k.intersect(s.k)) {
            auto [x, y, d] = k.intersection(s.k);
            if ((*this * d).contains(Vector(x, y)) && (s * d).contains(Vector(x, y))) {
                return 0;
            }
        }
        return std::min({dist(s.a), s.dist(a)});
    }
};
void read(Ray &a) {
    Vector A, B;
    read(A);
    read(B);
    a = Ray(A, B);
}
