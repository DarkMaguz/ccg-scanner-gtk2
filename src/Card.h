/*
 * Card.h
 *
 *  Created on: 18/10/2014
 *      Author: magnus
 */

#ifndef CARD_H_
#define CARD_H_

#include <gtkmm.h>
#include <mysql++.h>
#include <vector>

class Card : public Gtk::HBox
{
	public:
		Card( const int& id );
		virtual ~Card();
		
	protected:
		//Child widgets:
		Gtk::VBox m_VBoxImage, m_VBoxSetsInfo;
		Gtk::Image m_ImageCard, m_ImageSetIcon;
		
//		Gtk::EventBox m_EventBoxMiddle;
		Gtk::TextView m_TextViewMiddle;
		Glib::RefPtr<Gtk::TextBuffer> m_refTextBufferMiddle;
		
		Gtk::EventBox m_EventBoxRight; // For background color.
		Gtk::HSeparator m_HSeparator;
		Gtk::Label m_LabelOtherVersions;
//		std::vector<Gtk::HBox> m_vecHBoxSetIcons;
//		Gtk::VBox m_VBoxSetIcons;
		Gtk::HBox m_HBoxSetIcons;
		std::vector<Gtk::Image *> m_vecImageSetIcons;
		
//		Gtk::TextView m_TextViewRight;
//		Glib::RefPtr<Gtk::TextBuffer> m_refTextBufferRight;
		
	private:
		void GetCardData( void );
		
		void InsertTextInTextBuffer( void );
		void InsertSymbolsInTextBuffer( void );
		
		bool GetOtherVersionsOfCard( void );
		
		int Nid;
		Glib::ustring Nname;
		Glib::ustring Nset;
		Glib::ustring Ntype;
		Glib::ustring Nrarity;
		Glib::ustring Nmanacost;
		int Nconverted_manacost;
		Glib::ustring Npower;
		Glib::ustring Ntoughness;
		Glib::ustring Nloyalty;
		Glib::ustring Nability;
		Glib::ustring Nflavor;
		Glib::ustring Nvariation;
		Glib::ustring Nartist;
		int Nnumber;
		double Nrating;
		Glib::ustring Nruling;
		Glib::ustring Ncolor;
		Glib::ustring Ngenerated_mana;
		Glib::ustring Npricing_low;
		Glib::ustring Npricing_mid;
		Glib::ustring Npricing_high;
		Glib::ustring Nback_id;
		Glib::ustring Nwatermark;
		Glib::ustring Nprint_number;
		Glib::ustring Nis_original;
		Glib::ustring Nname_CN;
		Glib::ustring Nname_TW;
		Glib::ustring Nname_FR;
		Glib::ustring Nname_DE;
		Glib::ustring Nname_IT;
		Glib::ustring Nname_JP;
		Glib::ustring Nname_PT;
		Glib::ustring Nname_RU;
		Glib::ustring Nname_ES;
		Glib::ustring Nname_KO;
		Glib::ustring Ntype_CN;
		Glib::ustring Ntype_TW;
		Glib::ustring Ntype_FR;
		Glib::ustring Ntype_DE;
		Glib::ustring Ntype_IT;
		Glib::ustring Ntype_JP;
		Glib::ustring Ntype_PT;
		Glib::ustring Ntype_RU;
		Glib::ustring Ntype_ES;
		Glib::ustring Ntype_KO;
		Glib::ustring Nability_CN;
		Glib::ustring Nability_TW;
		Glib::ustring Nability_FR;
		Glib::ustring Nability_DE;
		Glib::ustring Nability_IT;
		Glib::ustring Nability_JP;
		Glib::ustring Nability_PT;
		Glib::ustring Nability_RU;
		Glib::ustring Nability_ES;
		Glib::ustring Nability_KO;
		Glib::ustring Nflavor_CN;
		Glib::ustring Nflavor_TW;
		Glib::ustring Nflavor_FR;
		Glib::ustring Nflavor_DE;
		Glib::ustring Nflavor_IT;
		Glib::ustring Nflavor_JP;
		Glib::ustring Nflavor_PT;
		Glib::ustring Nflavor_RU;
		Glib::ustring Nflavor_ES;
		Glib::ustring Nflavor_KO;
		Glib::ustring Nlegality_Block;
		Glib::ustring Nlegality_Standard;
		Glib::ustring Nlegality_Modern;
		Glib::ustring Nlegality_Legacy;
		Glib::ustring Nlegality_Vintage;
		Glib::ustring Nlegality_Highlander;
		Glib::ustring Nlegality_French_Commander;
		Glib::ustring Nlegality_Commander;
		Glib::ustring Nlegality_Peasant;
		Glib::ustring Nlegality_Pauper;
};

#endif /* CARD_H_ */
