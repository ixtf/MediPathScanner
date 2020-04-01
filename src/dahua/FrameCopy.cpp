//
// Created by jzb on 2020/4/1.
//

#include "FrameCopy.hpp"
#include "spdlog/spdlog.h"
#include "turbojpeg.h"
#include "jpeglib.h"
#include "../Util.hpp"

namespace MediPathScanner {
    FrameCopy::FrameCopy(CFrame const &frame)
            : blockId_(frame.getBlockId()),
              imageTimeStamp_(frame.getImageTimeStamp()),
              imagePixelFormat_(frame.getImagePixelFormat()),
              imageWidth_(frame.getImageWidth()),
              imageHeight_(frame.getImageHeight()),
              imagePaddingX_(frame.getImagePadddingX()),
              imagePaddingY_(frame.getImagePadddingY()),
              imageSize_(frame.getImageSize()),
              image_(nullptr),
              rgbDataSize_(0),
              rgbData_(nullptr) {
        if (frame.getImagePixelFormat() == gvspPixelMono8) {
            image_ = new(std::nothrow) uint8_t[frame.getImageSize()];
        } else {
            image_ = new(std::nothrow) uint8_t[frame.getImageWidth() * frame.getImageHeight() * 3];
        }
        if (image_) {
            memcpy(image_, frame.getImage(), frame.getImageSize());
        }
    }

    FrameCopy::~FrameCopy() {
        if (image_) {
            delete[] image_;
            image_ = nullptr;
        }
        if (rgbData_) {
            delete[] rgbData_;
            rgbData_ == nullptr;
        }
    }

    void FrameCopy::convertToRGB24() {
        if (rgbData_) {
            return;
        }
        if (image_) {
            rgbData_ = new(std::nothrow) uint8_t[imageWidth_ * imageHeight_ * 3];
            if (rgbData_) {
                IMGCNV_SOpenParam openParam;
                openParam.width = imageWidth_;
                openParam.height = imageHeight_;
                openParam.paddingX = imagePaddingX_;
                openParam.paddingY = imagePaddingY_;
                openParam.dataSize = imageSize_;
                openParam.pixelForamt = imagePixelFormat_;
                IMGCNV_EErr status = IMGCNV_ConvertToRGB24(image_, &openParam, rgbData_, &rgbDataSize_);
                if (status != IMGCNV_EErr::IMGCNV_SUCCESS) {
                    Log::error("IMGCNV_ConvertToRGB24 error {}", status);
//                throw "IMGCNV_ConvertToRGB24 error" + std::to_string(status);
                }
            }
        }
    }

    void FrameCopy::writeToFile(const std::string &filename, const int quality) {
        convertToRGB24();
        jpeg_compress_struct cinfo;
        jpeg_error_mgr jerr;
        cinfo.err = jpeg_std_error(&jerr);
        jpeg_create_compress(&cinfo);

        FILE *outfile = fopen(filename.c_str(), "wb");
        if (outfile == NULL) {
            fprintf(stderr, "can't open %s\n", filename.c_str());
            exit(1);
        }
        jpeg_stdio_dest(&cinfo, outfile);

        cinfo.image_width = imageWidth_;
        cinfo.image_height = imageHeight_;
        cinfo.input_components = 3;
        cinfo.in_color_space = JCS_RGB;

        JSAMPROW row_pointer[1];
        int const row_stride = imageWidth_ * 3;
        jpeg_set_defaults(&cinfo);
        jpeg_set_quality(&cinfo, quality, TRUE);
        jpeg_start_compress(&cinfo, TRUE);
        while (cinfo.next_scanline < cinfo.image_height) {
            row_pointer[0] = &rgbData_[cinfo.next_scanline * row_stride];
            (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
        }

        jpeg_finish_compress(&cinfo);
        fclose(outfile);
        jpeg_destroy_compress(&cinfo);
    }
}