/*
 ============================================================================
 Name        : CCG_Scanner-gtk2.cpp
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C++,
 ============================================================================
 */

#include "MainWindow.h"

#include <gtkmm-2.4/gtkmm.h>
#include <iostream>

int main( int argc, char **argv )
{
	
	try
	{
		
		Gtk::Main kit( argc, argv );
		
		MainWindow mv;
		
		//Shows the window and returns when it is closed.
		kit.run( mv );
		
	}
	catch ( const Glib::Error& ex )
	{
		
		std::cerr << "Exception caught: " << ex.what() << std::endl;
		
	}
	
	return 0;
	
}
