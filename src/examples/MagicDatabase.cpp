/*
 * MagicDatabase.cpp
 *
 *  Created on: 19/10/2014
 *      Author: magnus
 */

#include "MagicDatabase.h"

#include <uchardet.h>
#include <mysql++.h>
#include <fstream>
#include <iostream>

bool replace( Glib::ustring& str, const Glib::ustring& from, const Glib::ustring& to )
{
	
	size_t start_pos = str.find( from );
	
	if ( start_pos == Glib::ustring::npos )
		return false;
	
	str.replace( start_pos, from.length(), to );
	
	return true;
	
}

void CleanUpText2(  std::wstring& str )
{
	std::wcout << str << std::endl;
	std::cout << "---" << std::endl;
}

Glib::ustring MagicDatabase::CleanUpText( const char *text )
{
	
	Glib::ustring res = text;
	
//	uchardet_t ucd = uchardet_new();
//	uchardet_handle_data( ucd, text.c_str(), text.length() );
////	for ( std::vector<char *>::iterator it = m_CharSets.begin(); it != m_CharSets.end(); it++ )
////	{
////		
////	}
//	std::string cs = uchardet_get_charset( ucd );
//	remove_if( cs.begin(), cs.end(), isspace );
//	if ( !cs.empty() )
//	{
//		std::cout << cs << std::endl;
//	}
//	uchardet_reset( ucd );
//	uchardet_delete( ucd );
	
//	if ( !res.validate() )
//	{
//		
////		std::cout << Glib::locale_from_utf8( res ) << std::endl;
//		
////		for ( Glib::ustring::iterator it = res.begin(); it != res.end(); it++ )
////		{
////			if ( *it >= 256 )
////				std::cout << int( *it ) << std::setw( 10 ) << *it << std::endl;
//////				res.erase( it );
////		}
//		
//		std::cout << text << std::endl;
//		std::cout << "---" << std::endl;
//		
//	}
	
//	const Glib::ustring targets[] = { "#_", "_#", "\xa3", "\x97", "\x95" };
//	const Glib::ustring replacements[] = { "", "", "\n", "-", "*" };
//	
//	for ( int t = 0; t < 5; t++ )
//		while ( replace( res, targets[t], replacements[t] ) ) { }
	
//	for ( Glib::ustring::iterator it = res.begin(); it != res.end(); it++ )
//		if ( *it >= 256 )
////			std::cout << int( *it ) << std::endl;
//			res.erase( it );
	
	return res;
	
}

