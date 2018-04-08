/*
 * MainWindow.cpp
 *
 *  Created on: 21/08/2014
 *      Author: magnus
 */

#include "MainWindow.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include <mysql++.h>

MainWindow::MainWindow()
{
	
	set_title( "Collectible Card Games Scanner" );
	set_default_size( 1024, 768 );
	set_border_width( 0 );
	
	add( m_Notebook );
	
//	m_Notebook.append_page( m_CardLibrary, "Library" );
	m_Notebook.append_page( m_CardScanner, "Scanner" );
	m_Notebook.append_page( m_CardLibrary, "Library" );
	
	show_all();
	
}

MainWindow::~MainWindow()
{
	std::cout << "----------END--------------" << std::endl;
	std::cout << "----------END--------------" << std::endl;
	std::cout << "----------END--------------" << std::endl;
	std::cout << "----------END--------------" << std::endl;
}

bool MainWindow::LookUpCardByName( const std::string& cardName )
{
	
	mysqlpp::Connection conn( false );
	conn.connect( "magic_cards", "localhost", USERNAME, PASSWORD );
	
	// Check if user name is free
	mysqlpp::Query query = conn.query( "SELECT * FROM cards WHERE name = \"" + cardName + "\" LIMIT 1" );
	mysqlpp::StoreQueryResult res = query.store();

	return res.num_rows() != 0;
	
}
