/*
 * CardScanner.cpp
 *
 *  Created on: 18/10/2014
 *      Author: magnus
 */

#include "CardScanner.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include <mysql++.h>
#include <ssqls.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

CardScanner::CardScanner() :
	m_refTextBuffer( Gtk::TextBuffer::create() ),
	m_Tresh( 100.0 ),
	m_AdjustmentTresh( m_Tresh, 0.0, 255.0 ),
	m_Button( "Add image" ),
	m_Terminate( false ),
	m_CameraMode( CAMERAMODE_SCAN ),
	m_VideoCapture( -1 )
{
	
	m_Button.signal_clicked().connect( sigc::mem_fun( *this, &CardScanner::onButtonClicked ) );
	m_AdjustmentTresh.signal_value_changed().connect( sigc::mem_fun( *this, &CardScanner::onValueChanged ) );
	
	m_ScrolledWindow.add( m_VBox );
	//Only show the scrollbars when they are necessary.
	m_ScrolledWindow.set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );
	
	pack_start( m_ScrolledWindow );
	pack_start( m_VBoxRight );
	
	m_ScrolledWindowConsole.add( m_TextView );
	//Only show the scrollbars when they are necessary:
	m_ScrolledWindowConsole.set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );
	
	m_VBoxRight.pack_start( m_LiveWebCamImage );
	m_VBoxRight.pack_start( m_LiveWebCamImage2 );
	m_VBoxRight.pack_start( m_LiveWebCamImage3 );
	m_VBoxRight.pack_start( m_ScrolledWindowConsole );
	m_VBoxRight.pack_start( m_HScale );
	m_VBoxRight.pack_start( m_Button );
	
	m_HScale.set_adjustment( m_AdjustmentTresh );
	
	m_TextView.set_buffer( m_refTextBuffer );
	
	if ( !m_VideoCapture.isOpened() )
	{
		std::cerr << "Failed to open a video device or video file!\n" << std::endl;
		exit( EXIT_FAILURE );
	}
	else
	{
		m_Thread = Glib::Threads::Thread::create( sigc::mem_fun( *this, &CardScanner::LiveWebCam ) );
	}
	
	m_refTextBuffer->insert( m_refTextBuffer->end(), "Ready..." );
	
}

CardScanner::~CardScanner()
{
	
	{
		Glib::Threads::Mutex::Lock lock( m_MutexLiveWebCamImage );
		m_Terminate = true;
	}
	
	m_Thread->join();
	
	for ( m_ImageIt = m_Images.begin(); m_ImageIt < m_Images.end(); m_ImageIt++ )
		delete *m_ImageIt;
	
}


void CardScanner::onButtonClicked( void )
{
	
	Glib::Threads::Mutex::Lock lock( m_MutexTresh );
	
	m_Images.push_back( new Picture( m_LiveWebCamImage.get_pixbuf()->copy() ) );
	
	m_VBox.pack_end( *m_Images.back(), Gtk::PACK_SHRINK );
	m_Images.back()->show();
	
	//cv::imwrite( "MagicCard.jpg", m_Frame );
	
}

void CardScanner::onValueChanged( void )
{
	
	Glib::Threads::Mutex::Lock lock( m_MutexTresh );
	
	m_Tresh = m_AdjustmentTresh.get_value();
	
}

void CardScanner::LiveWebCam( void )
{
	
	double x, y;
	
	x = m_VideoCapture.get( CV_CAP_PROP_FRAME_WIDTH );
	y = m_VideoCapture.get( CV_CAP_PROP_FRAME_HEIGHT );
	
	std::cout << x << "x" << y << std::endl;
	
	m_VideoCapture.set( CV_CAP_PROP_FRAME_WIDTH, 1280 );
	m_VideoCapture.set( CV_CAP_PROP_FRAME_HEIGHT, 720 );
	//m_VideoCapture.set( CV_CAP_PROP_FPS, 15 );
	
	x = m_VideoCapture.get( CV_CAP_PROP_FRAME_WIDTH );
	y = m_VideoCapture.get( CV_CAP_PROP_FRAME_HEIGHT );
	
	std::cout << x << "x" << y << std::endl;
	
	while ( 1 ) 
	{
		
		m_VideoCapture >> m_Frame;
		
		if ( m_Frame.empty() )
			break;
		
		LookForCardName();
		
		//color swap from openCV (BGR) to Gdk::Pixbuf (RGB)
		cv::cvtColor( m_Frame, m_FrameRGB, CV_BGR2RGB );
		
		//create gtk pixel buffer from opencv image
		Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data( (guint8*)m_FrameRGB.data, Gdk::COLORSPACE_RGB, false, 8, m_FrameRGB.cols, m_FrameRGB.rows, m_FrameRGB.step );
		
		//resize if screen resolution is too low to display both images next to each other
		/*float screenWidth = get_screen()->get_width();
		if ( screenWidth < 2 * m_Frame.cols )
		{
			float aspectRatio = (float)m_Frame.cols / (float)m_Frame.rows;
			pixbuf = pixbuf->scale_simple( static_cast<int>( screenWidth / 2 - 20 ), static_cast<int>( ( screenWidth / 2 - 20 ) / aspectRatio ), Gdk::INTERP_BILINEAR );
		}*/
		
		{
			Glib::Threads::Mutex::Lock lock( m_MutexLiveWebCamImage );
			
			if ( m_Terminate )
				break;
			
			m_LiveWebCamImage.set( pixbuf );
			
		}
		
		//LookForCardName();
		
	}
	
}

