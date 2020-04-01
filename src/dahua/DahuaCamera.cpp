//
// Created by jzb on 2020/3/31.
//

#include "DahuaCamera.hpp"
#include "spdlog/spdlog.h"
#include "../Defs.hpp"
#include "../Util.hpp"

namespace MediPathScanner {
    DahuaCamera::~DahuaCamera() {
        if (eventPtr_) {
            if (!eventPtr_->unsubscribeConnectArgs(ConnectArgProc(&DahuaCamera::onDeviceLinkNotify, this))) {
                Log::error("ip: {} Fail to call unsubscribeConnectArgs()", ip_);
            }
            eventPtr_.reset();
        }
        if (streamPtr_ && streamPtr_.get()) {
            if (!streamPtr_->detachGrabbing(IStreamSource::Proc(&DahuaCamera::onGetFrame, this))) {
                Log::error("ip: {} Fail to call detachGrabbing()", ip_);
            }
            if (!streamPtr_->stopGrabbing()) {
                Log::error("ip: {} Fail to call stopGrabbing()", ip_);
            }
            streamPtr_.reset();
        }
        if (cameraPtr_ && cameraPtr_.get()) {
            if (!cameraPtr_->disConnect()) {
                Log::error("ip: {} Fail to call disConnect()", ip_);
            }
            cameraPtr_.reset();
        }
    }

    void DahuaCamera::onGetFrame(CFrame const &frame) {
        auto valid = frame.valid();
        if (!valid) {
            Log::error("frame is invalid!");
            return;
        }
        if (frame.getImageSize() <= 0) {
            Log::error("frame.getImageSize() <= 0!");
            return;
        }
        Log::debug("onGetFrame {}", frame.getBlockId());
        std::shared_ptr<FrameCopy> copySptr(new FrameCopy{frame});
        frameHandler_(std::move(copySptr));
    }

    bool DahuaCamera::connect(int const retryCount) {
        switch (status_) {
            case INIT: {
                Dahua::Infra::TVector<ICameraPtr> vCameraPtrList;
                if (!CSystem::getInstance().discovery(vCameraPtrList)) {
                    status_ = ERR;
                    Log::error("discovery device fail");
                    throw "discovery device fail";
                }
                if (0 == vCameraPtrList.size()) {
                    status_ = ERR;
                    Log::error("vCameraPtrList=0");
                    throw "vCameraPtrList=0";
                }
                for (auto cameraPtr : vCameraPtrList) {
                    auto gigeCameraPtr = IGigECamera::getInstance(cameraPtr);
                    auto ip = gigeCameraPtr->getIpAddress();
                    if (ip == ip_.c_str()) {
                        cameraPtr_ = cameraPtr;
                        break;
                    }
                }
                if (NULL == cameraPtr_.get()) {
                    status_ = ERR;
                    Log::error("cameraPtr_ is null");
                    throw "cameraPtr_ is null";
                }
                for (int i = 0; i < retryCount; i++) {
                    if (cameraPtr_->connect()) {
                        break;
                    }
                    SLEEP(500);
                }
                if (!cameraPtr_->isConnected()) {
                    status_ = ERR;
                    Log::error("Retry connect fail");
                    throw "Retry connect fail";
                }

                auto acquisitionCtrlPtr = CSystem::getInstance().createAcquisitionControl(cameraPtr_);
                setLineTriggerConf(acquisitionCtrlPtr);

                // 创建事件对象
                eventPtr_ = CSystem::getInstance().createEventSubscribe(cameraPtr_);
                if (NULL == eventPtr_.get()) {
                    status_ = ERR;
                    Log::error("create event eventPtr_ fail");
                    throw "create event eventPtr_ fail";
                }
                if (!eventPtr_->subscribeConnectArgs(ConnectArgProc(&DahuaCamera::onDeviceLinkNotify, this))) {
                    status_ = ERR;
                    Log::error("DahuaCamera::onDeviceLinkNotify fail");
                    throw "DahuaCamera::onDeviceLinkNotify fail";
                }

                streamPtr_ = CSystem::getInstance().createStreamSource(cameraPtr_);
                if (NULL == streamPtr_.get()) {
                    status_ = ERR;
                    Log::error("create stream streamPtr_ fail");
                    throw "create stream streamPtr_ fail";
                }
                if (!streamPtr_->attachGrabbing(IStreamSource::Proc(&DahuaCamera::onGetFrame, this))) {
                    status_ = ERR;
                    Log::error("attachGrabbing fail");
                    throw "attachGrabbing fail";
                }
                if (!streamPtr_->startGrabbing()) {
                    status_ = ERR;
                    Log::error("start grab fail");
                    throw "start grab fail";
                }

                status_ = ON_LINE;
                Log::info("=== DahuaCamera {} success ===", ip_);
            }
        }
    }

