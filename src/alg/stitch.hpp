#pragma once

#include <opencv2/opencv.hpp>

class Stitch {
private:
    cv::Ptr<cv::Stitcher> stitcher;

public:
    Stitch();

    // imglist - ͼ�����ݣ�����˳��, ����ͼ����ص������� >= 1/4
    // output - ƴ�Ӻõ�ͼ��
    // ��������0
    int proc(const std::vector<cv::Mat> &imglist, cv::Mat &output);
};