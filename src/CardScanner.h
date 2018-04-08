/*
 * CardScanner.h
 *
 *  Created on: 18/10/2014
 *      Author: magnus
 */

#ifndef CARDSCANNER_H_
#define CARDSCANNER_H_

#include "Picture.h"

#include <gtkmm.h>
#include <opencv2/highgui/highgui.hpp>
#include <tesseract/baseapi.h>
#include <vector>

// Scan mode lets you scan card after card and automatically add them to inventory.
// Detect mode shows instant info about a card.
enum
{
	CAMERAMODE_SCAN, // Default
	CAMERAMODE_DETECT
};

class CardScanner : public Gtk::HBox
{
	public:
		CardScanner();
		virtual ~CardScanner();
		
	protected:
		//Signal handlers:
		void onButtonClicked( void );
		void onValueChanged( void );
		
		Gtk::VBox m_VBox;
		Gtk::VBox m_VBoxRight;
		
		Gtk::ScrolledWindow m_ScrolledWindow;
		Gtk::ScrolledWindow m_ScrolledWindowConsole;
		
		Gtk::TextView m_TextView;
		Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
		
		Gtk::HScale m_HScale;
		double m_Tresh;
		Gtk::Adjustment m_AdjustmentTresh;
		
		Gtk::Button m_Button;
		
		std::vector<Picture *> m_Images;
		std::vector<Picture *>::iterator m_ImageIt;
		
		bool m_Terminate;
		
		Glib::Threads::Thread* m_Thread;
		Glib::Threads::Mutex m_MutexLiveWebCamImage;
		Glib::Threads::Mutex m_MutexTresh;
		
		int m_CameraMode;
		
		cv::VideoCapture m_VideoCapture;
		cv::Mat m_Frame;
		cv::Mat m_FrameRGB;
		std::vector<cv::Mat> m_RecentFrames;
		
		Gtk::Image m_LiveWebCamImage;
		Gtk::Image m_LiveWebCamImage2;
		Gtk::Image m_LiveWebCamImage3;
		
		void DisplayFrame( void );
		
		void LiveWebCam( void );
		void LookForCardName( void );
		void LookForCardOld2( void );
		void LookForCardOld( void );
		
		void LookForCardDB( std::string& s );
		
};

#endif /* CARDSCANNER_H_ */
