/********************************************
 * FILE NAME: preprocessing.cpp             *
 * DESCRIPTION:                             *
 * VERSION:                                 *
 * AUTHORS: Victor García                   *
 * MODIFIED BY: José Cappelletto            *
 ********************************************/

/*
	Based on original helper function from *mosaic* respository. Snapshot of

	commit 849b20407eebb5c2f5caac1f2389ab6a914259c1
	Author: victorygc <victorygarciac@gmail.com>
	Date:   Wed Jan 31 01:37:49 2018 -0400
	
	Intended to improve current histogram stretching implementation, from percentil based
	RGB channel stretch, to a more general channel-by-channel basis. This will also improve
	*uwimageproc* histretch module, as it will include the percentil based approach
	Currently being handled in a separate branch
*/

#include "preprocessing.h"

void getHistogram(cv::Mat img, int *histogram){    
	int i = 0, j = 0;

    // Initializing the histogram. TODO: Check if there is a faster way
    for(i=0; i<256; i++){
        histogram[i] = 0;
    }
	// by using aux variables, we decrease overhead create by multiple calls to cvMat image methods to retrieve its size
	// TODO: is it possible to measure the impact?
	int width, height;
	width = img.size().width;
	height = img.size().height;
    // Computing the histogram as a cumulative of each integer value. WARNING: this will fail for any non-integer image matrix
    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
			int value = img.at<int>(i,j);
            histogram[value] += 1;
        }
    }
}

void printHistogram(int histogram[256], std::string filename, cv::Scalar color){
    // Finding the maximum value of the histogram. It will be used to scale the
    // histogram to fit the image.
    int max = 0, i;
    for(i=0; i<256; i++){
        if( histogram[i] > max ) max= histogram[i];
    }
    // Creating an image from the histogram.
    cv::Mat imgHist(1480,1580, CV_8UC3, cv::Scalar(255,255,255));
    cv::Point pt1, pt2;
    pt1.y = 1380;
    for(i=0; i<256; i++){
        pt1.x = 150 + 5*i + 1;
        pt2.x = 150 + 5*i + 3;
        pt2.y = 1380 - 1280 * histogram[i] / max;
        cv::rectangle(imgHist,pt1,pt2,color,CV_FILLED);
    }
    // y-axis labels
    cv::rectangle(imgHist,cv::Point(130,1400),cv::Point(1450,80),cvScalar(0,0,0),1);
    cv::putText(imgHist, std::to_string(max), cv::Point(10,100), cv::FONT_HERSHEY_PLAIN, 1.5, cvScalar(0,0,0), 2.0);
    cv::putText(imgHist, std::to_string(max*3/4), cv::Point(10,420), cv::FONT_HERSHEY_PLAIN, 1.5, cvScalar(0,0,0), 2.0);
    cv::putText(imgHist, std::to_string(max/2), cv::Point(10,740), cv::FONT_HERSHEY_PLAIN, 1.5, cvScalar(0,0,0), 2.0);
    cv::putText(imgHist, std::to_string(max/4), cv::Point(10,1060), cv::FONT_HERSHEY_PLAIN, 1.5, cvScalar(0,0,0), 2.0);
    cv::putText(imgHist, std::to_string(0), cv::Point(10,1380), cv::FONT_HERSHEY_PLAIN, 1.5, cvScalar(0,0,0), 2.0);
    // x-axis labels
    cv::putText(imgHist, std::to_string(0), cv::Point(152-7*1,1430), cv::FONT_HERSHEY_PLAIN, 1.5, cvScalar(0,0,0), 2.0);
    cv::putText(imgHist, std::to_string(63), cv::Point(467-7*2,1430), cv::FONT_HERSHEY_PLAIN, 1.5, cvScalar(0,0,0), 2.0);
    cv::putText(imgHist, std::to_string(127), cv::Point(787-7*3,1430), cv::FONT_HERSHEY_PLAIN, 1.5, cvScalar(0,0,0), 2.0);
    cv::putText(imgHist, std::to_string(191), cv::Point(1107-7*3,1430), cv::FONT_HERSHEY_PLAIN, 1.5, cvScalar(0,0,0), 2.0);
    cv::putText(imgHist, std::to_string(255), cv::Point(1427-7*3,1430), cv::FONT_HERSHEY_PLAIN, 1.5, cvScalar(0,0,0), 2.0);

    // Saving the image
    cv::imwrite(filename, imgHist);
}

// Now it will operate in a single channel of the provided image. So, future implementations will require a function call per channel (still faster)
void colorChannelStretch(cv::Mat imgOriginal, cv::Mat imgStretched, int lowerPercentile, int higherPercentile){
    // Computing the histograms
    int histogram[256];
    getHistogram(imgOriginal, histogram);

    // Computing the percentiles. We force invalid values as initial values (just in case)
    int channelLowerPercentile = -1, channelHigherPercentile = -1;

    // Channel percentiles
    int i = 0, sum = 0;
	// Added aux var to reduce img.methods calls
	float normImgSize = imgOriginal.size().height * imgOriginal.size().width / 100.0;
	// while we don't reach the highPercentile threshold...    
	// Tis is some fashion of CFD: cumulative function distribution
	while ( sum < higherPercentile * normImgSize ){
        if(sum < normImgSize) channelLowerPercentile++;
        channelHigherPercentile++;
        sum += histogram[i];
        i++;
    }

    // Creating the modified image, imgStretched, pixel by pixel // TODO: this can be done in a single operation as y = m.x+b
    int j;
    for(i=0; i<imgOriginal.size().height; i++){
        for(j=0; j<imgOriginal.size().width; j++){
            // Single channel image 
            if ( imgOriginal.at<int>(i,j) < channelLowerPercentile) imgStretched.at<int>(i,j) = 0;
            else if ( imgOriginal.at<int>(i,j) > channelHigherPercentile ) imgStretched.at<int>(i,j) = 255;
            else imgStretched.at<int>(i,j) = ( 255 * ( imgOriginal.at<int>(i,j) - channelLowerPercentile ) ) / ( channelHigherPercentile - channelLowerPercentile );
        }
    }
}
