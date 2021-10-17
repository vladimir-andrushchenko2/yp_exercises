#include "bmp_image.h"

#include <array>
#include <fstream>
#include <string_view>
#include <iostream>

#include "pack_defines.h"

using namespace std;

namespace img_lib {

// функция вычисления отступа по ширине
static int GetBMPStride(int w) { return 4 * ((w * 3 + 3) / 4); }

PACKED_STRUCT_BEGIN BitmapFileHeader {
    BitmapFileHeader(int width, int height) {
        total_size_of_headers_and_data = GetBMPStride(width) * height;
    }

    char B = 'B';
    char M = 'M';
    uint32_t total_size_of_headers_and_data{};
    uint32_t space_filled_with_zeroes = 0;
    // size of both headers is 54 bytes
    uint32_t heades_size = 54;
}
PACKED_STRUCT_END

PACKED_STRUCT_BEGIN BitmapInfoHeader {
    BitmapInfoHeader(int width, int height) : width(width), height(height) {
        total_bytes = GetBMPStride(width) * height;
    }

    uint32_t bitmat_info_header_size = 40;
    int32_t width{};
    int32_t height{};
    uint16_t n_dimentions = 1;
    uint16_t bit_per_pixel = 24;
    uint32_t type_of_compression = 0;
    uint32_t total_bytes{};
    int32_t horizontal_resolution = 11811;
    int32_t vertical_resolution = 11811;
    int32_t colors_used = 0;
    int32_t meaningful_colors = 0x1000000;
}
PACKED_STRUCT_END

// напишите эту функцию
bool SaveBMP(const Path& file, const Image& image) {
    BitmapFileHeader file_header(image.GetWidth(), image.GetHeight());
    BitmapInfoHeader info_header(image.GetWidth(), image.GetHeight());

    assert(sizeof(file_header) == 14);
    // std::cout << sizeof(info_header) << std::endl;
    assert(sizeof(info_header) == 40);

    ofstream out(file, ios::binary);

    out.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
    out.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));

    const int stride = GetBMPStride(image.GetWidth());

    std::vector<char> buff(stride);

    for (int y = image.GetHeight() - 1; y >= 0; --y) {
        const Color* line = image.GetLine(y);

        for (int x = 0; x < image.GetWidth(); ++x) {
            buff[x * 3 + 2] = static_cast<char>(line[x].b);
            buff[x * 3 + 1] = static_cast<char>(line[x].g);
            buff[x * 3 + 0] = static_cast<char>(line[x].r);
        }

        out.write(reinterpret_cast<const char*>(buff.data()), buff.size());
    }

    return out.good();
}

// напишите эту функцию
Image LoadBMP(const Path& file) {
    ifstream ifs(file, ios::binary);

    // ignore first 18 bytes
    ifs.ignore(18);

    int width = -1;
    int height = -1;

    ifs.read(reinterpret_cast<char*>(&width), sizeof(width));
    ifs.read(reinterpret_cast<char*>(&height), sizeof(height));

    ifs.ignore(28);

    int stride = GetBMPStride(width);
    Image image(stride / 3, height, Color::Black());

    std::vector<char> buff(width * 3);

    for (int y = image.GetHeight() - 1; y >= 0; --y) {
        Color* line = image.GetLine(y);

        ifs.read(buff.data(), stride);

        for (int x = 0; x < width; ++x) {
            line[x].b = static_cast<byte>(buff[x * 3 + 0]);
            line[x].g = static_cast<byte>(buff[x * 3 + 1]);
            line[x].r = static_cast<byte>(buff[x * 3 + 2]);
        }
    }

    return image;
}

}  // namespace img_lib
