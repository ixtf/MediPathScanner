//
// Created by jzb on 2020/3/31.
//

#ifndef MEDIPATHSCANNER_SMCSERVICE_HPP
#define MEDIPATHSCANNER_SMCSERVICE_HPP


#include <yaml-cpp/yaml.h>

namespace MediPathScanner {
    class SMCService {
    public:
        inline static SMCService &getInstance() {
            static SMCService instance;
            return instance;
        }

        static SMCService &init(const YAML::Node &config);

    private:
        SMCService() = default;

        SMCService(const SMCService &) = delete;

        SMCService &operator=(const SMCService &) = delete;

        ~SMCService() = default;
    };
}


#endif //MEDIPATHSCANNER_SMCSERVICE_HPP
