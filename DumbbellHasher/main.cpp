#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct Circle {
    double x;
    double y;
    double r;
};

struct CircleHasher {
    size_t operator() (const Circle& circle) const {
        size_t h_x = d_hasher_(circle.x);
        size_t h_y = d_hasher_(circle.y);
        size_t h_r = d_hasher_(circle.r);

        return h_x + h_y * 37 + h_r * (37 * 37);
    }

private:
    std::hash<double> d_hasher_;
};

struct Dumbbell {
    Circle circle1;
    Circle circle2;
    string text;
};

struct DumbbellHash {
    size_t operator() (const Dumbbell& dumbbell) {
        return c_hasher_(dumbbell.circle1) * (37 * 37 * 37) + c_hasher_(dumbbell.circle2) * (37 * 37) + s_hasher_(dumbbell.text);
    }

private:
    std::hash<std::string> s_hasher_;
    CircleHasher c_hasher_;
};

int main() {
    DumbbellHash hash;
    Dumbbell dumbbell{{10, 11.5, 2.3}, {3.14, 15, -8}, "abc"s};
    cout << "Dumbbell hash "s << hash(dumbbell);
}
