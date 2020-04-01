//
// Created by jzb on 2020/3/31.
//

#include "DahuaService.hpp"
#include "../scan/ScanService.hpp"

namespace MediPathScanner {
    namespace {
        std::vector<DahuaCamera> kCameras;
    }

    DahuaService &DahuaService::init(const YAML::Node &config) {
        DahuaCamera viewCamera(config["dahua"]["viewCamera"]["ip"].as<std::string>(), ScanService::handleViewFrame);
        DahuaCamera scanCamera(config["dahua"]["scanCamera"]["ip"].as<std::string>(), ScanService::handleScanFrame);
        kCameras.emplace_back(viewCamera);
        kCameras.emplace_back(scanCamera);
        viewCamera.connect();
        scanCamera.connect();
        return *this;
    }
}