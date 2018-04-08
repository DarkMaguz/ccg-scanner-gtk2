/*
 * snap.cpp
 *
 *  Created on: 17/10/2014
 *      Author: magnus
 */


#include <opencv2/opencv.hpp>

#include <iostream>

int main( int argc, char **argv )
{
	
	 if( argc != 2 )
	 {
	   std::cout << "Usage:\n  " << argv[0] << " FILE" << std::endl;
	   return EXIT_FAILURE;
	 }
	
	cv::VideoCapture vc( -1 );
	cv::Mat frame;
	
	if ( !vc.isOpened() )
	{
		std::cerr << "Failed to open a video device or video file!\n" << std::endl;
		exit( EXIT_FAILURE );
	}
	
	vc.set( CV_CAP_PROP_FRAME_WIDTH, 1280 );
	vc.set( CV_CAP_PROP_FRAME_HEIGHT, 720 );
	
	vc >> frame;
	
	imwrite( argv[1], frame );
	
	return EXIT_SUCCESS;
	
}
