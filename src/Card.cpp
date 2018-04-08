/*
 * Card.cpp
 *
 *  Created on: 18/10/2014
 *      Author: magnus
 */

#include "Card.h"

#include <glibmm.h>
#include <mysql++.h>

//bool replace( Glib::ustring& str, const Glib::ustring& from, const Glib::ustring& to )
//{
//	
//	size_t start_pos = str.find( from );
//	
//	if ( start_pos == Glib::ustring::npos )
//		return false;
//	
//	str.replace( start_pos, from.length(), to );
//	
//	return true;
//	
//}
//
//void CleanUpText( Glib::ustring& text )
//{
//	
//	const Glib::ustring targets[] = { "#_", "_#", "\xa3", "\x97", "\x95" };
//	const Glib::ustring replacements[] = { "", "", "\n", "-", "*" };
//	
//	for ( int t = 0; t < 5; t++ )
//		while ( replace( text, targets[t], replacements[t] ) ) { }
//	
//}

Card::Card( const int& id ) :
	m_refTextBufferMiddle( Gtk::TextBuffer::create() ),
//	m_refTextBufferRight( Gtk::TextBuffer::create() ),
	m_LabelOtherVersions( "Other versions" ),
	Nid( id )
{
	
	set_border_width( 10 );
	
	GetCardData();
	
	Glib::RefPtr<Gdk::Pixbuf> pixbuf, pixbuf_small;// = Gdk::Pixbuf::create;
	
	try
	{
		pixbuf = Gdk::Pixbuf::create_from_file( Glib::ustring::compose( "../pics/magic_cards/%1/%2.full.jpg", Nset, Nname ) );
		pixbuf_small = Gdk::Pixbuf::create_from_file( Glib::ustring::compose( "../pics/magic_cards/%1/%2.full.jpg", Nset, Nname ), pixbuf->get_width() / 2, pixbuf->get_height() / 2 );
		//pixbuf->scale( pixbuf_small, 0, 0, pixbuf->get_width() / 4, pixbuf->get_height() / 4, 0, 0, 0, 0, Gdk::INTERP_HYPER );
	}
	catch ( const Glib::FileError& e )
	{
		std::cerr << __FILE__ << ":" << __LINE__ << "\n\tFileError: " << e.what() << std::endl;
	}
	catch ( const Gdk::PixbufError& e )
	{
		std::cerr << __FILE__ << ":" << __LINE__ << "\n\tPixbufError: " << e.what() << std::endl;
	}
	
	//m_Image.set( Glib::ustring::compose( "../pics/magic_cards/%1/%2.full.jpg", set_code, name ) );
	m_ImageCard.set( pixbuf_small );
	
	m_TextViewMiddle.set_buffer( m_refTextBufferMiddle );
	m_TextViewMiddle.set_editable( false );
	m_TextViewMiddle.set_can_focus( false );
	m_TextViewMiddle.set_border_width( 5 );
	m_TextViewMiddle.set_sensitive( false );
	m_TextViewMiddle.set_wrap_mode( Gtk::WRAP_WORD );
	m_TextViewMiddle.set_size_request( 500 );
	m_TextViewMiddle.modify_bg( Gtk::STATE_INSENSITIVE , Gdk::Color( "gray" ) );
	m_TextViewMiddle.modify_base( Gtk::STATE_INSENSITIVE , Gdk::Color( "gray" ) );
	
	InsertTextInTextBuffer();
	
	InsertSymbolsInTextBuffer();
	
	Glib::RefPtr<Gdk::Pixbuf> set_icon = Gdk::Pixbuf::create_from_file( Glib::ustring::compose( "../pics/icons/sets/small/%1-%2.png", Nset.c_str(), Nrarity.c_str() ) );
	m_ImageSetIcon.set( set_icon );
	
	m_EventBoxRight.modify_bg( Gtk::STATE_NORMAL , Gdk::Color("gray") );
	m_EventBoxRight.add( m_VBoxSetsInfo );
	
	m_VBoxSetsInfo.pack_start( m_ImageSetIcon, Gtk::PACK_SHRINK );
	
	if ( GetOtherVersionsOfCard() )
	{
		m_HSeparator.set_size_request( 250, 2 );
		m_VBoxSetsInfo.pack_start( m_HSeparator, Gtk::PACK_SHRINK );
		m_VBoxSetsInfo.pack_start( m_LabelOtherVersions, Gtk::PACK_SHRINK );
		
		for ( std::vector<Gtk::Image *>::iterator it = m_vecImageSetIcons.begin(); it != m_vecImageSetIcons.end(); it++ )
		{
			m_HBoxSetIcons.pack_start( **it, Gtk::PACK_SHRINK );
		}
		
		m_VBoxSetsInfo.pack_start( m_HBoxSetIcons, Gtk::PACK_SHRINK );
		
	}
	
//	m_TextViewRight.set_buffer( m_refTextBufferRight );
//	m_TextViewRight.set_editable( false );
//	m_TextViewRight.set_can_focus( false );
//	m_TextViewRight.set_border_width( 5 );
//	m_TextViewRight.set_sensitive( false );
	
	// We pack m_Image into m_VBox to get it to stay at top.
	m_VBoxImage.pack_start( m_ImageCard, Gtk::PACK_SHRINK );
	
	pack_start( m_VBoxImage, Gtk::PACK_SHRINK );
	pack_start( m_TextViewMiddle, Gtk::PACK_SHRINK );
	pack_start( m_EventBoxRight, Gtk::PACK_SHRINK );
//	pack_start( m_TextViewRight, Gtk::PACK_SHRINK );
	
}

