// Copyright (c) 2026 CyberCortex Robotics SRL. All rights reserved
// Author: Sorin Mihai Grigorescu

#include "CBinarySegmentationFilter.h"
#include <os/CCsvReader.h>

#define DYNALO_EXPORT_SYMBOLS
#include <dynalo/symbol_helper.hpp>

DYNALO_EXPORT CyC_FILTER_TYPE DYNALO_CALL getFilterType()
{
    CycDatablockKey key;
    return CBinarySegmentationFilter(key).getFilterType();
}

DYNALO_EXPORT CCycFilterBase* DYNALO_CALL createFilter(const ConfigFilterParameters _params)
{
    return new CBinarySegmentationFilter(_params);
}

CBinarySegmentationFilter::CBinarySegmentationFilter(CycDatablockKey key) :
    CCycFilterBase(key)
{
    // Assign the filter type, input type and output type
    setFilterType("CyC_BINARY_SEGMENTATION_FILTER_TYPE");
    m_OutputDataType = CyC_IMAGE;

    // Set the segmentation parameters
    m_nLowHue = 0;
    m_nHighHue = 60;
    m_nLowSaturation = 80;
    m_nHighSaturation = 255;
    m_nLowValue = 70;
    m_nHighValue = 255;
}

CBinarySegmentationFilter::CBinarySegmentationFilter(const ConfigFilterParameters& params) :
    CCycFilterBase(params)
{
    // Assign the filter type, input type and output type
    setFilterType("CyC_BINARY_SEGMENTATION_FILTER_TYPE");
    m_OutputDataType = CyC_IMAGE;

    // Set the segmentation parameters
    m_nLowHue = 0;
    m_nHighHue = 60;
    m_nLowSaturation = 80;
    m_nHighSaturation = 255;
    m_nLowValue = 70;
    m_nHighValue = 255;
}

CBinarySegmentationFilter::~CBinarySegmentationFilter()
{
	if (m_bIsEnabled)
		disable();
}

bool CBinarySegmentationFilter::enable()
{
    // Check the number of input sources
	if (getInputSources().size() != 1)
	{
		spdlog::error("ERROR: The number of input filters must be 1. Disabling the BinarySegmentation filter.");
		return false;
	}
	else
	{
		// Connect the input data variables to the input data stream
		m_pInputFilter = getInputSources()[0].pCycFilter;
	}
    
	// Initialize data, if the input filter is enabled
	if(getInputSourcesEnabled())
	{
		//m_pInputFilter->getOutputDataStructure(m_imgInputRGB);
        
        // Initialize the output binary image
		//m_imgBinary = cv::Mat(m_imgInputRGB[0].nRows, m_imgInputRGB[0].nCols, CV_8UC1);
    	
        spdlog::info("Filter [{}-{}]: CBinarySegmentation::enable() successful", getFilterKey().nCoreID, getFilterKey().nFilterID);
		m_bIsEnabled = true;
	}
	else
	{
		m_bIsEnabled = false;
	}

	return m_bIsEnabled;
}

bool CBinarySegmentationFilter::disable()
{
	if (isRunning())
		stop();
	
    m_bIsEnabled = false;
	return true;
}

bool CBinarySegmentationFilter::process()
{
    bool bReturn(false);
    std::unordered_map<CycDatablockKey, CyC_TIME_UNIT> sync;

    const auto ts = m_pInputFilter->getTimestampStop();

    if(ts > m_tLastReadImage)
    {
        m_tLastReadImage = ts;
        
        // Read data from the input filter
        if (m_pInputFilter->getData(m_imgInputRGB))
        {
            // Store the timestamps of the input filters used to compute the output of this filter
            sync[m_pInputFilter->getFilterKey()] = m_pInputFilter->getTimestampStop();
            
            cv::Mat imgInputRGB(m_imgInputRGB[0].nRows, m_imgInputRGB[0].nCols, m_imgInputRGB[0].nType1);
            imgInputRGB.data = static_cast<uchar*>(m_imgInputRGB[0].pData1);

            // Convert from BGR to HSV colorspace
            cv::cvtColor(imgInputRGB, m_imgHSV, cv::COLOR_BGR2HSV);

            // Detect the object based on HSV Range Values
            cv::inRange(m_imgHSV,
                cv::Scalar(m_nLowHue, m_nLowSaturation, m_nLowValue),
                cv::Scalar(m_nHighHue, m_nHighSaturation, m_nHighValue),
                m_OutputBinaryImg);

            bReturn = true;
        }
    }

    if (bReturn)
    {
        CycImages output;
        output.emplace_back(m_OutputBinaryImg);
        updateData(output, sync);
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }

    return bReturn;
}

void CBinarySegmentationFilter::loadFromDatastream(const std::string& datastream_entry, const std::string& db_root_path)
{
    csv::reader::row row;
    row.parse_line(datastream_entry, ',');

    enum { TS_STOP, SAMPLING_TIME, IMAGE_PATH, NUM };
    if (row.size() != NUM)
    {
        spdlog::error("Wrong number of columns. {} provided, but expected {}.", row.size(), NUM);
        return;
    }

    const std::string img_path = db_root_path + row.get<std::string>(IMAGE_PATH);
    auto img = cv::imread(img_path, cv::IMREAD_ANYCOLOR);

    const auto tTimestampStop  = row.get<CyC_TIME_UNIT>(TS_STOP);
    const auto tSamplingTime   = row.get<CyC_TIME_UNIT>(SAMPLING_TIME);
    const auto tTimestampStart = tTimestampStop - tSamplingTime;

    updateData(img, std::unordered_map<CycDatablockKey, CyC_TIME_UNIT>(), tTimestampStart, tTimestampStop, tSamplingTime);
}
