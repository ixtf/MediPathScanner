//
// Created by jzb on 2020/3/31.
//

#ifndef MEDIPATHSCANNER_DAHUASERVICE_HPP
#define MEDIPATHSCANNER_DAHUASERVICE_HPP


#include <yaml-cpp/yaml.h>
#include "DahuaCamera.hpp"

namespace MediPathScanner {
    class DahuaService {
    public:
        inline static DahuaService &getInstance() {
            static DahuaService instance;
            return instance;
        }

        DahuaService &init(const YAML::Node &config);

    private:
        DahuaService() = default;

        DahuaService(const DahuaService &) = delete;

        DahuaService &operator=(const DahuaService &) = delete;

        ~DahuaService() = default;
    };
}

#endif //MEDIPATHSCANNER_DAHUASERVICE_HPP
