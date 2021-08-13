#include <cassert>
#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;

class House {
   public:
    House(int length, int width, int height) : length_(length), width_(width), height_(height) {}

    int GetLength() const { return length_; }

    int GetHeight() const { return height_; }

    int GetWidth() const { return width_; }

   private:
    int length_;
    int width_;
    int height_;
};

class Resources {
   public:
    Resources(int brick_count) : brick_count_(brick_count) {}

    void TakeBricks(int count) {
        if (count > brick_count_ || count < 0) {
            throw std::out_of_range("attempt to take more bricks than available or negative amount");
        }

        brick_count_ -= count;
    }

    int GetBrickCount() const { return brick_count_; }

   private:
    int brick_count_;
};
// При попытке взять отрицательное количество кирпичей либо взять больше кирпичей, чем есть, метод Resources::TakeBricks
// должен выбросить исключение std::out_of_range

struct HouseSpecification {
    int length = 0;
    int width = 0;
    int height = 0;
};
// 8 bricks in height * 4 bricks in width = 1 square meter of wall

class Builder {
   public:
    Builder(Resources& resources) : resources_(resources) {}

    // (width + length) * 2 * 4 * height * 8
    House BuildHouse(const HouseSpecification& spec) {
        static constexpr int kBricksInRowIsMeter = 4;
        static constexpr int kBricksInStackIsMeter = 8;

        int perimeter = (spec.width + spec.length) * 2;

        int bricks_required = perimeter * kBricksInRowIsMeter * spec.height * kBricksInStackIsMeter;

        try {
            resources_.TakeBricks(bricks_required);
        } catch (const std::out_of_range&) {
            throw std::runtime_error("builder couldn't access bricks");
        }

        return {spec.length, spec.width, spec.height};
    }

   private:
    Resources& resources_;
};
// При нехватке кирпичей на постройку дома Строитель должен выбросить исключение std::runtime_error

int main() {
    Resources resources{10000};
    Builder builder1{resources};
    Builder builder2{resources};

    House house1 = builder1.BuildHouse(HouseSpecification{12, 9, 3});
    assert(house1.GetLength() == 12);
    assert(house1.GetWidth() == 9);
    assert(house1.GetHeight() == 3);
    cout << resources.GetBrickCount() << " bricks left"s << endl;

    House house2 = builder2.BuildHouse(HouseSpecification{8, 6, 3});
    assert(house2.GetLength() == 8);
    cout << resources.GetBrickCount() << " bricks left"s << endl;

    House banya = builder1.BuildHouse(HouseSpecification{4, 3, 2});
    assert(banya.GetHeight() == 2);
    cout << resources.GetBrickCount() << " bricks left"s << endl;
}
