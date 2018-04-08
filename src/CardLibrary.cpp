/*
 * CardLibrary.cpp
 *
 *  Created on: 18/10/2014
 *      Author: magnus
 */

#include "CardLibrary.h"

#include <mysql++.h>

CardLibrary::CardLibrary() :
	card1( 2049 ),
	card2( 4175 ),
	card3( 2166 ),
	card4( 4100 ),
	card5( 3828 )
{
	
	m_EventBox.add( m_ScrolledWindow );
	m_EventBox.modify_base( Gtk::STATE_NORMAL, Gdk::Color( "black" ) );
	
	m_ScrolledWindow.add( m_VBox );
	
	// Only show the scrollbars when they are necessary.
	m_ScrolledWindow.set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );
	
	pack_start( m_EventBox );
	
	m_VBox.pack_start( card1 );
	m_VBox.pack_start( card2 );
	m_VBox.pack_start( card3 );
	m_VBox.pack_start( card4 );
	m_VBox.pack_start( card5 );
	
}

CardLibrary::~CardLibrary()
{
	
}

void CardLibrary::onCardClicked( void )
{
	
}

void CardLibrary::FillTreeViewsModel( void )
{
	
//	mysqlpp::Connection conn( false );
//	conn.connect( "magic_cards", "localhost", USERNAME, PASSWORD );
//	
//	mysqlpp::Query query = conn.query( "SELECT * FROM cards" );
//	mysqlpp::StoreQueryResult res = query.store();
//	
//	// Fill the TreeView's model.
//	Gtk::TreeModel::Row row;
//	for ( int i = 0; i < res.num_rows(); i++ )
//	{
//		row = *( m_refTreeModel->append() );
//		row[m_Columns.m_col_id] = res[i]["id"];
//		mysqlpp::String k = res[i]["name"];
//		row[m_Columns.m_col_name] = k.c_str();
//		k = res[i]["set_name"];
//		row[m_Columns.m_col_set_name] = k.c_str();
//	}
	
}
