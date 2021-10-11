#include "ppm_image.h"

#include <iostream>
#include <string_view>
#include <algorithm>
#include <cmath>

using namespace std;

byte Negative(byte c) {
    return static_cast<byte>(255 - to_integer<int>(c));
}

void NegativeInplace(img_lib::Image& image) {
    using namespace img_lib;

    for (int y = 0; y < image.GetHeight(); ++y) {
        Color* begin_line = image.GetLine(y);
        const Color * end_line = begin_line + image.GetWidth();

        for (Color* pixel = begin_line; pixel != end_line; ++pixel) {
            pixel->r = Negative(pixel->r);
            pixel->g = Negative(pixel->g);
            pixel->b = Negative(pixel->b);
        }
    }
}

// реализуйте горизонтальное отражение
void HMirrInplace(img_lib::Image& image) {
    using namespace img_lib;

    for (int y = 0; y < image.GetHeight(); ++y) {
        Color* begin_line = image.GetLine(y);
        Color* end_line = begin_line + image.GetWidth();

        std::reverse(begin_line, end_line);
    }
}

int Sum(img_lib::Color c) {
    return to_integer<int>(c.r) + to_integer<int>(c.g) + to_integer<int>(c.b);
}

img_lib::Color GetSobelAsColor(const std::byte val) {
    return {val, val, val, static_cast<std::byte>(255)};
}

// реализуйте оператор Собеля
img_lib::Image Sobel(const img_lib::Image& image) {
    using namespace img_lib;

    Image output(image.GetWidth(), image.GetHeight(), Color::Black());

    int gx, gy;

    for (int y = 1; y < image.GetHeight() - 1; ++y) {
        Color* line_begin = output.GetLine(y);

        for (int x = 1; x < image.GetWidth() - 1; ++x) {
            int tl = Sum(image.GetPixel(x - 1, y - 1));
            int tc = Sum(image.GetPixel(x - 0, y - 1));
            int tr = Sum(image.GetPixel(x + 1, y - 1));

            int cl = Sum(image.GetPixel(x - 1, y));
            int cr = Sum(image.GetPixel(x + 1, y));

            int bl = Sum(image.GetPixel(x - 1, y + 1));
            int bc = Sum(image.GetPixel(x - 0, y + 1));
            int br = Sum(image.GetPixel(x + 1, y + 1));

            gx = -tl -2 * tc - tr + bl + 2 * bc + br;

            gy = -tl -2 * cl - bl + tr + 2 * cr + br;

            *(line_begin + x) = GetSobelAsColor(static_cast<std::byte>(std::clamp<double>(std::sqrt(gx*gx + gy*gy), 0., 255.)));
        }
    } 

    return output;
}

// реализуйте вертикальное отражение
void VMirrInplace(img_lib::Image& image) {
    using namespace img_lib;

    int bottom = image.GetHeight() - 1;

    for (int top = 0; top < bottom; ++top, --bottom) {
        Color* begin_line_top = image.GetLine(top);
        Color* end_line_top = begin_line_top + image.GetWidth();

        Color* begin_line_bottom = image.GetLine(bottom);

        std::swap_ranges(begin_line_top, end_line_top, begin_line_bottom);
    }
}

int main(int argc, const char** argv) {
    if (argc != 3) {
        cerr << "Usage: "sv << argv[0] << " <input image> <output image>"sv << endl;
        return 1;
    }

    auto image = img_lib::LoadPPM(argv[1]);
    if (!image) {
        cerr << "Error loading image"sv << endl;
        return 2;
    }

    image = Sobel(image);

    if (!img_lib::SavePPM(argv[2], image)) {
        cerr << "Error saving image"sv << endl;
        return 3;
    }

    cout << "Image saved successfully!"sv << endl;
}

/*
struct BrightnessCalculator {
    BrightnessCalculator(const img_lib::Image& image) : image(image) {}

    int At(int x, int y) const {
        if (x < 0 || x > image.GetWidth() || y < 0 || y > image.GetHeight()) {
            return 0;
        }
        
        return Sum(image.GetPixel(x, y));
    }

    const img_lib::Image& image;
};
*/