/*
 * ExampleWorker.h
 *
 *  Created on: 14/10/2014
 *      Author: magnus
 */

#ifndef EXAMPLEWORKER_H_
#define EXAMPLEWORKER_H_

#include <gtkmm.h>

class ExampleWindow;

class ExampleWorker
{
	public:
		ExampleWorker();
		virtual ~ExampleWorker();
		
		// Thread function.
		void do_work( ExampleWindow* caller );
		
		void get_data( double* fraction_done, Glib::ustring* message ) const;
		void stop_work( void );
		bool has_stopped( void ) const;
		
	private:
		// Synchronizes access to member data.
		mutable Glib::Threads::Mutex m_Mutex;
		
		// Data used by both GUI thread and worker thread.
		bool m_shall_stop;
		bool m_has_stopped;
		double m_fraction_done;
		Glib::ustring m_message;
		
};

#endif /* EXAMPLEWORKER_H_ */
