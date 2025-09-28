// Copyright (c) 2025 CyberCortex Robotics SRL. All rights reserved
// Author: Sorin Mihai Grigorescu

#ifndef CMONOCAMERA_H_
#define CMONOCAMERA_H_

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include "CyC_TYPES.h"
#include "CCycFilterBase.h"
#include "os/CFilterUtils.h"
#include "sensors/CPinholeCameraSensorModel.h"
#include <os/CCsvReader.h>
#include "vision/CProjectiveGeometry.h"
#include "vision/CImageDisplayUtils.h"
#include "vision/CTriangulation.h"

class CCameraFilter : public CCycFilterBase
{
public:
    enum MonoCameraInterfaceType
    {
        MONO_CAMERA_SIM_INTERFACE = 0,
        MONO_CAMERA_USB_INTERFACE = 1,
        MONO_CAMERA_UNITY_INTERFACE = 2,
        MONO_CAMERA_RASPI_INTERFACE = 3,
        MONO_CAMERA_ARDRONE_INTERFACE = 4,
        MONO_CAMERA_ANAFI_INTERFACE = 5
    };

public:
    explicit CCameraFilter(CycDatablockKey _key);
    explicit CCameraFilter(ConfigFilterParameters _params);
    ~CCameraFilter() override;

    bool enable() override;
    bool disable() override;

private:
    bool	    process() override;
    void        loadFromDatastream(const std::string& _datastream_entry, const std::string& _db_root_path) override;
    static int  StringToEnumType(const std::string& _str_type);

private:
    bool          m_bRectifyImages;

    // Updates pose of the camera
    CCycFilterBase*   m_pPoseDataFilter = nullptr;
    CyC_TIME_UNIT     m_lastReadTsPose = 0;

private:
    cv::VideoCapture	      m_VideoCapture;

    CyC_INT		m_nDeviceID;
    CyC_INT		m_nApiID;
    CyC_INT     m_InterfaceType = 0;

    // Voxels (in world coordinates system) used for simulated camera
    CycVoxels   m_Voxels;
};

#endif /* CMONOCAMERA_H_ */
