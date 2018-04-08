/*
 * MagicDatabase.h
 *
 *  Created on: 19/10/2014
 *      Author: magnus
 */

#ifndef MAGICDATABASE_H_
#define MAGICDATABASE_H_

#include <gtkmm.h>
#include <string>

class MagicDatabase: public Gtk::Window
{
	public:
		MagicDatabase();
		virtual ~MagicDatabase();
		
	protected:
		//Signal handlers:
		void on_button_quit();
		
		//Tree model columns:
		class ModelColumns: public Gtk::TreeModel::ColumnRecord
		{
			public:
				
				ModelColumns()
				{
					add( Nid );
					add( Nname );
					add( Nset );
					add( Ntype );
					add( Nrarity );
					add( Nmanacost );
					add( Nconverted_manacost );
					add( Npower );
					add( Ntoughness );
					add( Nloyalty );
					add( Nability );
					add( Nflavor );
					add( Nvariation );
					add( Nartist );
					add( Nnumber );
					add( Nrating );
					add( Nruling );
					add( Ncolor );
					add( Ngenerated_mana );
					add( Npricing_low );
					add( Npricing_mid );
					add( Npricing_high );
					add( Nback_id );
					add( Nwatermark );
					add( Nprint_number );
					add( Nis_original );
					/*add( Nname_CN );
					add( Nname_TW );
					add( Nname_FR );
					add( Nname_DE );
					add( Nname_IT );
					add( Nname_JP );
					add( Nname_PT );
					add( Nname_RU );
					add( Nname_ES );
					add( Nname_KO );
					add( Ntype_CN );
					add( Ntype_TW );
					add( Ntype_FR );
					add( Ntype_DE );
					add( Ntype_IT );
					add( Ntype_JP );
					add( Ntype_PT );
					add( Ntype_RU );
					add( Ntype_ES );
					add( Ntype_KO );
					add( Nability_CN );
					add( Nability_TW );
					add( Nability_FR );
					add( Nability_DE );
					add( Nability_IT );
					add( Nability_JP );
					add( Nability_PT );
					add( Nability_RU );
					add( Nability_ES );
					add( Nability_KO );
					add( Nflavor_CN );
					add( Nflavor_TW );
					add( Nflavor_FR );
					add( Nflavor_DE );
					add( Nflavor_IT );
					add( Nflavor_JP );
					add( Nflavor_PT );
					add( Nflavor_RU );
					add( Nflavor_ES );
					add( Nflavor_KO );*/
					add( Nlegality_Block );
					add( Nlegality_Standard );
					add( Nlegality_Modern );
					add( Nlegality_Legacy );
					add( Nlegality_Vintage );
					add( Nlegality_Highlander );
					add( Nlegality_French_Commander );
					add( Nlegality_Commander );
					add( Nlegality_Peasant );
					add( Nlegality_Pauper );
				}
				
