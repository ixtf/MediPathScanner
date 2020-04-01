//
// Created by jzb on 2020/4/1.
//

#ifndef MEDIPATHSCANNER_SCANREGION_HPP
#define MEDIPATHSCANNER_SCANREGION_HPP

#include <atomic>
#include <opencv2/opencv.hpp>
#include "../dahua/FrameCopy.hpp"

namespace MediPathScanner {
    class ScanRegion {
    public:
        friend class ScanTask;

        enum Status {
            INIT,
            SCANNING,
            FINISH,
            ERR,
        };

        ScanRegion(const int serialNum, const cv::Rect &rect, const std::string dataDir, const int totalFrameCount)
                : serialNum_(serialNum), rect_(rect), dataDir_(dataDir), totalFrameCount_(totalFrameCount) {};

        ~ScanRegion();

    private:
        const int serialNum_;
        const cv::Rect rect_;
        const std::string dataDir_;
        const int totalFrameCount_;

        Status status_ = INIT;
        std::atomic<int> frameCount_;

        void initSMC(void);

        bool isFinished(void);

        void handleScanFrame(const std::shared_ptr<FrameCopy> frame);
    };
}

#endif //MEDIPATHSCANNER_SCANREGION_HPP