    void DahuaCamera::setLineTriggerConf(IAcquisitionControlPtr acquisitionCtrlPtr) {
        auto enumNode = acquisitionCtrlPtr->triggerSource();
        if (!enumNode.setValueBySymbol("Line1")) {
            Log::error("set trigger source fail");
            throw "set trigger source fail";
        }

        enumNode = acquisitionCtrlPtr->triggerSelector();
        if (!enumNode.setValueBySymbol("FrameStart")) {
            Log::error("set trigger selector fail");
            throw "set trigger selector fail";
        }

        enumNode = acquisitionCtrlPtr->triggerMode();
        if (!enumNode.setValueBySymbol("On")) {
            Log::error("set trigger mode fail");
            throw "set trigger mode fail";
        }

        enumNode = acquisitionCtrlPtr->triggerActivation();
        if (!enumNode.setValueBySymbol("RisingEdge")) {
            Log::error("set trigger activation fail");
            throw "set trigger activation fail";
        }

        /*CDoubleNode doubleNode = sptrAcquisitionCtl->triggerDelay();
        bRet = doubleNode.setValue(30.0);
        if (bRet != true)
        {
            printf( "set trigger delay failed.");
            return false;
        }*/
    }

    void DahuaCamera::onDeviceLinkNotify(SConnectArg const &conArg) {
        // 如果只针对断线时的操作，只要接收到offLine时处理即可
        if (SConnectArg::offLine == conArg.m_event) {
            status_ = OFF_LINE;
            Log::info("camera is offline");
            if (streamPtr_.get()) {
                if (!streamPtr_->detachGrabbing(IStreamSource::Proc(&DahuaCamera::onGetFrame, this))) {
                    Log::error("detach stream callback fail");
                }
                if (!streamPtr_->stopGrabbing()) {
                    Log::error("stop grab fail");
                }
            }

            if (eventPtr_.get()) {
                if (!eventPtr_->unsubscribeConnectArgs(ConnectArgProc(&DahuaCamera::onDeviceLinkNotify, this))) {
                    Log::error("unsubscribeConnectArgs fail");
                }
            }
        } else if (SConnectArg::onLine == conArg.m_event) {
            tryToResumeConnect();
        }
    }

    bool DahuaCamera::tryToResumeConnect(int const retryCount) {
        // 断开相机连接
        if (!cameraPtr_->disConnect()) {
            Log::error("*******  disConnect failed  *******");
        }
        for (int i = 0; i < retryCount; i++) {
            if (cameraPtr_->connect()) {
                break;
            }
            SLEEP(500);
        }
        if (!cameraPtr_->isConnected()) {
            status_ = ERR;
            Log::error("Retry connect fail");
            return false;
        }

        eventPtr_.reset();
        eventPtr_ = CSystem::getInstance().createEventSubscribe(cameraPtr_);
        if (!eventPtr_->subscribeConnectArgs(ConnectArgProc(&DahuaCamera::onDeviceLinkNotify, this))) {
            status_ = ERR;
            Log::error("DahuaCamera::onDeviceLinkNotify fail");
            return false;
        }

        streamPtr_.reset();
        streamPtr_ = CSystem::getInstance().createStreamSource(cameraPtr_);
        if (NULL == streamPtr_.get()) {
            status_ = ERR;
            Log::error("create stream obj fail");
            return false;
        }
        if (!streamPtr_->attachGrabbing(IStreamSource::Proc(&DahuaCamera::onGetFrame, this))) {
            status_ = ERR;
            Log::error("attachGrabbing fail");
            return false;
        }
        if (!streamPtr_->startGrabbing()) {
            status_ = ERR;
            Log::error("startGrabbing fail");
            return false;
        }

        status_ = ON_LINE;
        return true;
    }
}