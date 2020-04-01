#include "Util.hpp"
#include "smc/SMCService.hpp"
#include "scan/ScanService.hpp"
#include "dahua/DahuaService.hpp"
#include "net/NetService.hpp"

#include <fstream>
#include <iomanip>

using namespace MediPathScanner;

void json_test(void) {
    json j;
    j["pi"] = 3.141;
    j["nothing"] = nullptr;
    j["list"] = {1, 0, 2};
    j["answer"]["everything"] = 42;
    j["object"] = {{"currency", "USD"},
                   {"value",    42.99}};
    std::cout << j.dump() << std::endl;

    auto j2 = R"({
                "happy": true,
                "pi": 3.141
              })"_json;
    std::cout << j2.dump(4) << std::endl;

    std::ofstream o1("/tmp/nlohmann/test.json");
    o1 << std::setw(4) << j << std::endl;
}

void yml_test(void) {
    YAML::Node node;
    node["test"] = true;
    std::ofstream o2("/tmp/nlohmann/test.yml");
    o2 << std::setw(4) << node << std::endl;

    auto status = MediPathScanner::Util::mkdir("/tmp/nlohmann/test1/test2");
    std::cout << std::setw(4) << status << std::endl;
}

int main() {
    const auto tp = std::chrono::system_clock::now();
    long l = std::chrono::system_clock::now().time_since_epoch().count();

    json_test();
    yml_test();

    auto config = MediPathScanner::Util::init("/home/jzb/CLionProjects/MediPathScanner");
    SMCService::getInstance().init(config);
    ScanService::getInstance().init(config);
    DahuaService::getInstance().init(config);
    NetService::getInstance().start(config);

    Log::info("=== rootPath: ===");

    spdlog::drop_all();
    return 0;
}
