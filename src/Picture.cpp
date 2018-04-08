/*
 * Picture.cpp
 *
 *  Created on: 14/10/2014
 *      Author: magnus
 */

#include "Picture.h"

#include <iostream>

Picture::Picture( const Glib::RefPtr<Gdk::Pixbuf>& pixBuf ) :
	m_refPixbuf( pixBuf ),
	m_refPixbufLarge( pixBuf )
{
	
	//m_refPixbuf->scale( m_refPixbufSmall, 0, 0, m_refPixbuf->get_width() / 2, m_refPixbuf->get_height() / 2, 0, 0, 0, 0, Gdk::INTERP_HYPER );
	
	if ( m_refPixbuf )
		set_size_request( m_refPixbuf->get_width(), m_refPixbuf->get_height() );
	
}

Picture::Picture( const std::string& pathToPicture )
{
	
	try
	{
		m_refPixbuf = Gdk::Pixbuf::create_from_file( pathToPicture );
		m_refPixbufLarge = m_refPixbuf;
	}
	catch ( const Glib::FileError& ex )
	{
		std::cerr << "FileError: " << ex.what() << std::endl;
	}
	catch ( const Gdk::PixbufError& ex )
	{
		std::cerr << "PixbufError: " << ex.what() << std::endl;
	}
	
	//m_refPixbuf->scale( m_refPixbufSmall, 0, 0, m_refPixbuf->get_width() / 2, m_refPixbuf->get_height() / 2, 0, 0, 0, 0, Gdk::INTERP_HYPER );
	
	if ( m_refPixbuf )
		set_size_request( m_refPixbuf->get_width(), m_refPixbuf->get_height() );
	
}

Picture::~Picture()
{
	
}

bool Picture::on_draw( const Cairo::RefPtr<Cairo::Context>& cr )
{
	
	if ( !m_refPixbuf )
		return false;
	
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	
	// Draw the image in the middle of the drawing area, or (if the image is
	// larger than the drawing area) draw the middle part of the image.
	Gdk::Cairo::set_source_pixbuf( cr, m_refPixbuf, ( width - m_refPixbuf->get_width() ) / 2, ( height - m_refPixbuf->get_height() ) / 2 );
	cr->paint();
	
	return true;
	
}

bool Picture::on_expose_event( GdkEventExpose* ev )
{
	
	if ( !m_refPixbuf )
		return false;
	
	m_refPixbuf->render_to_drawable( get_window(), get_style()->get_black_gc(), 0, 0, 0, 0, m_refPixbuf->get_width(), m_refPixbuf->get_height(), Gdk::RGB_DITHER_MAX, 0, 0 );
	
	return true;
	
}
