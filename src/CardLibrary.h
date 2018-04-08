/*
 * CardLibrary.h
 *
 *  Created on: 18/10/2014
 *      Author: magnus
 */

#ifndef CARDLIBRARY_H_
#define CARDLIBRARY_H_

#include "Card.h"

#include <gtkmm.h>
#include <vector>

class CardLibrary : public Gtk::VBox
{
	public:
		CardLibrary();
		virtual ~CardLibrary();
		
	protected:
		// Signal handlers. 
		void onCardClicked( void );
		
		//Child widgets:
		Gtk::EventBox m_EventBox;
		Gtk::ScrolledWindow m_ScrolledWindow;
		Gtk::VBox m_VBox;
		
		//std::vector<Card> m_Cards;
		Card card1;
		Card card2;
		Card card3;
		Card card4;
		Card card5;
		
		void FillTreeViewsModel( void );
		
};

#endif /* CARDLIBRARY_H_ */