bool initTess( tesseract::TessBaseAPI& tess )
{
	
	std::string current = setlocale( LC_NUMERIC, NULL );
	setlocale( LC_NUMERIC, "C" );
	
	int ret = tess.Init( NULL, "eng", tesseract::OEM_TESSERACT_ONLY );
	
	setlocale( LC_NUMERIC, current.c_str() );
	
	return ret != -1;
	
}

void GetText( const cv::Mat& gray, std::string& s, int &c )
{
	
	tesseract::TessBaseAPI tess;
	
	if ( !initTess( tess ) )
	{
		std::cerr << "Could not initialize tesseract." << std::endl;
		exit( EXIT_FAILURE );
	}
	
	tess.SetPageSegMode( tesseract::PSM_AUTO );
	
	tess.SetImage( (uchar*)gray.data, gray.cols, gray.rows, 1, gray.cols );
	
	//m_refTextBuffer->set_text( tess.GetUTF8Text() );
	
	int *confi = tess.AllWordConfidences();
	int i = 0;
	std::cout << "-------------------------------------------------------------------------" << std::endl;
	while ( confi[i] != -1 )
	{
		c = confi[i];
		std::cout << confi[i] << "\t";
		i++;
	}
	delete []confi;
	
	s = tess.GetUTF8Text();
	std::cout << tess.GetUTF8Text() << std::endl;
	std::cout << "-------------------------------------------------------------------------" << std::endl;
	
}

std::vector<cv::Rect> detectLetters( const cv::Mat& img )
{
	
	std::vector<cv::Rect> boundRect;
	cv::Mat img_gray, img_sobel, img_threshold, element;
	cvtColor( img, img_gray, CV_BGR2GRAY );
	cv::Sobel( img_gray, img_sobel, CV_8U, 1, 0, 3, 1, 1, cv::BORDER_DEFAULT );
	cv::threshold( img_sobel, img_threshold, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY );
	element = getStructuringElement( cv::MORPH_RECT, cv::Size( 17, 3 ) );
	cv::morphologyEx( img_threshold, img_threshold, CV_MOP_CLOSE, element ); //Does the trick
	
	std::vector<std::vector<cv::Point> > contours;
	cv::findContours( img_threshold, contours, 0, 1 );
	
	std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
	for ( int i = 0; i < contours.size(); i++ )
		if ( contours[i].size() > 100 )
		{
			
			cv::approxPolyDP( cv::Mat( contours[i] ), contours_poly[i], 3, true );
			cv::Rect appRect( boundingRect( cv::Mat( contours_poly[i] ) ) );
			
			// Resize bounding rectangle so it gets a little bigger.
			int n = 30;
			int m = 20;
			appRect.x = std::max( appRect.x - ( n / 2 ), 0 );
			appRect.y = std::max( appRect.y - ( m / 2 ), 0 );
			appRect.width += n;
			appRect.height += m;
			if ( appRect.x + appRect.width > img.cols )
				appRect.width = img.cols - appRect.x;
			if ( appRect.y + appRect.height > img.rows )
				appRect.height = img.rows - appRect.y;
			
			if ( appRect.width > appRect.height )
				boundRect.push_back( appRect );
			
		}
	
	return boundRect;
	
}

