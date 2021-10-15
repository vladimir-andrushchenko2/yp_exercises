#pragma once
#include "img_lib.h"

namespace img_lib {

bool SavePPM(const Path& file, const Image& image);
Image LoadPPM(const Path& file);

}  // namespace img_lib