				Gtk::TreeModelColumn<int> Nid;
				Gtk::TreeModelColumn<Glib::ustring> Nname;
				Gtk::TreeModelColumn<Glib::ustring> Nset;
				Gtk::TreeModelColumn<Glib::ustring> Ntype;
				Gtk::TreeModelColumn<Glib::ustring> Nrarity;
				Gtk::TreeModelColumn<Glib::ustring> Nmanacost;
				Gtk::TreeModelColumn<int> Nconverted_manacost;
				Gtk::TreeModelColumn<Glib::ustring> Npower;
				Gtk::TreeModelColumn<Glib::ustring> Ntoughness;
				Gtk::TreeModelColumn<Glib::ustring> Nloyalty;
				Gtk::TreeModelColumn<Glib::ustring> Nability;
				Gtk::TreeModelColumn<Glib::ustring> Nflavor;
				Gtk::TreeModelColumn<Glib::ustring> Nvariation;
				Gtk::TreeModelColumn<Glib::ustring> Nartist;
				Gtk::TreeModelColumn<int> Nnumber;
				Gtk::TreeModelColumn<double> Nrating;
				Gtk::TreeModelColumn<Glib::ustring> Nruling;
				Gtk::TreeModelColumn<Glib::ustring> Ncolor;
				Gtk::TreeModelColumn<Glib::ustring> Ngenerated_mana;
				Gtk::TreeModelColumn<Glib::ustring> Npricing_low;
				Gtk::TreeModelColumn<Glib::ustring> Npricing_mid;
				Gtk::TreeModelColumn<Glib::ustring> Npricing_high;
				Gtk::TreeModelColumn<Glib::ustring> Nback_id;
				Gtk::TreeModelColumn<Glib::ustring> Nwatermark;
				Gtk::TreeModelColumn<Glib::ustring> Nprint_number;
				Gtk::TreeModelColumn<Glib::ustring> Nis_original;
//				Gtk::TreeModelColumn<Glib::ustring> Nname_CN;
//				Gtk::TreeModelColumn<Glib::ustring> Nname_TW;
//				Gtk::TreeModelColumn<Glib::ustring> Nname_FR;
//				Gtk::TreeModelColumn<Glib::ustring> Nname_DE;
//				Gtk::TreeModelColumn<Glib::ustring> Nname_IT;
//				Gtk::TreeModelColumn<Glib::ustring> Nname_JP;
//				Gtk::TreeModelColumn<Glib::ustring> Nname_PT;
//				Gtk::TreeModelColumn<Glib::ustring> Nname_RU;
//				Gtk::TreeModelColumn<Glib::ustring> Nname_ES;
//				Gtk::TreeModelColumn<Glib::ustring> Nname_KO;
//				Gtk::TreeModelColumn<Glib::ustring> Ntype_CN;
//				Gtk::TreeModelColumn<Glib::ustring> Ntype_TW;
//				Gtk::TreeModelColumn<Glib::ustring> Ntype_FR;
//				Gtk::TreeModelColumn<Glib::ustring> Ntype_DE;
//				Gtk::TreeModelColumn<Glib::ustring> Ntype_IT;
//				Gtk::TreeModelColumn<Glib::ustring> Ntype_JP;
//				Gtk::TreeModelColumn<Glib::ustring> Ntype_PT;
//				Gtk::TreeModelColumn<Glib::ustring> Ntype_RU;
//				Gtk::TreeModelColumn<Glib::ustring> Ntype_ES;
//				Gtk::TreeModelColumn<Glib::ustring> Ntype_KO;
//				Gtk::TreeModelColumn<Glib::ustring> Nability_CN;
//				Gtk::TreeModelColumn<Glib::ustring> Nability_TW;
//				Gtk::TreeModelColumn<Glib::ustring> Nability_FR;
//				Gtk::TreeModelColumn<Glib::ustring> Nability_DE;
//				Gtk::TreeModelColumn<Glib::ustring> Nability_IT;
//				Gtk::TreeModelColumn<Glib::ustring> Nability_JP;
//				Gtk::TreeModelColumn<Glib::ustring> Nability_PT;
//				Gtk::TreeModelColumn<Glib::ustring> Nability_RU;
//				Gtk::TreeModelColumn<Glib::ustring> Nability_ES;
//				Gtk::TreeModelColumn<Glib::ustring> Nability_KO;
//				Gtk::TreeModelColumn<Glib::ustring> Nflavor_CN;
//				Gtk::TreeModelColumn<Glib::ustring> Nflavor_TW;
//				Gtk::TreeModelColumn<Glib::ustring> Nflavor_FR;
//				Gtk::TreeModelColumn<Glib::ustring> Nflavor_DE;
//				Gtk::TreeModelColumn<Glib::ustring> Nflavor_IT;
//				Gtk::TreeModelColumn<Glib::ustring> Nflavor_JP;
//				Gtk::TreeModelColumn<Glib::ustring> Nflavor_PT;
//				Gtk::TreeModelColumn<Glib::ustring> Nflavor_RU;
//				Gtk::TreeModelColumn<Glib::ustring> Nflavor_ES;
//				Gtk::TreeModelColumn<Glib::ustring> Nflavor_KO;
				Gtk::TreeModelColumn<Glib::ustring> Nlegality_Block;
				Gtk::TreeModelColumn<Glib::ustring> Nlegality_Standard;
				Gtk::TreeModelColumn<Glib::ustring> Nlegality_Modern;
				Gtk::TreeModelColumn<Glib::ustring> Nlegality_Legacy;
				Gtk::TreeModelColumn<Glib::ustring> Nlegality_Vintage;
				Gtk::TreeModelColumn<Glib::ustring> Nlegality_Highlander;
				Gtk::TreeModelColumn<Glib::ustring> Nlegality_French_Commander;
				Gtk::TreeModelColumn<Glib::ustring> Nlegality_Commander;
				Gtk::TreeModelColumn<Glib::ustring> Nlegality_Peasant;
				Gtk::TreeModelColumn<Glib::ustring> Nlegality_Pauper;
		};
		
		ModelColumns m_Columns;
		
		//Child widgets:
		Gtk::VBox m_VBox;
		//Gtk::Label m_Label;
		
		Gtk::ScrolledWindow m_ScrolledWindow;
		Gtk::TreeView m_TreeView;
		Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
		Gtk::HButtonBox m_ButtonBox;
		Gtk::Button m_Button_Quit;
		
	private:
		void FillTreeViewsModel( void );
		Glib::ustring CleanUpText( const char *text );
		
//		std::vector<char *> m_CharSets;
		
};

#endif /* MAGICDATABASE_H_ */
