//
// Created by jzb on 2020/3/31.
//

#ifndef MEDIPATHSCANNER_SCANSERVICE_HPP
#define MEDIPATHSCANNER_SCANSERVICE_HPP

#include <yaml-cpp/yaml.h>
#include "../dahua/FrameCopy.hpp"

namespace MediPathScanner {
    class ScanService {
    public:
        inline static ScanService &getInstance() {
            static ScanService instance;
            return instance;
        }

        void init(const YAML::Node &node);

        static void initNewTask();

        static void handleViewFrame(const std::shared_ptr<FrameCopy> frame);

        static void handleScanFrame(const std::shared_ptr<FrameCopy> frame);

    private:
        ScanService() = default;

        ScanService(const ScanService &) = delete;

        ScanService &operator=(const ScanService &) = delete;

        ~ScanService() = default;
    };
}


#endif //MEDIPATHSCANNER_SCANSERVICE_HPP
