#include "bmp_image.h"
#include "pack_defines.h"

#include <array>
#include <fstream>
#include <string_view>

using namespace std;

namespace img_lib {

PACKED_STRUCT_BEGIN BitmapFileHeader {
    // поля заголовка Bitmap File Header
}
PACKED_STRUCT_END

PACKED_STRUCT_BEGIN BitmapInfoHeader {
    // поля заголовка Bitmap Info Header
}
PACKED_STRUCT_END

// функция вычисления отступа по ширине
static int GetBMPStride(int w) {
    return 4 * ((w * 3 + 3) / 4);
}

// напишите эту функцию
bool SaveBMP(const Path& file, const Image& image) {
    return false;
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
