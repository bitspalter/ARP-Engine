//////////////////////////////////////////////////////////////////////////////////
// [ APP_Class_Header ]
//////////////////////////////////////////////////////////////////////////////////
//
// APP
//
// [::Last modi: 24.03.17 L.ey (µ~)::]
//
//
#ifndef _C_APP_H_
 #define _C_APP_H_

 #include <iostream>
 
 using namespace std;
 
 #include <gtkmm/window.h>
 #include <gtkmm/button.h>
 #include <gtkmm/comboboxtext.h>
 #include <gtkmm/layout.h>
 
 #include "C_Edit_IP.hpp"
 #include "C_Edit_MAC.hpp"
 
 #include "C_Net.hpp"

//////////////////////////////////////////////////////////////////////////////////
// CONSTANT
//////////////////////////////////////////////////////////////////////////////////
 
 const int C_APP_ERROR = 0x00;
 const int C_APP_READY = 0x01;
   
//////////////////////////////////////////////////////////////////////////////////
// STRUCT
//////////////////////////////////////////////////////////////////////////////////

 struct SButton {
    Gtk::Button send;
 };
 
 //////////////////////////////
 
 struct SLabel {
    Gtk::Label mac_eth_s;
    Gtk::Label mac_eth_d;
    Gtk::Label ip_s;
    Gtk::Label ip_d;
    Gtk::Label mac_s;
    Gtk::Label mac_d;
 };
 
 struct SCombo {
    Gtk::ComboBoxText interface;
    Gtk::ComboBoxText type;
    Gtk::ComboBoxText count;
    Gtk::ComboBoxText sleep;
 };
 
//////////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////////
 
 class C_App : public Gtk::Window {
  
    public:
      
       C_App();
       virtual ~C_App();

    protected:

       Gtk::Layout m_layout;

       SButton sbutton;
       SLabel  slabel;
       SCombo  scombo;
       
       C_Edit_IP EditIpD;
       C_Edit_IP EditIpS;
       
       C_Edit_MAC EditMacS;
       C_Edit_MAC EditMacD;

       C_Edit_MAC EditEthMacS;
       C_Edit_MAC EditEthMacD;

       ////////////////////////
      
       //Signal handlers:
       void on_button_send();
       bool on_configure_changed(GdkEventConfigure* configure_event);
      
       ////////////////////////
      
       C_Net CNet;
 };

#endif // _C_APP_H_