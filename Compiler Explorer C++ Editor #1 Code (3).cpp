#include <iostream>
#include <numeric>
#include <random>

struct coordinates {
    double x;
    double y;
};

coordinates operator+(coordinates const& a, coordinates const& b) {
    return coordinates{a.x + b.x, a.y + b.y};
}

coordinates operator-(coordinates const& a, coordinates const& b) {
    return coordinates{a.x - b.x, a.y - b.y};
}
coordinates operator*(coordinates const& a, double const& b) {
    return coordinates{a.x * b, a.y * b};
}
coordinates operator/(coordinates const& a, double const& b) {
    return coordinates{a.x / b, a.y / b};
}
bool operator!=(coordinates const& a, coordinates const& b) {
    return a.x != b.x && a.y != b.y;
}

struct boid {
    coordinates p;
    coordinates v;
};

class Flock {
    std::vector<boid> flock_;

   public:
    Flock(std::vector<boid> flock) : flock_{flock} {}

    auto center_mass(int const& n_boids) {
        coordinates sum{};
        for (auto it = flock_.begin(); it != flock_.end(); ++it) {
            sum = sum + it->p;
        };
        coordinates cm = sum / (n_boids - 1);
        return cm;
    }

    auto center_mass2(int const& n_boids) {
        auto it_first = flock_.begin();
        auto it_last = flock_.end();

        coordinates i{0., 0.};

        coordinates sum = std::accumulate(it_first, it_last, i,
                                          [&](boid const& b1, boid const& b2) {
                                              auto p1 = b1.p;
                                              auto p2 = b2.p;
                                              coordinates p_sum = p1 + p2;
                                              return p_sum;
                                          });

        coordinates cm = sum / (n_boids - 1);
        return cm;
    }
};

int main() {
    boid b1{3., 6., 0., 0.};
    boid b2{2., 4., 0., 0.};
    boid b3{4., 5., 0., 0.};
    int const n_boids = 3;

    Flock f{{b1, b2, b3}};

    auto c = f.center_mass(n_boids);
    auto d = f.center_mass2(n_boids);
    std::cout << c.x << '\n';
    std::cout << c.y << '\n';
    std::cout << d.x << '\n';
    std::cout << d.y << '\n';
}