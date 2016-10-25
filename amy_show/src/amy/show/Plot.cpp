/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/highgui/highgui.hpp>  // for named window
#include <vector>

#include "amy/show/Plot.h"

namespace amy 
{
void Plot::plotRecord(Record& oRecord, int maxRange)
{  
    // create clean RGB image
    cv::Mat image = cv::Mat::zeros(PLOT_H, PLOT_W, CV_8UC3); 

    // get limits of magnitude
    oRecord.findRecordLimits();
    
    // get x factor to fill timeline in plot
    float xfactor = (float)(PLOT_W - LEFT_MARGIN - MARGIN) / oRecord.getMaxTime();
    // get y factor to fill max range in plot
    float yfactor = (float)(PLOT_H/2 - MARGIN) / maxRange;

    const int POS_XAXIS = PLOT_H/2;            
    cv::Scalar color = cv::Scalar(255, 255, 255);  // white
    
    // draw axis
    drawAxes(image, POS_XAXIS, yfactor);
    
    // plot records  in image  
    std::vector<recordElement>& listRecords = oRecord.getRecords();         
    for (recordElement& element : listRecords)
    {        
        int x = LEFT_MARGIN + xfactor * element.time;
        // draw upside-down
        int y = POS_XAXIS - yfactor * element.val1;
        // ignore points that fall out of plot
        if (y >= 0 && y<PLOT_H)
        {
            cv::circle(image, cv::Point(x, y), 3, color);           
        }
    }
    
    // show plot
    cv::namedWindow("plot");         
    cv::imshow("plot", image);
    cv::waitKey(5000);
    //cv::destroyWindow("plot");
    cv::destroyAllWindows();
}

void Plot::drawAxes(cv::Mat image, int POS_XAXIS, float yfactor)
{
    cv::Scalar colorAxis = cv::Scalar(0, 0, 255);  // red
    // axes
    cv::Point x0 = cv::Point(LEFT_MARGIN, POS_XAXIS);
    cv::Point x1 = cv::Point(PLOT_W-1, POS_XAXIS);
    cv::Point y0 = cv::Point(LEFT_MARGIN, 0);
    cv::Point y1 = cv::Point(LEFT_MARGIN, PLOT_H-1);    
    cv::line(image, x0, x1, colorAxis);
    cv::line(image, y0, y1, colorAxis);   
    // scale line 50
    cv::Scalar colorScale = cv::Scalar(255, 255, 255);  // white
    int y50 = POS_XAXIS - (yfactor * 50);    
    x0 = cv::Point(LEFT_MARGIN, y50);
    x1 = cv::Point(PLOT_W-1, y50);
    cv::line(image, x0, x1, colorScale);
    // scale line -50
    int ym50 = POS_XAXIS - (yfactor * -50);
    x0 = cv::Point(LEFT_MARGIN, ym50);
    x1 = cv::Point(PLOT_W-1, ym50);    
    cv::line(image, x0, x1, colorScale);
}

}