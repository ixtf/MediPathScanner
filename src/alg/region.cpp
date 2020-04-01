#include "region.hpp"

using cv::Mat;

int get_roi_rect(Mat gray, cv::Rect &rect, float border_exp = 0.05f) {
    Mat labels, stats, centroids;
    int ncomp = connectedComponentsWithStats(gray > 128, labels, stats, centroids);
    if (ncomp <= 1)
        return 1;
    int maxidx(0), maxval(0);
    for (int i = 1; i < stats.rows; i++) {
        int v = stats.at<int>(i, 4);
        if (v > maxval) {
            maxidx = i;
            maxval = v;
        }
    }
    uchar *p = stats.ptr(maxidx);
    int l = ((int *) p)[0], t = ((int *) p)[1], w = ((int *) p)[2], h = ((int *) p)[3];
    int r = l + w, b = t + h;
    int bd = int(border_exp * MIN(w, h) + 0.5);
    l += bd;
    t += bd;
    r -= bd;
    b -= bd;
    if (l >= r || t >= b)
        return 1;
    rect.x = l;
    rect.y = t;
    rect.width = r - l;
    rect.height = b - t;
    return 0;
}

int Region::proc(cv::Mat gray, std::vector<cv::Rect> &regions) {
    regions.clear();

    const float SCALE = 0.25f;
    Mat I;
    cv::resize(gray, I, cv::Size(), SCALE, SCALE);
    cv::Rect roi;
    int res = get_roi_rect(I, roi);
    if (res)
        return res;

    I = I(cv::Range(roi.y, roi.y + roi.height), cv::Range(roi.x, roi.x + roi.width)).clone();
    // dog
    const float SIGMA1 = 1.f, SIGMA2 = 3.f;
    Mat g1, g2;
    cv::GaussianBlur(I, g1, cv::Size(int(2 * ceil(3 * SIGMA1) + 1), 1), SIGMA1);
    cv::GaussianBlur(I, g2, cv::Size(int(2 * ceil(3 * SIGMA2) + 1), 1), SIGMA2);
    g1.convertTo(g1, CV_32F);
    g2.convertTo(g2, CV_32F);
    Mat dog = g2 - g1;

    const float THRESH_BW = 5;
    Mat labels, stats, centroids;
    int ncomp = connectedComponentsWithStats(dog > THRESH_BW, labels, stats, centroids);

    const float THRESH_CONN = 50, EXPAND = 0.2f;
    for (int i = 1; i < stats.rows; i++) {
        uchar *p = stats.ptr(i);
        if (((int *) p)[4] >= THRESH_CONN) {
            int l = ((int *) p)[0], t = ((int *) p)[1], w = ((int *) p)[2], h = ((int *) p)[3];
            l += roi.x;
            t += roi.y;
            int r = l + w, b = t + h;
            l = int(float(l) / SCALE + 0.5);
            t = int(float(t) / SCALE + 0.5);
            r = int(float(r) / SCALE + 0.5);
            b = int(float(b) / SCALE + 0.5);
            int ex = int(EXPAND * MIN(r - l, b - t) + 0.5);
            l = MAX(0, l - ex);
            t = MAX(0, t - ex);
            r = MIN(gray.cols, r + ex);
            b = MIN(gray.rows, b + ex);
            regions.push_back(cv::Rect(l, t, r - l, b - t));
        }
    }

    return 0;
}
