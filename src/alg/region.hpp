#pragma once

#include <opencv2/opencv.hpp>

class Region {
public:
    Region() {};

    // gray - 灰度图
    // regions - 需要扫描的方框区域
    // 正常返回0
    int proc(cv::Mat gray, std::vector<cv::Rect> &regions);
};