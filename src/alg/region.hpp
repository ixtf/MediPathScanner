#pragma once

#include <opencv2/opencv.hpp>

class Region {
public:
    Region() {};

    // gray - �Ҷ�ͼ
    // regions - ��Ҫɨ��ķ�������
    // ��������0
    int proc(cv::Mat gray, std::vector<cv::Rect> &regions);
};