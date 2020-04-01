//
// Created by jzb on 2020/3/31.
//

#include "Util.hpp"
#include <spdlog/async.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace {
    std::string kRootPath;
    YAML::Node kConfig;
    std::shared_ptr<spdlog::logger> kFileLogger = nullptr;

    int _mkdir(const char *path) {
        return mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
}

namespace MediPathScanner {
    namespace Util {
        YAML::Node &init(const std::string rootPath) {
            kRootPath = rootPath;
            kConfig = YAML::LoadFile(kRootPath + "/config.yml");
            kFileLogger = spdlog::rotating_logger_mt<spdlog::async_factory>("file", rootPath + "/log/log",
                                                                            1024 * 1024 * 5, 3);

            spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e thread %t] [%l] %v");
            if (kConfig["prod"].as<bool>()) {
                spdlog::set_level(spdlog::level::info);
                spdlog::set_default_logger(kFileLogger);
            } else {
                spdlog::set_level(spdlog::level::debug);
            }
            return kConfig;
        }

        const bool dirExists(const std::string path) {
            struct stat st;
            stat(path.c_str(), &st);
            return st.st_mode & S_IFDIR;
        }

        const bool mkdir(const std::string path) {
            if (path.empty()) {
                return false;
            }

            if (path[0] == '/') {

            }
            std::string current_level = "/";
            std::string level;
            std::stringstream ss(path);

            // split path using slash as a separator
            while (std::getline(ss, level, '/')) {
                current_level += level; // append folder to the current level

                // create current level
                if (!dirExists(current_level) && _mkdir(current_level.c_str()) != 0)
                    return -1;

                current_level += "/"; // don't forget to append a slash
            }
            return 0;
        }
    }
}
