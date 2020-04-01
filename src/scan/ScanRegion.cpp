//
// Created by jzb on 2020/4/1.
//

#include "ScanRegion.hpp"
#include "../Util.hpp"

namespace MediPathScanner {
    bool ScanRegion::isFinished() {
        return FINISH == status_ || frameCount_ == totalFrameCount_;
    }

    void ScanRegion::handleScanFrame(const std::shared_ptr<FrameCopy> frame) {}

    void ScanRegion::initSMC() {}

    ScanRegion::~ScanRegion() {}
}
