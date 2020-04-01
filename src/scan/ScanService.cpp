//
// Created by jzb on 2020/3/31.
//

#include "ScanService.hpp"
#include "ScanTask.hpp"
#include "../Util.hpp"

namespace {
    using namespace MediPathScanner;
    std::string kDeviceId;
    std::string kDataPath;
    std::unique_ptr<ScanTask> kScanTaskUptr = nullptr;
    rxcpp::subjects::subject<std::shared_ptr<FrameCopy>> scanFrameSubject;
}

namespace MediPathScanner {
    void ScanService::init(const YAML::Node &node) {
        kDeviceId = node["scan"]["deviceId"].as<std::string>();
        kDataPath = node["scan"]["dataPath"].as<std::string>();
    }

    void ScanService::initNewTask() {
        auto timestamp = std::chrono::system_clock::now().time_since_epoch().count();
        auto taskId = kDeviceId + "-" + std::to_string(timestamp);
        auto taskDataDir = kDataPath + "/" + taskId;
        Util::mkdir(taskDataDir);
        kScanTaskUptr = std::unique_ptr<ScanTask>(new ScanTask{taskId, taskDataDir});
        kScanTaskUptr->scanFrameSubscription_ = scanFrameSubject.get_observable()
                .observe_on(rxcpp::observe_on_new_thread())
                .subscribe(
                        [](auto frame) {
                            kScanTaskUptr->handleScanFrame(std::move(frame));
                        },
                        [](auto ePtr) {
                            try {
                                std::rethrow_exception(ePtr);
                            } catch (const std::exception &e) {
                                kScanTaskUptr->handleScanError(e);
                            }
                        }
                );
    }

    void ScanService::handleViewFrame(const std::shared_ptr<FrameCopy> frame) {
        kScanTaskUptr->handleViewFrame(std::move(frame));
    }

    void ScanService::handleScanFrame(const std::shared_ptr<FrameCopy> frame) {
        scanFrameSubject.get_subscriber().on_next(std::move(frame));
    }
}