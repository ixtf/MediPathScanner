//
// Created by jzb on 2020/4/1.
//

#include "AlgService.hpp"
#include "region.hpp"

namespace MediPathScanner {
    void AlgService::region(const std::string filename, std::vector<cv::Rect> &regions) {
        Region rg;
        cv::Mat I = cv::imread(filename, 0);
        rg.proc(I, regions);
    }
}