Card::~Card()
{
	
	for ( std::vector<Gtk::Image *>::iterator it = m_vecImageSetIcons.begin(); it != m_vecImageSetIcons.end(); it++ )
		delete *it;
	
}

void Card::GetCardData( void )
{
	
	try
	{
		
		mysqlpp::Connection conn( false );
		if ( !conn.connect( "magic_cards", "localhost", USERNAME, PASSWORD ) )
		{
			std::cerr << "DB connection failed: " << conn.error() << std::endl;
			return;
		}
		
		mysqlpp::Query query = conn.query();
		query << "SET NAMES 'utf8'";
		query.execute();
		
		query << "SELECT * FROM Ncards WHERE Nid = " << Nid;
		mysqlpp::StoreQueryResult res = query.store();
		if ( !res )
		{
			std::cerr << __FILE__ << ":" << __LINE__ << "\n\tFailed to get item list: " << query.error() << std::endl;
			return;
		}
		else if ( res.empty() )
		{
			std::cerr << __FILE__ << ":" << __LINE__ << "\n\tResult set \"" << query.str() << "\" is empty: " << query.error() << std::endl;
			return;
		}
		else if ( res.size() > 1 )
		{
			std::cerr << __FILE__ << ":" << __LINE__ << "\n\tWarning ID NOT UNIQE!: Result set \"" << query.str() << "\" is larger than 1: " << res.size() << std::endl;
		}
		
		Nname = res[0]["Nname"].c_str();
		Nset = res[0]["Nset"].c_str();
		Ntype = res[0]["Ntype"].c_str();
		Nrarity = res[0]["Nrarity"].c_str();
		Nmanacost = res[0]["Nmanacost"].c_str();
		Nconverted_manacost = res[0]["Nconverted_manacost"];
		Npower = res[0]["Npower"].c_str();
		Ntoughness = res[0]["Ntoughness"].c_str();
		Nloyalty = res[0]["Nloyalty"].c_str();
		Nability = res[0]["Nability"].c_str();
		Nflavor = res[0]["Nflavor"].c_str();
		Nvariation = res[0]["Nvariation"].c_str();
		Nartist = res[0]["Nartist"].c_str();
		Nnumber = res[0]["Nnumber"];
		Nrating = res[0]["Nrating"];
		Nruling = res[0]["Nruling"].c_str();
		Ncolor = res[0]["Ncolor"].c_str();
		Ngenerated_mana = res[0]["Ngenerated_mana"].c_str();
		Npricing_low = res[0]["Npricing_low"].c_str();
		Npricing_mid = res[0]["Npricing_mid"].c_str();
		Npricing_high = res[0]["Npricing_high"].c_str();
		Nback_id = res[0]["Nback_id"].c_str();
		Nwatermark = res[0]["Nwatermark"].c_str();
		Nprint_number = res[0]["Nprint_number"].c_str();
		Nis_original = res[0]["Nis_original"].c_str();
		Nname_CN = res[0]["Nname_CN"].c_str();
		Nname_TW = res[0]["Nname_TW"].c_str();
		Nname_FR = res[0]["Nname_FR"].c_str();
		Nname_DE = res[0]["Nname_DE"].c_str();
		Nname_IT = res[0]["Nname_IT"].c_str();
		Nname_JP = res[0]["Nname_JP"].c_str();
		Nname_PT = res[0]["Nname_PT"].c_str();
		Nname_RU = res[0]["Nname_RU"].c_str();
		Nname_ES = res[0]["Nname_ES"].c_str();
		Nname_KO = res[0]["Nname_KO"].c_str();
		Ntype_CN = res[0]["Ntype_CN"].c_str();
		Ntype_TW = res[0]["Ntype_TW"].c_str();
		Ntype_FR = res[0]["Ntype_FR"].c_str();
		Ntype_DE = res[0]["Ntype_DE"].c_str();
		Ntype_IT = res[0]["Ntype_IT"].c_str();
		Ntype_JP = res[0]["Ntype_JP"].c_str();
		Ntype_PT = res[0]["Ntype_PT"].c_str();
		Ntype_RU = res[0]["Ntype_RU"].c_str();
		Ntype_ES = res[0]["Ntype_ES"].c_str();
		Ntype_KO = res[0]["Ntype_KO"].c_str();
		Nability_CN = res[0]["Nability_CN"].c_str();
		Nability_TW = res[0]["Nability_TW"].c_str();
		Nability_FR = res[0]["Nability_FR"].c_str();
		Nability_DE = res[0]["Nability_DE"].c_str();
		Nability_IT = res[0]["Nability_IT"].c_str();
		Nability_JP = res[0]["Nability_JP"].c_str();
		Nability_PT = res[0]["Nability_PT"].c_str();
		Nability_RU = res[0]["Nability_RU"].c_str();
		Nability_ES = res[0]["Nability_ES"].c_str();
		Nability_KO = res[0]["Nability_KO"].c_str();
		Nflavor_CN = res[0]["Nflavor_CN"].c_str();
		Nflavor_TW = res[0]["Nflavor_TW"].c_str();
		Nflavor_FR = res[0]["Nflavor_FR"].c_str();
		Nflavor_DE = res[0]["Nflavor_DE"].c_str();
		Nflavor_IT = res[0]["Nflavor_IT"].c_str();
		Nflavor_JP = res[0]["Nflavor_JP"].c_str();
		Nflavor_PT = res[0]["Nflavor_PT"].c_str();
		Nflavor_RU = res[0]["Nflavor_RU"].c_str();
		Nflavor_ES = res[0]["Nflavor_ES"].c_str();
		Nflavor_KO = res[0]["Nflavor_KO"].c_str();
		Nlegality_Block = res[0]["Nlegality_Block"].c_str();
		Nlegality_Standard = res[0]["Nlegality_Standard"].c_str();
		Nlegality_Modern = res[0]["Nlegality_Modern"].c_str();
		Nlegality_Legacy = res[0]["Nlegality_Legacy"].c_str();
		Nlegality_Vintage = res[0]["Nlegality_Vintage"].c_str();
		Nlegality_Highlander = res[0]["Nlegality_Highlander"].c_str();
		Nlegality_French_Commander = res[0]["Nlegality_French_Commander"].c_str();
		Nlegality_Commander = res[0]["Nlegality_Commander"].c_str();
		Nlegality_Peasant = res[0]["Nlegality_Peasant"].c_str();
		Nlegality_Pauper = res[0]["Nlegality_Pauper"].c_str();
		
	}
	catch ( const mysqlpp::BadQuery& e )
	{
		// Handle any query errors
		std::cerr << __FILE__ << ":" << __LINE__ << "\n\tQuery error: " << e.what() << std::endl;
	}
	catch ( const mysqlpp::BadConversion& e )
	{
		// Handle bad conversions
		std::cerr << __FILE__ << ":" << __LINE__ << "\n\tConversion error: " << e.what() << std::endl << "\tretrieved data size: " << e.retrieved << ", actual size: " << e.actual_size << std::endl;
	}
	catch ( const mysqlpp::Exception& e )
	{
		// Catch-all for any other MySQL++ exceptions
		std::cerr << __FILE__ << ":" << __LINE__ << "\n\tError: " << e.what() << std::endl;
	}
	
}


