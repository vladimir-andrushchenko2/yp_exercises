#define _USE_MATH_DEFINES
#include <cmath>

#include "svg.h"  // Объявления классов библиотеки должны быть расположены в файле svg.h

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

        container.Add(polyline);
    }

   private:
    svg::Point center_;
    double outer_rad_;
    double inner_rad_;
    int num_rays_;
};

class Snowman { /* Реализуйте самостоятельно */
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

int main() {
    using namespace svg;
    using namespace shapes;
    using namespace std;

    vector<unique_ptr<svg::Drawable>> picture;

    picture.emplace_back(make_unique<Triangle>(Point{100, 20}, Point{120, 50}, Point{80, 40}));
    // 5-лучевая звезда с центром {50, 20}, длиной лучей 10 и внутренним радиусом 4
    picture.emplace_back(make_unique<Star>(Point{50.0, 20.0}, 10.0, 4.0, 5));
    // Снеговик с "головой" радиусом 10, имеющей центр в точке {30, 20}
    // picture.emplace_back(make_unique<Snowman>(Point{30, 20}, 10.0));

    svg::Document doc;
    // Так как документ реализует интерфейс ObjectContainer,
    // его можно передать в DrawPicture в качестве цели для рисования
    DrawPicture(picture, doc);

    // Выводим полученный документ в stdout
    doc.Render(cout);
}