#include "stitch.hpp"

Stitch::Stitch() {
    stitcher = cv::Stitcher::create(cv::Stitcher::Mode::SCANS);
}

int Stitch::proc(const std::vector<cv::Mat> &imglist, cv::Mat &output) {
    cv::Stitcher::Status status = stitcher->stitch(imglist, output);
    if (status != cv::Stitcher::OK)
        return 1;

    return 0;
}

