/*
 * MainWindow.h
 *
 *  Created on: 21/08/2014
 *      Author: magnus
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "CardLibrary.h"
#include "CardScanner.h"

#include <gtkmm.h>

class MainWindow : public Gtk::Window
{
	public:
		MainWindow();
		virtual ~MainWindow();
		
	protected:
		//Signal handlers:
		
		//Child widgets:
		Gtk::Notebook m_Notebook;
		
		CardLibrary m_CardLibrary;
		CardScanner m_CardScanner;
		
		bool LookUpCardByName( const std::string& cardName );
		
};

#endif /* MAINWINDOW_H_ */
