#include "svg.h"

#include <sstream>

namespace svg {

using namespace std::literals;

void Object::Render(const RenderContext& context) const {
    context.RenderIndent();

    // Делегируем вывод тега своим подклассам
    RenderObject(context);

    context.out << std::endl;
}

// ---------- Circle ------------------

Circle& Circle::SetCenter(Point center) {
    center_ = center;
    return *this;
}

Circle& Circle::SetRadius(double radius) {
    radius_ = radius;
    return *this;
}

void Circle::RenderObject(const RenderContext& context) const {
    auto& out = context.out;
    out << "<circle cx=\""sv << center_.x << "\" cy=\""sv << center_.y << "\" "sv;
    out << "r=\""sv << radius_ << "\" "sv;
    out << "/>"sv;
}

// ---------- Polyline ------------------

Polyline& Polyline::AddPoint(Point point) {
    points_.push_back(point);
    return *this;
}

void Polyline::RenderObject(const RenderContext& context) const {
    auto& out = context.out;
    out << "<polyline points=\""sv;
    for (auto it = points_.begin(); it != points_.end(); ++it) {
        out << it->x << ","sv << it->y;
        if (it + 1 != points_.end()) {
            out << " "sv;
        }
    }
    out << "\""sv;
    out << "/>"sv;
}

// ---------- Text ------------------
void PrintData(std::ostream& out, const std::string& data) {
    for (char c : data) {
        switch (c) {
            case '\"':
                out << "&quot;"sv;
                break;
            case '\'':
                out << "&apos;"sv;
                break;
            case '<':
                out << "&lt;"sv;
                break;
            case '>':
                out << "&gt;"sv;
                break;
            case '&':
                out << "&amp;"sv;
                break;
            default:
                out << c;
                break;
        }
    }
}

Text& Text::SetPosition(Point pos) {
    position_ = pos;
    return *this;
}

Text& Text::SetOffset(Point pos) {
    offset_ = pos;
    return *this;
}

Text& Text::SetFontSize(uint32_t size) {
    size_ = size;
    return *this;
}

Text& Text::SetFontFamily(std::string font_family) {
    font_family_ = font_family;
    return *this;
}

Text& Text::SetFontWeight(std::string font_weight) {
    font_weight_ = font_weight;
    return *this;
}

Text& Text::SetData(std::string data) {
    data_ = data;
    return *this;
}

template <typename Attr, typename Val>
std::string AttributeValue(Attr attribute, Val value) {
    std::stringstream output;
    output << attribute << "=\""sv << value << "\""sv;

    return output.str();
}

void Text::RenderObject(const RenderContext& context) const {
    auto& out = context.out;
    // <text x="35" y="20" dx="0" dy="6" font-size="12" font-family="Verdana" font-weight="bold">Hello C++</text
    out << "<text "sv;
    out << AttributeValue("x"sv, position_.x) << " "sv << AttributeValue("y"sv, position_.y) << " "sv;
    out << AttributeValue("dx"sv, offset_.x) << " "sv << AttributeValue("dy"sv, offset_.y) << " "sv;
    out << AttributeValue("font-size"sv, size_);

    if (!font_family_.empty()) {
        out << " "sv;
        out << AttributeValue("font-family"sv, font_family_);
    }

    if (!font_weight_.empty()) {
        out << " "sv;
        out << AttributeValue("font-weight"sv, font_weight_);
    }

    out << ">"sv;
    PrintData(out, data_);
    out << "<"sv;
    out << "/text>"sv;
}

// ---------- Document ------------------

void Document::AddPtr(std::unique_ptr<Object>&& obj) { objects_.push_back(std::move(obj)); }

void Document::Render(std::ostream& out) const {
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"sv << std::endl;
    out << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"sv << std::endl;

    for (const auto& object : objects_) {
        RenderContext ctx(out, 2, 2);
        object->Render(ctx);
    }

    out << "</svg>"sv;
}

}  // namespace svg
