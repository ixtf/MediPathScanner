#pragma once

#include <opencv2/opencv.hpp>

class Stitch {
private:
    cv::Ptr<cv::Stitcher> stitcher;

public:
    Stitch();

    // imglist - 图像数据，不分顺序, 相邻图像的重叠区域需 >= 1/4
    // output - 拼接好的图像
    // 正常返回0
    int proc(const std::vector<cv::Mat> &imglist, cv::Mat &output);
};