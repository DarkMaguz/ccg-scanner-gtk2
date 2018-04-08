/*
 * Picture.h
 *
 *  Created on: 14/10/2014
 *      Author: magnus
 */

#ifndef PICTURE_H_
#define PICTURE_H_

#include <gtkmm.h>
#include <string>

class Picture : public Gtk::DrawingArea
{
	public:
		Picture( const Glib::RefPtr<Gdk::Pixbuf>& pixBuf );
		Picture( const std::string& pathToPicture );
		virtual ~Picture();
		
	protected:
		//Override default signal handler:
		virtual bool on_draw( const Cairo::RefPtr<Cairo::Context>& cr );
		virtual bool on_expose_event( GdkEventExpose* ev );
		
		Glib::RefPtr<Gdk::Pixbuf> m_refPixbuf;
		Glib::RefPtr<Gdk::Pixbuf> m_refPixbufLarge;
		//Glib::RefPtr<Gdk::Pixbuf> m_refPixbufSmall;
		
};

#endif /* PICTURE_H_ */
