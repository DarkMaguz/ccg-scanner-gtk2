/*
 * ExampleWindow.h
 *
 *  Created on: 14/10/2014
 *      Author: magnus
 */

#ifndef EXAMPLEWINDOW_H_
#define EXAMPLEWINDOW_H_

#include "ExampleWorker.h"

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
	public:
		ExampleWindow();
		virtual ~ExampleWindow();
		
		// Called from the worker thread.
		void notify( void );
		
	private:
		// Signal handlers.
		void on_start_button_clicked( void );
		void on_stop_button_clicked( void );
		void on_quit_button_clicked( void );
		
		void update_start_stop_buttons( void );
		void update_widgets( void );
		
		// Dispatcher handler.
		void on_notification_from_worker_thread( void );
		
		// Member data.
		Gtk::VBox m_VBox;
		Gtk::HButtonBox m_ButtonBox;
		Gtk::Button m_ButtonStart;
		Gtk::Button m_ButtonStop;
		Gtk::Button m_ButtonQuit;
		Gtk::ProgressBar m_ProgressBar;
		Gtk::ScrolledWindow m_ScrolledWindow;
		Gtk::TextView m_TextView;
		
		Glib::Dispatcher m_Dispatcher;
		ExampleWorker m_Worker;
		Glib::Threads::Thread* m_WorkerThread;
		
};

#endif /* EXAMPLEWINDOW_H_ */
