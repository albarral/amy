/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/highgui/highgui.hpp>  // for named window
#include <vector>

#include "amy/show/Plot.h"

namespace amy 
{
void Plot::plotRecord(Record& oRecord)
{  
    const int MARGIN = 40;  // size of plot margin (pixels)
    cv::Size size;
    
    // create image with size according to the record values that need to be plotted
    oRecord.findRecordLimits();
    // width depends on time
    size.width = oRecord.getMaxTime() + MARGIN;    
    // height depends on value range (bottom is 0 or negative)
    int bottom = (oRecord.getMinValue1() < 0 ? (int)oRecord.getMinValue1() : 0);
    size.height = (int)oRecord.getMaxValue1() - bottom + MARGIN;    
    // create clean RGB image
    cv::Mat image = cv::Mat::zeros(size.height, size.width, CV_8UC3); 
            
    cv::Scalar color = cv::Scalar(255, 255, 255);  // white
    cv::Scalar colorOrig = cv::Scalar(0, 0, 255);  // red
    // offset the y=0 position to allow showing negative values
    int zeroPos = abs(bottom) + 0.5*MARGIN;
    
    // draw origin
    cv::circle(image, cv::Point(0, zeroPos), 3, colorOrig);
    
    // plot records  in image  
    std::vector<recordElement>& listRecords = oRecord.getRecords();         
    for (recordElement& element : listRecords)
    {        
        cv::circle(image, cv::Point(element.time, (int)element.val1 + zeroPos), 3, color);
    }
    
    // show plot
    cv::namedWindow("plot");         
    cv::imshow("plot", image);
    cv::waitKey(0);
    cv::destroyWindow("plot");
}

}