void CardScanner::LookForCardName( void )
{
	
	/*static int framesSkipped = 15;
	
	if ( framesSkipped < 15 )
	{
		framesSkipped++;
		return;
	}
	framesSkipped = 0;*/
	
	//cv::Mat gray;
	//cv::cvtColor( m_Frame, gray, CV_BGR2GRAY );
	
	//GetText( gray );
	
	std::vector<cv::Rect> letterBBoxes1 = detectLetters( m_Frame );
	
	static int framesSkipped = 15;
	
	if ( framesSkipped < 15 )
	{
		framesSkipped++;
	}
	else
	{
		framesSkipped = 0;
		/*for ( int i = 0; i < std::min( letterBBoxes1.size(), (size_t)2 ); i++ )
		{
			cv::Mat img = m_Frame( letterBBoxes1[i] );
			GetText( img );
		}*/
		
		if ( !letterBBoxes1.empty() )
		{
			std::string cardName;
			int c = 0;
			
			cv::Mat img = m_Frame( letterBBoxes1[0] );
			cv::cvtColor( img, img, CV_BGR2GRAY );
//			GetText( img, s, c );
			
			cv::Mat img2 = m_Frame( letterBBoxes1[0] );
			//color swap from openCV (BGR) to Gdk::Pixbuf (RGB)
			cv::cvtColor( img2, img2, CV_BGR2RGB );
			cv::cvtColor( img2, img2, CV_RGB2GRAY );
			
			cv::Mat rgb = cv::Mat( img2.size(), CV_8UC3 ); //3 channels
			cv::cvtColor( img2, rgb, CV_GRAY2RGB ); //"pump" the greyscale channels up 3 color channels
			Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data( (guint8*)rgb.data, Gdk::COLORSPACE_RGB, false, 8, rgb.cols, rgb.rows, rgb.step );
			GetText( img2, cardName, c );
			//create gtk pixel buffer from opencv image
			//Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data( (guint8*)img2.data, Gdk::COLORSPACE_RGB, false, 8, img2.cols, img2.rows, img2.step );
			//pixbuf->save( Glib::ustring::compose( "../pics/plains/%1-%2.png", s, c ), "png" );
			m_LiveWebCamImage2.set( pixbuf );
			
			this->LookForCardDB( cardName );
			
		}
		
	}
	
	/*if ( !letterBBoxes1.empty() )
	{
		cv::Mat img = m_Frame( letterBBoxes1[0] );
		
		cv::cvtColor( img, img, CV_BGR2RGB );
		
		//create gtk pixel buffer from opencv image
		Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data( (guint8*)img.data, Gdk::COLORSPACE_RGB, false, 8, img.cols, img.rows, img.step );
		m_LiveWebCamImage2.set( pixbuf );
	}*/
	
	for ( int i = 0; i < letterBBoxes1.size(); i++ )
		cv::rectangle( m_Frame, letterBBoxes1[i], cv::Scalar( 0, 255, 0 ), 3, 8, 0 );
	
}

void CardScanner::LookForCardDB( std::string& s )
{
	// TODO impliment db lookup.
	std::cout << "Not implimented yet.." << std::endl;
}

IplImage *CreateImage( int rows, int cols, int depth, int channels )
{
	
	IplImage *header = cvCreateImageHeader( cvSize( rows, cols ), depth, channels );
	cvCreateData( header );
	
	return header;
	
}

double SumSquared( const cv::Mat& img1, const cv::Mat& img2 )
{
	
	cv::Mat tmp( img1.rows, img1.cols, 8, 1 );// = CreateImage( img1.rows, img1.cols, 8, 1 );
	//std::cout << "k1" << std::endl;
	cv::subtract( img1, img2, tmp );
	//cv::absdiff( img1, img2, tmp );
	//cv::Mat tmp = img1 - img2;
	//std::cout << "k2" << std::endl;
	cv::pow( tmp, 2.0, tmp );
	//std::cout << "k3" << std::endl;
	double r = cv::sum( tmp ).val[0]; 
	return r;
	
}

void CardScanner::DisplayFrame( void )
{
	
	//color swap from openCV (BGR) to Gdk::Pixbuf (RGB)
	cv::cvtColor( m_Frame, m_Frame, CV_BGR2RGB );
	
	//create gtk pixel buffer from opencv image
	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data( (guint8*)m_Frame.data, Gdk::COLORSPACE_RGB, false, 8, m_Frame.cols, m_Frame.rows, m_Frame.step );
	
	Glib::Threads::Mutex::Lock lock( m_MutexLiveWebCamImage );
	m_LiveWebCamImage.set( pixbuf );
	
}

