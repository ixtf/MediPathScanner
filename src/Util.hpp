//
// Created by jzb on 2020/3/31.
//

#ifndef MEDIPATHSCANNER_UTIL_HPP
#define MEDIPATHSCANNER_UTIL_HPP

#include <yaml-cpp/yaml.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

using json = nlohmann::json;
namespace Log = spdlog;

namespace MediPathScanner {
    namespace Util {
        YAML::Node &init(const std::string rootPath);

        const bool mkdir(const std::string path);

        const bool dirExists(const std::string path);
    }
}


#endif //MEDIPATHSCANNER_UTIL_HPP
