/*
 * example.cpp
 *
 *  Created on: 14/10/2014
 *      Author: magnus
 */

#include "ExampleWindow.h"

#include <gtkmm.h>
#include <iostream>

int main( int argc, char **argv )
{
	
	try
	{
		
		Gtk::Main kit(argc, argv);
		
		ExampleWindow ew;
		
		//Shows the window and returns when it is closed.
		kit.run( ew );
		
	}
	catch ( const Glib::Error& ex )
	{
		
		std::cerr << "Exception caught: " << ex.what() << std::endl;
		
	}
	
	return 0;
	
}
