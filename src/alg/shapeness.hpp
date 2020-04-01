#pragma once

#include <opencv2/opencv.hpp>

class Shapeness {
public    :
    Shapeness() {};

    // bgr - bgrͼ��
    // magnitude - ͼ��ķŴ���
    // shapescore - �õ��������ȷ���
    // ��������0
    int proc(cv::Mat bgr, int magnitude, float &shapescore);
};