MagicDatabase::MagicDatabase() :
	m_Button_Quit( "Quit" )
{
	
	set_title( "Gtk::TreeView (ListStore) example" );
	set_border_width( 5 );
	//set_default_size( 400, 200 );
	maximize();
	
	add( m_VBox );
	
	//Add the TreeView, inside a ScrolledWindow, with the button underneath:
	m_ScrolledWindow.add( m_TreeView );
	
	//Only show the scrollbars when they are necessary:
	m_ScrolledWindow.set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );
	
	//m_VBox.pack_start( m_Label );
	m_VBox.pack_start( m_ScrolledWindow );
	m_VBox.pack_start( m_ButtonBox, Gtk::PACK_SHRINK );
	
	m_ButtonBox.pack_start( m_Button_Quit, Gtk::PACK_SHRINK );
	m_ButtonBox.set_border_width( 5 );
	m_ButtonBox.set_layout( Gtk::BUTTONBOX_END );
	m_Button_Quit.signal_clicked().connect( sigc::mem_fun( *this, &MagicDatabase::on_button_quit ) );
	
	//Create the Tree model:
	m_refTreeModel = Gtk::ListStore::create( m_Columns );
	m_TreeView.set_model( m_refTreeModel );
	
	//Fill the TreeView's model
	FillTreeViewsModel();
	
	//Add the TreeView's view columns:
	//This number will be shown with the default numeric formatting.
	m_TreeView.append_column( "Nid", m_Columns.Nid );
	m_TreeView.append_column( "Nname", m_Columns.Nname );
	m_TreeView.append_column( "Nset", m_Columns.Nset );
	m_TreeView.append_column( "Ntype", m_Columns.Ntype );
	m_TreeView.append_column( "Nrarity", m_Columns.Nrarity );
	m_TreeView.append_column( "Nmanacost", m_Columns.Nmanacost );
	m_TreeView.append_column( "Nconverted_manacost", m_Columns.Nconverted_manacost );
	m_TreeView.append_column( "Npower", m_Columns.Npower );
	m_TreeView.append_column( "Ntoughness", m_Columns.Ntoughness );
	m_TreeView.append_column( "Nloyalty", m_Columns.Nloyalty );
	m_TreeView.append_column( "Nability", m_Columns.Nability );
	m_TreeView.append_column( "Nflavor", m_Columns.Nflavor );
	m_TreeView.append_column( "Nvariation", m_Columns.Nvariation );
	m_TreeView.append_column( "Nartist", m_Columns.Nartist );
	m_TreeView.append_column( "Nnumber", m_Columns.Nnumber );
	m_TreeView.append_column( "Nrating", m_Columns.Nrating );
	m_TreeView.append_column( "Nruling", m_Columns.Nruling );
	m_TreeView.append_column( "Ncolor", m_Columns.Ncolor );
	m_TreeView.append_column( "Ngenerated_mana", m_Columns.Ngenerated_mana );
	m_TreeView.append_column( "Npricing_low", m_Columns.Npricing_low );
	m_TreeView.append_column( "Npricing_mid", m_Columns.Npricing_mid );
	m_TreeView.append_column( "Npricing_high", m_Columns.Npricing_high );
	m_TreeView.append_column( "Nback_id", m_Columns.Nback_id );
	m_TreeView.append_column( "Nwatermark", m_Columns.Nwatermark );
	m_TreeView.append_column( "Nprint_number", m_Columns.Nprint_number );
	m_TreeView.append_column( "Nis_original", m_Columns.Nis_original );
