//
// Created by jzb on 2020/3/31.
//

#ifndef MEDIPATHSCANNER_NETSERVICE_HPP
#define MEDIPATHSCANNER_NETSERVICE_HPP


#include <yaml-cpp/yaml.h>

namespace MediPathScanner {
    class NetService {
    public:
        inline static NetService &getInstance() {
            static NetService instance;
            return instance;
        }

        void start(const YAML::Node &node);

    private:
        NetService() = default;

        NetService(const NetService &) = delete;

        NetService &operator=(const NetService &) = delete;

        ~NetService() = default;
    };
}

#endif //MEDIPATHSCANNER_NETSERVICE_HPP