void Card::InsertTextInTextBuffer( void )
{
	
	Gtk::TextBuffer::iterator it = m_refTextBufferMiddle->begin();
	Glib::RefPtr<Gtk::TextBuffer::Tag> tag = Gtk::TextBuffer::Tag::create();
	tag->property_weight() = PANGO_WEIGHT_BOLD;
	m_refTextBufferMiddle->get_tag_table()->add( tag );
	it = m_refTextBufferMiddle->insert_with_tag( it, Nname, tag );
	it = m_refTextBufferMiddle->insert( it, " " );
	it = m_refTextBufferMiddle->insert( it, Nmanacost );
//	it = m_refTextBufferMiddle->insert( it, " (" );
//	it = m_refTextBufferMiddle->insert( it, Nconverted_manacost );
//	it = m_refTextBufferMiddle->insert( it, ")\n" );
	it = m_refTextBufferMiddle->insert( it, Glib::ustring::compose( " (%1)\n ", Nconverted_manacost ) );
	it = m_refTextBufferMiddle->insert( it, Ntype );
	if ( !Npower.empty() || !Ntoughness.empty() )
	{
		it = m_refTextBufferMiddle->insert( it, " (" );
		it = m_refTextBufferMiddle->insert( it, Npower );
		it = m_refTextBufferMiddle->insert( it, "/" );
		it = m_refTextBufferMiddle->insert( it, Ntoughness );
		it = m_refTextBufferMiddle->insert( it, ")" );
	}
	it = m_refTextBufferMiddle->insert( it, "\n" );
	it = m_refTextBufferMiddle->insert( it, Nability );
	
}

