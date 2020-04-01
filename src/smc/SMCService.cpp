//
// Created by jzb on 2020/3/31.
//

#include "SMCService.hpp"
#include "SMCEngine.h"
#include "../exception/AppException.hpp"

namespace {
    SMCEngContext kSMCContext;
}

namespace MediPathScanner {
    SMCService &SMCService::init(const YAML::Node &config) {
//    SMCEngInitParam initParam;
//    SMCEng_GetDefaultParameter(&initParam);
//    initParam.blockMode = config["smc"]["blockMode"].as<int>();
//    initParam.smcip = config["smc"]["smcip"].as<std::string>().c_str();
//    initParam.dBeginParking[AXIS_X] = config["smc"]["beginParking"]["X"].as<double>();
//    initParam.dBeginParking[AXIS_Y] = config["smc"]["beginParking"]["Y"].as<double>();
//    initParam.dBeginParking[AXIS_Z] = config["smc"]["beginParking"]["Z"].as<double>();
//    initParam.dEndParking[AXIS_X] = config["smc"]["endParking"]["X"].as<double>();
//    initParam.dEndParking[AXIS_Y] = config["smc"]["endParking"]["Y"].as<double>();
//    initParam.dEndParking[AXIS_Z] = config["smc"]["endParking"]["Z"].as<double>();
//    if (SMCEng_Init(&initParam, &kSMCContext) != SMCE_NOERROR) {
//        spdlog::log(spdlog::level::err, "SMCEng_Init fail");
//        throw "";
//    }
//    if (SMCEng_Reset(kSMCContext, 255) != SMCE_NOERROR) {
//        spdlog::log(spdlog::level::err, "SMCEng_Reset fail");
//        throw "";
//    }
//    spdlog::log(spdlog::level::info, "===SMCService::init success===");
//    return getInstance();
    }
}