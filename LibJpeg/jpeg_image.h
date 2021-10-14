#pragma once
#include "img_lib.h"

#include <filesystem>

namespace img_lib {

bool SaveJPEG(const Path& file, const Image& image);
Image LoadJPEG(const Path& file);

class JPEGInterface : public ImageFormatInterface {
   public:
    bool SaveImage(const img_lib::Path& file, const img_lib::Image& image) const override {
        return SaveJPEG(file, image);
    }

    img_lib::Image LoadImage(const img_lib::Path& file) const override {
        return LoadJPEG(file);
    }
};

} // of namespace img_lib