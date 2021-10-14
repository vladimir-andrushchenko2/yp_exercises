#pragma once
#include "img_lib.h"

namespace img_lib {

bool SavePPM(const Path& file, const Image& image);
Image LoadPPM(const Path& file);


class PPMInterface : public ImageFormatInterface {
   public:
    bool SaveImage(const img_lib::Path& file, const img_lib::Image& image) const override {
        return SavePPM(file, image);
    }

    img_lib::Image LoadImage(const img_lib::Path& file) const override {
        return LoadPPM(file);
    }
};

}  // namespace img_lib
