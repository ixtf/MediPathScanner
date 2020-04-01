//
// Created by jzb on 2020/3/31.
//

#ifndef MEDIPATHSCANNER_DAHUACAMERA_HPP
#define MEDIPATHSCANNER_DAHUACAMERA_HPP

#include "GenICam/System.h"
#include "GenICam/Camera.h"
#include "GenICam/GigE/GigECamera.h"
#include "GenICam/GigE/GigEInterface.h"
#include "Infra/PrintLog.h"
#include "Memory/SharedPtr.h"
#include "FrameCopy.hpp"

using namespace Dahua::GenICam;

namespace MediPathScanner {
    class DahuaCamera {
    public:
        typedef std::function<void(const std::shared_ptr<FrameCopy>)> FrameHandler;

        enum Status {
            INIT,
            ERR,
            ON_LINE,
            OFF_LINE,
        };

        DahuaCamera(const std::string ip, const FrameHandler h) : ip_(ip), frameHandler_(h), status_(INIT) {}

        ~DahuaCamera();

        bool connect(int const retryCount = 100);

        void onGetFrame(const CFrame &frame);

        void onDeviceLinkNotify(const SConnectArg &conArg);

    private:
        const std::string ip_;
        const FrameHandler frameHandler_;
        Status status_;
        std::string errorMessage_;
        Dahua::GenICam::ICameraPtr cameraPtr_;
        Dahua::GenICam::IStreamSourcePtr streamPtr_;
        Dahua::GenICam::IEventSubscribePtr eventPtr_;

        void setLineTriggerConf(IAcquisitionControlPtr acquisitionCtrlPtr);

        bool tryToResumeConnect(int const retryCount = 100);
    };
}


#endif //MEDIPATHSCANNER_DAHUACAMERA_HPP