//	m_TreeView.append_column( "Nname_CN", m_Columns.Nname_CN );
//	m_TreeView.append_column( "Nname_TW", m_Columns.Nname_TW );
//	m_TreeView.append_column( "Nname_FR", m_Columns.Nname_FR );
//	m_TreeView.append_column( "Nname_DE", m_Columns.Nname_DE );
//	m_TreeView.append_column( "Nname_IT", m_Columns.Nname_IT );
//	m_TreeView.append_column( "Nname_JP", m_Columns.Nname_JP );
//	m_TreeView.append_column( "Nname_PT", m_Columns.Nname_PT );
//	m_TreeView.append_column( "Nname_RU", m_Columns.Nname_RU );
//	m_TreeView.append_column( "Nname_ES", m_Columns.Nname_ES );
//	m_TreeView.append_column( "Nname_KO", m_Columns.Nname_KO );
//	m_TreeView.append_column( "Ntype_CN", m_Columns.Ntype_CN );
//	m_TreeView.append_column( "Ntype_TW", m_Columns.Ntype_TW );
//	m_TreeView.append_column( "Ntype_FR", m_Columns.Ntype_FR );
//	m_TreeView.append_column( "Ntype_DE", m_Columns.Ntype_DE );
//	m_TreeView.append_column( "Ntype_IT", m_Columns.Ntype_IT );
//	m_TreeView.append_column( "Ntype_JP", m_Columns.Ntype_JP );
//	m_TreeView.append_column( "Ntype_PT", m_Columns.Ntype_PT );
//	m_TreeView.append_column( "Ntype_RU", m_Columns.Ntype_RU );
//	m_TreeView.append_column( "Ntype_ES", m_Columns.Ntype_ES );
//	m_TreeView.append_column( "Ntype_KO", m_Columns.Ntype_KO );
//	m_TreeView.append_column( "Nability_CN", m_Columns.Nability_CN );
//	m_TreeView.append_column( "Nability_TW", m_Columns.Nability_TW );
//	m_TreeView.append_column( "Nability_FR", m_Columns.Nability_FR );
//	m_TreeView.append_column( "Nability_DE", m_Columns.Nability_DE );
//	m_TreeView.append_column( "Nability_IT", m_Columns.Nability_IT );
//	m_TreeView.append_column( "Nability_JP", m_Columns.Nability_JP );
//	m_TreeView.append_column( "Nability_PT", m_Columns.Nability_PT );
//	m_TreeView.append_column( "Nability_RU", m_Columns.Nability_RU );
//	m_TreeView.append_column( "Nability_ES", m_Columns.Nability_ES );
//	m_TreeView.append_column( "Nability_KO", m_Columns.Nability_KO );
//	m_TreeView.append_column( "Nflavor_CN", m_Columns.Nflavor_CN );
//	m_TreeView.append_column( "Nflavor_TW", m_Columns.Nflavor_TW );
//	m_TreeView.append_column( "Nflavor_FR", m_Columns.Nflavor_FR );
//	m_TreeView.append_column( "Nflavor_DE", m_Columns.Nflavor_DE );
//	m_TreeView.append_column( "Nflavor_IT", m_Columns.Nflavor_IT );
//	m_TreeView.append_column( "Nflavor_JP", m_Columns.Nflavor_JP );
//	m_TreeView.append_column( "Nflavor_PT", m_Columns.Nflavor_PT );
//	m_TreeView.append_column( "Nflavor_RU", m_Columns.Nflavor_RU );
//	m_TreeView.append_column( "Nflavor_ES", m_Columns.Nflavor_ES );
//	m_TreeView.append_column( "Nflavor_KO", m_Columns.Nflavor_KO );
	m_TreeView.append_column( "Nlegality_Block", m_Columns.Nlegality_Block );
	m_TreeView.append_column( "Nlegality_Standard", m_Columns.Nlegality_Standard );
	m_TreeView.append_column( "Nlegality_Modern", m_Columns.Nlegality_Modern );
	m_TreeView.append_column( "Nlegality_Legacy", m_Columns.Nlegality_Legacy );
	m_TreeView.append_column( "Nlegality_Vintage", m_Columns.Nlegality_Vintage );
	m_TreeView.append_column( "Nlegality_Highlander", m_Columns.Nlegality_Highlander );
	m_TreeView.append_column( "Nlegality_French_Commander", m_Columns.Nlegality_French_Commander );
	m_TreeView.append_column( "Nlegality_Commander", m_Columns.Nlegality_Commander );
	m_TreeView.append_column( "Nlegality_Peasant", m_Columns.Nlegality_Peasant );
	m_TreeView.append_column( "Nlegality_Pauper", m_Columns.Nlegality_Pauper );
	
	//Make all the columns reorderable:
	//This is not necessary, but it's nice to show the feature.
	//You can use TreeView::set_column_drag_function() to more
	//finely control column drag and drop.
	Glib::ListHandle<Gtk::TreeViewColumn *> lh = m_TreeView.get_columns();
	for ( Glib::ListHandle<Gtk::TreeViewColumn *>::iterator it = lh.begin(); it != lh.end(); it++ )
		(*it)->set_reorderable();
	
	Gtk::TreeView::Column *pColumn = m_TreeView.get_column( 0 );
	pColumn->set_sort_column( m_Columns.Nid );
	pColumn = m_TreeView.get_column( 1 );
	pColumn->set_sort_column( m_Columns.Nname );
	pColumn = m_TreeView.get_column( 2 );
	pColumn->set_sort_column( m_Columns.Nset );
	pColumn = m_TreeView.get_column( 3 );
	pColumn->set_sort_column( m_Columns.Ntype );
	pColumn = m_TreeView.get_column( 4 );
	pColumn->set_sort_column( m_Columns.Nrarity );
	
	
	show_all_children();
	
}

MagicDatabase::~MagicDatabase()
{
}

void MagicDatabase::on_button_quit()
{
	hide();
}

