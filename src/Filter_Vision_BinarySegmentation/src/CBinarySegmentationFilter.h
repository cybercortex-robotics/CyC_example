// Copyright (c) 2025 CyberCortex Robotics SRL. All rights reserved
// Author: Sorin Mihai Grigorescu

#ifndef CBinarySegmentationFilter_H_
#define CBinarySegmentationFilter_H_

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include "CyC_TYPES.h"
#include "CCycFilterBase.h"
#include "os/CTimer.h"

class CBinarySegmentationFilter: public CCycFilterBase
{
public:
	explicit CBinarySegmentationFilter(CycDatablockKey key);
	explicit CBinarySegmentationFilter(const ConfigFilterParameters& params);
	~CBinarySegmentationFilter() override;

	bool enable() override;
	bool disable() override;

private:
    void init();
    bool process() override;
    void loadFromDatastream(const std::string& datastream_entry, const std::string& db_root_path) override;

private:
	CCycFilterBase*	m_pInputFilter;
	CycImages		m_imgInputRGB;
	cv::Mat			m_imgHSV;
	cv::Mat			m_OutputBinaryImg;

	// Segmentation parameters
	CyC_UINT m_nLowHue;
	CyC_UINT m_nHighHue;
	CyC_UINT m_nLowSaturation;
	CyC_UINT m_nHighSaturation;
	CyC_UINT m_nLowValue;
	CyC_UINT m_nHighValue;

    CyC_TIME_UNIT m_tLastReadImage = 0;
};

#endif /* CBinarySegmentationFilter_H_ */
