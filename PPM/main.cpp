#include "ppm_image.h"

#include <iostream>
#include <string_view>
#include <algorithm>

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

    // NegativeInplace(image); 
    VMirrInplace(image);

    if (!img_lib::SavePPM(argv[2], image)) {
        cerr << "Error saving image"sv << endl;
        return 3;
    }

    cout << "Image saved successfully!"sv << endl;
}