void MagicDatabase::FillTreeViewsModel( void )
{
	
	try
	{
		
		mysqlpp::Connection conn( false );
		if ( !conn.connect( "magic_cards", "localhost", USERNAME, PASSWORD ) )
		{
			std::cerr << "DB connection failed: " << conn.error() << std::endl;
			return;
		}
		
		//mysqlpp::SetCharsetNameOption *cno = new mysqlpp::SetCharsetNameOption( "utf8" );
		//conn.set_option( cno );
		
		mysqlpp::Query query = conn.query();
		query << "SET NAMES 'utf8'";
		query.execute();
		
		query << "SELECT * FROM Ncards WHERE Nid = 26";
		//std::cout << "Query: " << query.str() << std::endl;
		mysqlpp::UseQueryResult uq_res = query.use();
		//mysqlpp::StoreQueryResult res = query.store();
		if ( !uq_res )
		{
			std::cerr << "Failed to get item list: " << query.error() << std::endl;
			return;
		}
		
		if ( uq_res.num_fields() < 1 )
		{
			std::cerr  << "Result set \"" << query.str() << "\" is empty: " << query.error() << std::endl;
			return;
		}
		
		Gtk::TreeModel::Row row;
		//for ( size_t i = 0; i < res.size(); i++ )
		while ( mysqlpp::Row res = uq_res.fetch_row() )
		{
			
//			uchardet_t ucd = uchardet_new();
//			uchardet_handle_data( ucd, res["Nability"].c_str(), res["Nability"].length() );
//			std::cout << uchardet_get_charset( ucd ) << std::endl;
//			uchardet_delete( ucd );
			
//			if ( CleanUpText( res["Nid"] == 5803 )
//			{
//				
//			}
			
			row = *( m_refTreeModel->append() );
			
			row[m_Columns.Nid] = res["Nid"];
			row[m_Columns.Nname] = CleanUpText( res["Nname"].c_str() );
			row[m_Columns.Nset] = CleanUpText( res["Nset"].c_str() );
			row[m_Columns.Ntype] = CleanUpText( res["Ntype"].c_str() );
			row[m_Columns.Nrarity] = CleanUpText( res["Nrarity"].c_str() );
			row[m_Columns.Nmanacost] = CleanUpText( res["Nmanacost"].c_str() );
			row[m_Columns.Nconverted_manacost] = res["Nconverted_manacost"];
			row[m_Columns.Npower] = CleanUpText( res["Npower"].c_str() );
			row[m_Columns.Ntoughness] = CleanUpText( res["Ntoughness"].c_str() );
			row[m_Columns.Nloyalty] = CleanUpText( res["Nloyalty"].c_str() );
			row[m_Columns.Nability] = CleanUpText( res["Nability"].c_str() );
			row[m_Columns.Nflavor] = CleanUpText( res["Nflavor"].c_str() );
			row[m_Columns.Nvariation] = CleanUpText( res["Nvariation"].c_str() );
			row[m_Columns.Nartist] = CleanUpText( res["Nartist"].c_str() );
			row[m_Columns.Nnumber] = res["Nnumber"];
			row[m_Columns.Nrating] = res["Nrating"];
			//std::wstring s;// = res["Nruling"].data();
			//res["Nruling"].to_string( s );
			//CleanUpText2( s );
			//row[m_Columns.Nruling] = s;
			
//			std::ofstream ofs( "testsql.txt", std::ios::binary );
//			if ( ofs.is_open() )
//			{
//				ofs << res["Ntype"].data();
//				ofs.close();
//			}
			
			row[m_Columns.Nruling] = CleanUpText( res["Nruling"].c_str() );
			row[m_Columns.Ncolor] = CleanUpText( res["Ncolor"].c_str() );
			row[m_Columns.Ngenerated_mana] = CleanUpText( res["Ngenerated_mana"].c_str() );
			row[m_Columns.Npricing_low] = CleanUpText( res["Npricing_low"].c_str() );
			row[m_Columns.Npricing_mid] = CleanUpText( res["Npricing_mid"].c_str() );
			row[m_Columns.Npricing_high] = CleanUpText( res["Npricing_high"].c_str() );
			row[m_Columns.Nback_id] = CleanUpText( res["Nback_id"].c_str() );
			row[m_Columns.Nwatermark] = CleanUpText( res["Nwatermark"].c_str() );
			row[m_Columns.Nprint_number] = CleanUpText( res["Nprint_number"].c_str() );
			row[m_Columns.Nis_original] = CleanUpText( res["Nis_original"].c_str() );
//			row[m_Columns.Nname_CN] = CleanUpText( res["Nname_CN"].c_str() );
//			row[m_Columns.Nname_TW] = CleanUpText( res["Nname_TW"].c_str() );
//			row[m_Columns.Nname_FR] = CleanUpText( res["Nname_FR"].c_str() );
//			row[m_Columns.Nname_DE] = CleanUpText( res["Nname_DE"].c_str() );
//			row[m_Columns.Nname_IT] = CleanUpText( res["Nname_IT"].c_str() );
//			row[m_Columns.Nname_JP] = CleanUpText( res["Nname_JP"].c_str() );
//			row[m_Columns.Nname_PT] = CleanUpText( res["Nname_PT"].c_str() );
//			row[m_Columns.Nname_RU] = CleanUpText( res["Nname_RU"].c_str() );
//			row[m_Columns.Nname_ES] = CleanUpText( res["Nname_ES"].c_str() );
//			row[m_Columns.Nname_KO] = CleanUpText( res["Nname_KO"].c_str() );
//			row[m_Columns.Ntype_CN] = CleanUpText( res["Ntype_CN"].c_str() );
//			row[m_Columns.Ntype_TW] = CleanUpText( res["Ntype_TW"].c_str() );
//			row[m_Columns.Ntype_FR] = CleanUpText( res["Ntype_FR"].c_str() );
//			row[m_Columns.Ntype_DE] = CleanUpText( res["Ntype_DE"].c_str() );
//			row[m_Columns.Ntype_IT] = CleanUpText( res["Ntype_IT"].c_str() );
//			row[m_Columns.Ntype_JP] = CleanUpText( res["Ntype_JP"].c_str() );
//			row[m_Columns.Ntype_PT] = CleanUpText( res["Ntype_PT"].c_str() );
//			row[m_Columns.Ntype_RU] = CleanUpText( res["Ntype_RU"].c_str() );
//			row[m_Columns.Ntype_ES] = CleanUpText( res["Ntype_ES"].c_str() );
//			row[m_Columns.Ntype_KO] = CleanUpText( res["Ntype_KO"].c_str() );
//			row[m_Columns.Nability_CN] = CleanUpText( res["Nability_CN"].c_str() );
//			row[m_Columns.Nability_TW] = CleanUpText( res["Nability_TW"].c_str() );
//			row[m_Columns.Nability_FR] = CleanUpText( res["Nability_FR"].c_str() );
//			row[m_Columns.Nability_DE] = CleanUpText( res["Nability_DE"].c_str() );
//			row[m_Columns.Nability_IT] = CleanUpText( res["Nability_IT"].c_str() );
//			row[m_Columns.Nability_JP] = CleanUpText( res["Nability_JP"].c_str() );
//			row[m_Columns.Nability_PT] = CleanUpText( res["Nability_PT"].c_str() );
//			row[m_Columns.Nability_RU] = CleanUpText( res["Nability_RU"].c_str() );
//			row[m_Columns.Nability_ES] = CleanUpText( res["Nability_ES"].c_str() );
//			row[m_Columns.Nability_KO] = CleanUpText( res["Nability_KO"].c_str() );
//			row[m_Columns.Nflavor_CN] = CleanUpText( res["Nflavor_CN"].c_str() );
//			row[m_Columns.Nflavor_TW] = CleanUpText( res["Nflavor_TW"].c_str() );
//			row[m_Columns.Nflavor_FR] = CleanUpText( res["Nflavor_FR"].c_str() );
//			row[m_Columns.Nflavor_DE] = CleanUpText( res["Nflavor_DE"].c_str() );
//			row[m_Columns.Nflavor_IT] = CleanUpText( res["Nflavor_IT"].c_str() );
//			row[m_Columns.Nflavor_JP] = CleanUpText( res["Nflavor_JP"].c_str() );
//			row[m_Columns.Nflavor_PT] = CleanUpText( res["Nflavor_PT"].c_str() );
//			row[m_Columns.Nflavor_RU] = CleanUpText( res["Nflavor_RU"].c_str() );
//			row[m_Columns.Nflavor_ES] = CleanUpText( res["Nflavor_ES"].c_str() );
//			row[m_Columns.Nflavor_KO] = CleanUpText( res["Nflavor_KO"].c_str() );
			row[m_Columns.Nlegality_Block] = CleanUpText( res["Nlegality_Block"].c_str() );
			row[m_Columns.Nlegality_Standard] = CleanUpText( res["Nlegality_Standard"].c_str() );
			row[m_Columns.Nlegality_Modern] = CleanUpText( res["Nlegality_Modern"].c_str() );
			row[m_Columns.Nlegality_Legacy] = CleanUpText( res["Nlegality_Legacy"].c_str() );
			row[m_Columns.Nlegality_Vintage] = CleanUpText( res["Nlegality_Vintage"].c_str() );
			row[m_Columns.Nlegality_Highlander] = CleanUpText( res["Nlegality_Highlander"].c_str() );
			row[m_Columns.Nlegality_French_Commander] = CleanUpText( res["Nlegality_French_Commander"].c_str() );
			row[m_Columns.Nlegality_Commander] = CleanUpText( res["Nlegality_Commander"].c_str() );
			row[m_Columns.Nlegality_Peasant] = CleanUpText( res["Nlegality_Peasant"].c_str() );
			row[m_Columns.Nlegality_Pauper] = CleanUpText( res["Nlegality_Pauper"].c_str() );
			
		}
		
//		if ( cno != NULL )
//			delete cno;
		
		std::cout << "k1" << std::endl;
		
		set_title( Glib::ustring::compose( "%1 - %2", get_title(), m_refTreeModel->get_n_columns() ) );
		
	}
	catch ( const mysqlpp::BadQuery& er )
	{
		// Handle any query errors
		std::cerr << "Query error: " << er.what() << std::endl;
	}
	catch ( const mysqlpp::BadConversion& er )
	{
		// Handle bad conversions
		std::cerr << "Conversion error: " << er.what() << std::endl << "\tretrieved data size: " << er.retrieved << ", actual size: " << er.actual_size << std::endl;
	}
	catch ( const mysqlpp::Exception& er )
	{
		// Catch-all for any other MySQL++ exceptions
		std::cerr << "Error: " << er.what() << std::endl;
	}
	
}

int main( int argc, char **argv )
{
	
//	std::string line;
//	std::ifstream myfile( "utf8data.txt" );
//	if ( myfile.is_open() )
//	{
//		while ( std::getline( myfile, line ) )
//		{
//			
//			uchardet_t ucd = uchardet_new();
//			uchardet_handle_data( ucd, line.c_str(), line.length() );
//			std::cout << uchardet_get_charset( ucd ) << std::endl;
//			uchardet_delete( ucd );
//			
//			std::cout << line << std::endl;
//			std::cout << "---" << std::endl;
//		}
//		myfile.close();
//	}
//	else
//		std::cout << "Unable to open file" << std::endl;
//	
//	return 0;
	
	try
	{
		
		Gtk::Main kit( argc, argv );
		
		MagicDatabase md;
		
		//Shows the window and returns when it is closed.
		kit.run( md );
		
	}
	catch ( const Glib::Error& ex )
	{
		
		std::cerr << "Exception caught: " << ex.what() << std::endl;
		
	}
	
	return 0;
	
}
