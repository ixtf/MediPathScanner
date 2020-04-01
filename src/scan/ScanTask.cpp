//
// Created by jzb on 2020/4/1.
//

#include <fstream>
#include <spdlog/spdlog.h>
#include "ScanTask.hpp"
#include "../alg/AlgService.hpp"
#include "../smc/SMCService.hpp"
#include "../Util.hpp"

namespace MediPathScanner {
    ScanTask::~ScanTask() {
        scanFrameSubscription_.unsubscribe();
    }

    bool ScanTask::isFinished() {
        return status_ == FINISHED;
    }

    bool ScanTask::isErr() {
        return status_ == ERR;
    }

    void ScanTask::handleViewFrame(const std::shared_ptr<FrameCopy> frame) {
        const std::string filename = dataDir_ + "/view.jpeg";
        frame->writeToFile(filename);
        AlgService::getInstance().region(filename, rects_);
        YAML::Node taskNode;
        taskNode["id"] = id_;
        for (auto rect:rects_) {
            YAML::Node rectNode;
            rectNode["x"] = rect.x;
            rectNode["y"] = rect.y;
            rectNode["width"] = rect.width;
            rectNode["height"] = rect.height;
            taskNode["rects"].push_back(rectNode);
        }
        std::ofstream osData(dataDir_ + "/view.yml");
        osData << taskNode << std::endl;
        switchScanRectByIndex();
        status_ = SCANNING;
    }

    void ScanTask::switchScanRectByIndex(const int idx) {
        auto scanRegionDataDir = dataDir_ + "/region_" + std::to_string(idx);
        MediPathScanner::Util::mkdir(currentScanRegion->dataDir_);
        auto totalFrameCount = 100;
        currentScanRegion = CurrentScanRegion(new ScanRegion{idx, rects_.at(idx), scanRegionDataDir, totalFrameCount});
        currentScanRegion->initSMC();
    }

    void ScanTask::handleScanFrame(const std::shared_ptr<FrameCopy> frame) {
        currentScanRegion->handleScanFrame(std::move(frame));
        if (currentScanRegion->isFinished()) {
            bool allFinished = currentScanRegion->serialNum_ == scannedRegions_.size();
            if (allFinished) {
                status_ = FINISHED;
                scanFrameSubscription_.unsubscribe();
            } else {
                switchScanRectByIndex(currentScanRegion->serialNum_);
            }
        }
    }

    void ScanTask::handleScanError(const std::exception &e) {
        status_ = ERR;
        scanFrameSubscription_.unsubscribe();
        Log::error(e.what());
    }
}