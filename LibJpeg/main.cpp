#include <filesystem>
#include <iostream>
#include <memory>
#include <string_view>

#include "img_lib.h"
#include "jpeg_image.h"
#include "ppm_image.h"

using namespace std;
using namespace std::string_view_literals;

int main(int argc, const char** argv) {
    using namespace img_lib;

    if (argc != 3) {
        cerr << "Usage: "sv << argv[0] << " <in_file> <out_file>"sv << endl;
        return 1;
    }

    img_lib::Path in_path = argv[1];
    img_lib::Path out_path = argv[2];

    Format input_format = GetFormatByExtension(in_path);
    Format output_format = GetFormatByExtension(out_path);

    std::unique_ptr<ImageFormatInterface> input_interface_ptr;
    std::unique_ptr<ImageFormatInterface> output_interface_ptr;

    switch (input_format) {
        case Format::JPEG:
            input_interface_ptr = unique_ptr<ImageFormatInterface>(new JPEGInterface());
            break;
        
        case Format::PPM:
            input_interface_ptr = unique_ptr<ImageFormatInterface>(new PPMInterface());
            break;
        
        default:
            assert(false);
    }

    switch (output_format) {
        case Format::JPEG:
            output_interface_ptr = unique_ptr<ImageFormatInterface>(new JPEGInterface());
            break;
        
        case Format::PPM:
            output_interface_ptr = unique_ptr<ImageFormatInterface>(new PPMInterface());
            break;

        default:
            assert(false);
    }

    img_lib::Image image = input_interface_ptr->LoadImage(in_path);
    if (!image) {
        cerr << "Loading failed"sv << endl;
        return 4;
    }

    if (!output_interface_ptr->SaveImage(out_path, image)) {
        cerr << "Saving failed"sv << endl;
        return 5;
    }

    cout << "Successfully converted"sv << endl;
}