void CardScanner::LookForCardOld2( void )
{
	
	bool has_moved = false;
	bool been_to_base = true;
	
	double n_pixels = m_Frame.rows * m_Frame.cols;
	
	cv::Mat grey( m_Frame.rows, m_Frame.cols, 8, 1 );// = CreateImage( m_Frame.rows, m_Frame.cols, 8, 1 );
	m_RecentFrames.push_back( grey.clone() );
	/*cv::Mat base = grey.clone();
	cv::cvtColor( m_Frame, base, cv::COLOR_RGB2GRAY );
	cv::Mat tmp = grey.clone();*/
	
	while ( m_CameraMode == CAMERAMODE_SCAN )
	{
		
		m_VideoCapture >> m_Frame;
		//cv::cvtColor( m_Frame, grey, cv::COLOR_RGB2GRAY );
		
		double biggest_diff = 0;
		
		for ( std::vector<cv::Mat>::iterator it = m_RecentFrames.begin(); it != m_RecentFrames.end(); it++ )
			biggest_diff = cv::max( biggest_diff, SumSquared( grey, *it ) / n_pixels );
		
		m_RecentFrames.push_back( grey );
		
		if ( m_RecentFrames.size() > 3 )
			m_RecentFrames.erase( m_RecentFrames.begin() );
		
		// Set text on frame.
		Glib::ustring frameText = Glib::ustring::compose( "%1", biggest_diff );
		cv::putText( m_Frame, frameText.c_str(), cv::Point( 1, 24 ), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar( 255, 255, 244) );
		
		DisplayFrame();
		
	}
	
	m_refTextBuffer->insert( m_refTextBuffer->begin(), Glib::ustring::compose( "%1 * %2 = %3\n", m_Frame.rows, m_Frame.cols, n_pixels ) );
	
	usleep( 1000 );
	
}

void CardScanner::LookForCardOld( void )
{
	
	cv::Mat grayFrame;
	cv::RNG rng( 12345 );
	
	// Convert image to gray and blur it.
	cv::cvtColor( m_Frame, grayFrame, cv::COLOR_BGR2GRAY );
	cv::blur( grayFrame, grayFrame, cv::Size( 3, 3 ) );
	
	cv::Mat threshold_output;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	
	// Detect edges using Threshold.
	m_MutexTresh.lock();
	cv::threshold( grayFrame, threshold_output, m_Tresh, 255, cv::THRESH_BINARY );
	m_MutexTresh.unlock();
	// Find contours.
	cv::findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point( 0, 0 ) );
	
	// Approximate contours to polygons + get bounding rects and circles.
	std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
	std::vector<cv::Rect> boundRect( contours.size() );
	
	for ( size_t i = 0; i < contours.size(); i++ )
	{
		cv::approxPolyDP( cv::Mat( contours[i] ), contours_poly[i], 3, true );
		boundRect[i] = cv::boundingRect( cv::Mat( contours_poly[i] ) );
	}
	
	// Draw polygonal contour + bonding rects.
	cv::Mat drawing = cv::Mat::zeros( threshold_output.size(), CV_8UC3 );
	for ( size_t i = 0; i < contours.size(); i++ )
	{
		cv::Scalar color = cv::Scalar( rng.uniform( 0, 255 ), rng.uniform( 0, 255 ), rng.uniform( 0, 255 ) );
		//cv::drawContours( drawing, contours_poly, (int)i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point() );
		cv::rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
	}
	
	//cv::cvtColor( threshold_output, threshold_output, cv::COLOR_GRAY2BGR );
	//cv::cvtColor( threshold_output, threshold_output, cv::COLOR_BGR2RGB );
	//Glib::RefPtr<Gdk::Pixbuf> pixbuf2 = Gdk::Pixbuf::create_from_data( (guint8*)threshold_output.data, Gdk::COLORSPACE_RGB, false, 8, threshold_output.cols, threshold_output.rows, threshold_output.step );
	//m_LiveWebCamImage2.set( pixbuf2 );
	
	//cv::cvtColor( drawing, drawing, cv::COLOR_GRAY2BGR );
	//cv::cvtColor( drawing, drawing, cv::COLOR_BGR2RGB );
	Glib::RefPtr<Gdk::Pixbuf> pixbuf3 = Gdk::Pixbuf::create_from_data( (guint8*)drawing.data, Gdk::COLORSPACE_RGB, false, 8, drawing.cols, drawing.rows, drawing.step );
	
	m_LiveWebCamImage3.set( pixbuf3 );
	
	/*bool has_moved = false;
	bool been_to_base = true;
	
	//cv::Mat::MSize size = m_Frame.size;
	//n_pixels size[0]*size[1];
	int n_pixels = m_Frame.rows * m_Frame.cols;
	
	m_refTextBuffer->insert( m_refTextBuffer->begin(), Glib::ustring::compose( "%1 * %2 = %3\n", m_Frame.rows, m_Frame.cols, n_pixels ) );*/
	
	usleep( 1000 );
	
}
