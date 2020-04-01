//
// Created by jzb on 2020/4/1.
//

#ifndef MEDIPATHSCANNER_ALGSERVICE_HPP
#define MEDIPATHSCANNER_ALGSERVICE_HPP

#include <opencv2/opencv.hpp>

namespace MediPathScanner {
    class AlgService {
    public:
        inline static AlgService &getInstance() {
            static AlgService instance;
            return instance;
        }

        void region(const std::string filename, std::vector<cv::Rect> &regions);

    private:
        AlgService() = default;

        AlgService(const AlgService &) = delete;

        AlgService &operator=(const AlgService &) = delete;

        ~AlgService() = default;
    };
}


#endif //MEDIPATHSCANNER_ALGSERVICE_HPP
