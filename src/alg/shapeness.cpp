#include "shapeness.hpp"

using cv::Mat;

int Shapeness::proc(cv::Mat bgr, int magnitude, float &shapescore) {
    shapescore = 0;
    const float MAG = 20.f, SCALE = 0.5f;
    float scale = SCALE * MAG / magnitude;
    Mat gray;
    cv::cvtColor(bgr, gray, cv::COLOR_BGR2GRAY);
    cv::resize(gray, gray, cv::Size(), scale, scale);
    Mat dx, dy, mag;
    cv::Sobel(gray, dx, CV_32F, 1, 0);
    cv::Sobel(gray, dy, CV_32F, 0, 1);
    cv::magnitude(dx, dy, mag);
    shapescore = cv::mean(mag)[0];

    return 0;
}