void Card::InsertSymbolsInTextBuffer( void )
{
	
	Glib::ustring tmp = m_refTextBufferMiddle->get_text( true );
	size_t pos = tmp.find( '{' );
	// We need to add one to position for each inserted icon.
	int loopCount = 0;
	while ( pos != Glib::ustring::npos )
	{
		
		Glib::ustring symbol = m_refTextBufferMiddle->get_slice( m_refTextBufferMiddle->get_iter_at_offset( pos + loopCount + 1 ), m_refTextBufferMiddle->get_iter_at_offset( pos + 3 + loopCount - 1 ) );
		
		Gtk::TextBuffer::iterator it = m_refTextBufferMiddle->erase( m_refTextBufferMiddle->get_iter_at_offset( pos + loopCount ), m_refTextBufferMiddle->get_iter_at_offset( pos + 3 + loopCount ) );
		
		try
		{
			Glib::RefPtr<Gdk::Pixbuf> icon = Gdk::Pixbuf::create_from_file( Glib::ustring::compose( "../pics/icons/small/%1.gif", symbol.c_str() ) );
			m_refTextBufferMiddle->insert_pixbuf( it, icon );
		}
		catch ( const Glib::FileError& e )
		{
			std::cerr << __FILE__ << ":" << __LINE__ << "\n\tFileError: " << e.what() << std::endl;
//			std::cout << pos << std::endl;
//			m_refTextBufferMiddle->insert( it, "___" );
//			std::cout << m_refTextBufferMiddle->get_text( true ) << std::endl;
//			std::cout << "-----------" << std::endl;
//			std::cout << Nability << std::endl;
//			exit( EXIT_FAILURE );
		}
		catch ( const Gdk::PixbufError& e )
		{
			std::cerr << __FILE__ << ":" << __LINE__ << "\n\tPixbufError: " << e.what() << std::endl;
		}
		
		tmp = m_refTextBufferMiddle->get_text( true );
		pos = tmp.find( '{' );
		
		loopCount++;
		
	}
	
}

bool Card::GetOtherVersionsOfCard( void )
{
	
	try
	{
		
		mysqlpp::Connection conn( false );
		if ( !conn.connect( "magic_cards", "localhost", USERNAME, PASSWORD ) )
		{
			std::cerr << __FILE__ << ":" << __LINE__ << "\n\tDB connection failed: " << conn.error() << std::endl;
			return false;
		}
		
		mysqlpp::Query query = conn.query();
		query << "SET NAMES 'utf8'";
		query.execute();
		
		query << "SELECT * FROM Ncards WHERE Nname = '" << Nname << "'";
		mysqlpp::StoreQueryResult res = query.store();
		if ( !res )
		{
			std::cerr << __FILE__ << ":" << __LINE__ << "\n\tFailed to get item list: " << query.error() << std::endl;
			return false;
		}
		else if ( res.empty() )
		{
			return false;
		}
		
		try
		{
			
			for ( size_t i = 0; i < res.num_rows(); i++ )
			{
				
				Glib::RefPtr<Gdk::Pixbuf> set_icon = Gdk::Pixbuf::create_from_file( Glib::ustring::compose( "../pics/icons/sets/small/%1-%2.png", res[i]["Nset"].c_str(), res[i]["Nrarity"].c_str() ) );
				Gtk::Image *image = new Gtk::Image;
				image->set( set_icon );
				
				m_vecImageSetIcons.push_back( image );
				
			}
			
		}
		catch ( const Glib::FileError& e )
		{
			std::cerr << __FILE__ << ":" << __LINE__ << "\n\tFileError: " << e.what() << std::endl;
		}
		catch ( const Gdk::PixbufError& e )
		{
			std::cerr << __FILE__ << ":" << __LINE__ << "\n\tPixbufError: " << e.what() << std::endl;
		}
		
	}
	catch ( const mysqlpp::BadQuery& e )
	{
		// Handle any query errors
		std::cerr << __FILE__ << ":" << __LINE__ << "\n\tQuery error: " << e.what() << std::endl;
		return false;
	}
	catch ( const mysqlpp::BadConversion& er )
	{
		// Handle bad conversions
		std::cerr << __FILE__ << ":" << __LINE__ << "\n\tConversion error: " << er.what() << std::endl << "\tretrieved data size: " << er.retrieved << ", actual size: " << er.actual_size << std::endl;
		return false;
	}
	catch ( const mysqlpp::Exception& er )
	{
		// Catch-all for any other MySQL++ exceptions
		std::cerr << __FILE__ << ":" << __LINE__ << "\n\tError: " << er.what() << std::endl;
		return false;
	}
	
	return true;
	
}
