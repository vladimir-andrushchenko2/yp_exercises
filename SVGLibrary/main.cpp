#define _USE_MATH_DEFINES
#include <cmath>
#include <string>

#include "svg.h"  // Объявления классов библиотеки должны быть расположены в файле svg.h

using namespace std::string_literals;

namespace shapes {

class Triangle : public svg::Drawable {
   public:
    Triangle(svg::Point p1, svg::Point p2, svg::Point p3) : p1_(p1), p2_(p2), p3_(p3) {}

    // Реализует метод Draw интерфейса svg::Drawable
    void Draw(svg::ObjectContainer& container) const override {
        container.Add(svg::Polyline().AddPoint(p1_).AddPoint(p2_).AddPoint(p3_).AddPoint(p1_));
    }

   private:
    svg::Point p1_, p2_, p3_;
};

class Star : public svg::Drawable {
   public:
    Star(svg::Point center, double outer_rad, double inner_rad, int num_rays)
        : center_(center), outer_rad_(outer_rad), inner_rad_(inner_rad), num_rays_(num_rays) {}

    void Draw(svg::ObjectContainer& container) const override {
        using namespace svg;
        Polyline polyline;

        for (int i = 0; i <= num_rays_; ++i) {
            double angle = 2 * M_PI * (i % num_rays_) / num_rays_;
            polyline.AddPoint({center_.x + outer_rad_ * sin(angle), center_.y - outer_rad_ * cos(angle)});
            if (i == num_rays_) {
                break;
            }
            angle += M_PI / num_rays_;
            polyline.AddPoint({center_.x + inner_rad_ * sin(angle), center_.y - inner_rad_ * cos(angle)});
        }

        container.Add(polyline.SetFillColor("red"s).SetStrokeColor("black"s));
    }

   private:
    svg::Point center_;
    double outer_rad_;
    double inner_rad_;
    int num_rays_;
};

class Snowman : public svg::Drawable {
   public:
    Snowman(svg::Point center, double rad) : center_(center), rad_(rad) {}

    void Draw(svg::ObjectContainer& container) const override {
        container.Add(svg::Circle(svg::Point{center_.x, center_.y + 5.0 * rad_}, rad_ * 2)
                          .SetFillColor("rgb(240,240,240)"s)
                          .SetStrokeColor("black"s));
        container.Add(svg::Circle(svg::Point{center_.x, center_.y + 2.0 * rad_}, rad_ * 1.5)
                          .SetFillColor("rgb(240,240,240)"s)
                          .SetStrokeColor("black"s));
        container.Add(svg::Circle(center_, rad_).SetFillColor("rgb(240,240,240)"s).SetStrokeColor("black"s));
    }

   private:
    svg::Point center_;
    double rad_;
};

}  // namespace shapes

template <typename DrawableIterator>
void DrawPicture(DrawableIterator begin, DrawableIterator end, svg::ObjectContainer& target) {
    for (auto it = begin; it != end; ++it) {
        (*it)->Draw(target);
    }
}

template <typename Container>
void DrawPicture(const Container& container, svg::ObjectContainer& target) {
    using namespace std;
    DrawPicture(begin(container), end(container), target);
}

// Выполняет линейную интерполяцию значения от from до to в зависимости от параметра t
uint8_t Lerp(uint8_t from, uint8_t to, double t) {
    return static_cast<uint8_t>(std::round((to - from) * t + from));
}

int main() {
    using namespace svg;
    using namespace std;

    const uint8_t start_r = 0;
    const uint8_t end_r = 20;
    const uint8_t start_g = 255;
    const uint8_t end_g = 20;
    const uint8_t start_b = 30;
    const uint8_t end_b = 150;

    const int num_circles = 10;
    Document doc;
    for (int i = 0; i < num_circles; ++i) {
        const double t = double(i) / (num_circles - 1);

        const string r = to_string(Lerp(start_r, end_r, t));
        const string g = to_string(Lerp(start_g, end_g, t));
        const string b = to_string(Lerp(start_b, end_b, t));

        string fill_color = "rgb("s + r + ","s + g + ","s + b + ")"s;
        doc.Add(Circle()
                    .SetFillColor(fill_color)
                    .SetStrokeColor("black"s)
                    .SetCenter({i * 20.0 + 40, 40.0})
                    .SetRadius(15));
    }
    doc.Render(cout);
}