cmake_minimum_required(VERSION 3.15)
project(MediPathScanner)

set(CMAKE_CXX_STANDARD 20)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_package(PkgConfig)
pkg_check_modules(YAMLCPP REQUIRED yaml-cpp>=0.6)
include_directories(${YAMLCPP_INCLUDE_DIRS})

find_package(RapidJSON REQUIRED)
set(NLOHMANN_DIR /home/jzb/git/nlohmann_json)
include_directories(${NLOHMANN_DIR}/single_include)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(RXCPP_DIR /home/jzb/git/RxCpp)
include_directories(${RXCPP_DIR}/Rx/v2/src)

set(SPDLOG_DIR /home/jzb/git/spdlog)
include_directories(${SPDLOG_DIR}/include)

set(DAHUA_DIR /opt/DahuaTech/MVviewer)
include_directories(${DAHUA_DIR}/include)
link_directories(${DAHUA_DIR}/lib)
link_directories(${DAHUA_DIR}/lib/GenICam/bin/Linux64_x64)

set(LIBJPEG_TURBO_DIR /opt/libjpeg-turbo)
include_directories(${LIBJPEG_TURBO_DIR}/include)
link_directories(${LIBJPEG_TURBO_DIR}/lib64)

add_executable(MediPathScanner src/main.cpp src/Defs.hpp src/Util.cpp src/Util.hpp src/exception/AppException.hpp
        src/scan/ScanService.cpp src/scan/ScanService.hpp src/scan/ScanTask.cpp src/scan/ScanTask.hpp
        src/net/NetService.cpp src/net/NetService.hpp
        src/smc/SMCService.cpp src/smc/SMCService.hpp src/smc/SMCEngine.h src/smc/ErrCodeDef.h
        src/alg/region.cpp src/alg/region.hpp src/alg/shapeness.cpp src/alg/shapeness.hpp src/alg/stitch.cpp src/alg/stitch.hpp
        src/dahua/DahuaService.cpp src/dahua/DahuaService.hpp src/dahua/DahuaCamera.cpp src/dahua/DahuaCamera.hpp src/dahua/FrameCopy.cpp src/dahua/FrameCopy.hpp
        src/alg/AlgService.cpp src/alg/AlgService.hpp src/scan/ScanRegion.cpp src/scan/ScanRegion.hpp)

target_link_libraries(MediPathScanner ${OpenCV_LIBS} ${YAMLCPP_LIBRARIES} Threads::Threads MVSDK ImageConvert turbojpeg jpeg)