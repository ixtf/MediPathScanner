//
// Created by jzb on 2020/4/1.
//

#ifndef MEDIPATHSCANNER_SCANTASK_HPP
#define MEDIPATHSCANNER_SCANTASK_HPP


#include <rxcpp/rx.hpp>
#include <vector>
#include "ScanRegion.hpp"
#include "../dahua/FrameCopy.hpp"

namespace MediPathScanner {
    class ScanTask {
    public:
        friend class ScanService;

        enum Status {
            INIT,
            SCANNING,
            FINISHED,
            ERR,
        };

        ScanTask(const std::string id, const std::string dataDir) : id_(id), dataDir_(dataDir) {};

        ~ScanTask();

    private:
        typedef std::unique_ptr<ScanRegion> CurrentScanRegion;
        const std::string id_;
        const std::string dataDir_;
        Status status_ = INIT;
        std::vector<cv::Rect> rects_;
        rxcpp::subscription scanFrameSubscription_;
        CurrentScanRegion currentScanRegion;
        std::vector<std::shared_ptr<ScanRegion>> scannedRegions_;

        bool isErr(void);

        bool isFinished(void);

        void switchScanRectByIndex(const int idx = 0);

        void handleViewFrame(const std::shared_ptr<FrameCopy> frame);

        void handleScanFrame(const std::shared_ptr<FrameCopy> frame);

        void handleScanError(const std::exception &e);
    };
}

#endif //MEDIPATHSCANNER_SCANTASK_HPP
