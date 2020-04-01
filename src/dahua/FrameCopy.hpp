//
// Created by jzb on 2020/4/1.
//

#ifndef MEDIPATHSCANNER_FRAMECOPY_HPP
#define MEDIPATHSCANNER_FRAMECOPY_HPP

#include "GenICam/System.h"
#include "GenICam/Camera.h"
#include "GenICam/GigE/GigECamera.h"
#include "GenICam/GigE/GigEInterface.h"
#include "Infra/PrintLog.h"
#include "Media/ImageConvert.h"
#include "Memory/SharedPtr.h"

namespace MediPathScanner {
    using namespace Dahua::GenICam;

    class FrameCopy {
    private:
        uint8_t *image_;
        int rgbDataSize_;
        uint8_t *rgbData_;
    public:
        const uint64_t blockId_;
        const uint64_t imageTimeStamp_;
        const EPixelType imagePixelFormat_;
        const int imageWidth_;
        const int imageHeight_;
        const int imagePaddingX_;
        const int imagePaddingY_;
        const int imageSize_;

        FrameCopy(CFrame const &frame);

        ~FrameCopy();

        void convertToRGB24();

        void writeToFile(const std::string &filename, int const quality = 100);

    private:
        FrameCopy(const FrameCopy &) = delete;

        FrameCopy &operator=(const FrameCopy &) = delete;

        FrameCopy &operator=(const FrameCopy &&) = delete;
    };
}

#endif //MEDIPATHSCANNER_FRAMECOPY_HPP
