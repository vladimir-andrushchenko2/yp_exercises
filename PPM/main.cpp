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

int GetBrightness(const img_lib::Color* color) {
    int output = 0;

    output += static_cast<int>(color->r);
    output += static_cast<int>(color->g);
    output += static_cast<int>(color->b);
 
    return output;
}

std::vector<int> GetBrightness(const img_lib::Image& image) {
    using namespace img_lib;

    std::vector<int> brightness(image.GetWidth(), image.GetHeight());

    for (int y = 0; y < image.GetHeight(); ++y) {
        const Color* line_begin = image.GetLine(y);

        for (int x = 0; x < image.GetWidth(); ++x) {
            brightness[y * image.GetWidth() + x] = GetBrightness(line_begin + x);
        }
    }

    return brightness;
}

struct BrightnessGrid {
    BrightnessGrid(const img_lib::Image& image): h(image.GetHeight()), w(image.GetWidth()) {
        brightness = GetBrightness(image);
    }

    std::vector<int> brightness;
    int h, w;

    int At(int x, int y) {
        if (x < 0 || x > w || y < 0 || y > h) {
            return 0;
        }
        
        return brightness[y * w + x];
    }
};

img_lib::Color GetSobelAsColor(const std::byte val) {
    return {val, val, val, static_cast<std::byte>(255)};
}

void AddBlackFrame(img_lib::Image& image) {
    using namespace img_lib;

    Color* begin_line = image.GetLine(0);
    Color* end_line = begin_line + image.GetWidth();

    std::fill(begin_line, end_line, Color::Black());

    for (int y = 1; y < image.GetHeight(); ++y) {
        begin_line = image.GetLine(y);
        end_line = begin_line + image.GetWidth();

        *begin_line = Color::Black();
        *(end_line - 1) = Color::Black();
    }

    begin_line = image.GetLine(image.GetHeight() - 1);
    end_line = begin_line + image.GetWidth();

    std::fill(begin_line, end_line, Color::Black());
}

// реализуйте оператор Собеля
img_lib::Image Sobel(const img_lib::Image& image) {
    using namespace img_lib;

    Image output(image.GetWidth(), image.GetHeight(), Color::Black());

    BrightnessGrid brightness_grid(image);

    int gx, gy;

    for (int y = 0; y < image.GetHeight(); ++y) {
        Color* line_begin = output.GetLine(y);

        for (int x = 0; x < image.GetWidth(); ++x) {
            int tl = brightness_grid.At(x - 1, y - 1);
            int tc = brightness_grid.At(x - 0, y - 1);
            int tr = brightness_grid.At(x + 1, y - 1);

            int cl = brightness_grid.At(x - 1, y);
            int cr = brightness_grid.At(x + 1, y);

            int bl = brightness_grid.At(x - 1, y + 1);
            int bc = brightness_grid.At(x - 0, y + 1);
            int br = brightness_grid.At(x + 1, y + 1);

            gx = -tl -2 * tc - tr + bl + 2 * bc + br;

            gy = -tl -2 * cl - bl + tr + 2 * cr + br;

            *(line_begin + x) = GetSobelAsColor(static_cast<std::byte>(std::clamp<double>(std::sqrt(gx*gx + gy*gy), 0., 255.)));
        }
    } 

    AddBlackFrame(output);

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

    // NegativeInplace(image); 
    // VMirrInplace(image);
    image = Sobel(image);

    if (!img_lib::SavePPM(argv[2], image)) {
        cerr << "Error saving image"sv << endl;
        return 3;
    }

    cout << "Image saved successfully!"sv << endl;
}
