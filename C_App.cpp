//////////////////////////////////////////////////////////////////////////////////
// [ APP_Class_Source ]
//////////////////////////////////////////////////////////////////////////////////

#include "C_App.hpp"

//////////////////////////////////////////////////////////////////////////////////
// [ Konstructor ]  
//////////////////////////////////////////////////////////////////////////////////
C_App::C_App(){
  
   this->set_title("ARP - ENGINE");
   this->resize(535, 220);

   /////////////////////////////////////////////
   
   if(CNet.start() != C_NET_READY){
      cout << "ERROR: CNet.start" << endl;
      return;
   }
   
   /////////////////////////////////////////////
   // signal
   CNet.CNRaw.signal_data().connect(sigc::mem_fun(CNet, &C_Net::on_arp_data));
   
   /////////////////////////////////////////////
   //Fill the interface combo:
   const vector<S_Net_Interface>* pDA_Interface = CNet.CNInterface.get_pDA_Interface();

   for(auto iface : *pDA_Interface) scombo.interface.append(iface.ps_Name);

   /////////////////////////////////////////////
   
   scombo.interface.set_active(CNet.CNInterface.get_First_Active());
   scombo.interface.set_size_request(84, 30); 
   
   ////////////////
   scombo.type.set_size_request(126, 30);
   scombo.type.append("Request");
   scombo.type.append("Response");
   scombo.type.set_active(0);
   
   ////////////////
   scombo.count.set_size_request(94, 30);
   scombo.count.append("1 Packet");
   scombo.count.append("10 Packets");
   scombo.count.append("100 Packets");
   scombo.count.append("1000 Packets");
   scombo.count.set_active(0);
   
   ////////////////
   scombo.sleep.set_size_request(94, 30);
   scombo.sleep.append("1 ms");
   scombo.sleep.append("10 ms");
   scombo.sleep.append("100 ms");
   scombo.sleep.append("1000 ms");
   scombo.sleep.set_active(0);
   
   //////////////////////////////////////////////////////////////
   // Button
   sbutton.send.set_label("send");
   sbutton.send.set_size_request(84, 30);
   sbutton.send.signal_clicked().connect(sigc::mem_fun(*this, &C_App::on_button_send));
   
   ////////////////
   // label
   
   Pango::FontDescription fdsc("Courier New 12"); 
   
   slabel.mac_eth_s.set_label("MAC_ETH_S");
   slabel.mac_eth_s.set_alignment(0.0f, 0.5f);
   slabel.mac_eth_s.set_size_request(234, 30);
   slabel.mac_eth_s.override_font(fdsc);
   ////////////////
   slabel.mac_eth_d.set_label("MAC_ETH_D");
   slabel.mac_eth_d.set_alignment(0.0f, 0.5f);
   slabel.mac_eth_d.set_size_request(234, 30);
   slabel.mac_eth_d.override_font(fdsc);
   ////////////////
   slabel.ip_s.set_label("IP_S");
   slabel.ip_s.set_alignment(0.0f, 0.5f);
   slabel.ip_s.set_size_request(168, 30);
   slabel.ip_s.override_font(fdsc);
   ////////////////
   slabel.ip_d.set_label("IP_D");
   slabel.ip_d.set_alignment(0.0f, 0.5f);
   slabel.ip_d.set_size_request(168, 30);
   slabel.ip_d.override_font(fdsc);
   ////////////////
   slabel.mac_s.set_label("MAC_S");
   slabel.mac_s.set_alignment(0.0f, 0.5f);
   slabel.mac_s.set_size_request(252, 30);
   slabel.mac_s.override_font(fdsc);
   ////////////////
   slabel.mac_d.set_label("MAC_D");
   slabel.mac_d.set_alignment(0.0f, 0.5f);
   slabel.mac_d.set_size_request(252, 30);
   slabel.mac_d.override_font(fdsc);

   ///////////////////////////////////////////////////////
   // edit
   EditIpD.setSize(3, 30);
   EditIpD.setIP("192.168.23.10");

   EditIpS.setSize(3, 30);
   EditIpS.setIP("192.168.23.100");
   
   EditMacS.setSize(3, 30);
   EditMacS.setMAC("00","0A","CD","21","5F","A5");
   
   EditMacD.setSize(3, 30);
   EditMacD.setMAC("FF","FF","FF","FF","FF","FF");
   
   EditEthMacS.setSize(3, 30);
   EditEthMacS.setMAC("00","0A","CD","21","5F","A5");
   
   EditEthMacD.setSize(3, 30);
   EditEthMacD.setMAC("FF","FF","FF","FF","FF","FF");
   
   ///////////////////////////////////////////////////////
   // layout
   m_layout.put(sbutton.send,      94,  0);
   
   m_layout.put(scombo.interface,  10,  0);
   m_layout.put(scombo.count,     178,  0);
   m_layout.put(scombo.sleep,     302,  0);
   m_layout.put(scombo.type,      396,  0);
   
   m_layout.put(slabel.ip_s,       10,  90);
   m_layout.put(EditIpS.aEdit[0],  10, 120);
   m_layout.put(EditIpS.aEdit[1],  52, 120);
   m_layout.put(EditIpS.aEdit[2],  94, 120);
   m_layout.put(EditIpS.aEdit[3], 136, 120);
   
   m_layout.put(slabel.ip_d,      272,  90);
   m_layout.put(EditIpD.aEdit[0], 272, 120);
   m_layout.put(EditIpD.aEdit[1], 314, 120);
   m_layout.put(EditIpD.aEdit[2], 356, 120);
   m_layout.put(EditIpD.aEdit[3], 398, 120);
   
   m_layout.put(slabel.mac_s,       10, 150);
   m_layout.put(EditMacS.aEdit[0],  10, 180);
   m_layout.put(EditMacS.aEdit[1],  52, 180);
   m_layout.put(EditMacS.aEdit[2],  94, 180);
   m_layout.put(EditMacS.aEdit[3], 136, 180);
   m_layout.put(EditMacS.aEdit[4], 178, 180);
   m_layout.put(EditMacS.aEdit[5], 220, 180);
   
   m_layout.put(slabel.mac_d,      272, 150);
   m_layout.put(EditMacD.aEdit[0], 272, 180);
   m_layout.put(EditMacD.aEdit[1], 314, 180);
   m_layout.put(EditMacD.aEdit[2], 356, 180);
   m_layout.put(EditMacD.aEdit[3], 398, 180);
   m_layout.put(EditMacD.aEdit[4], 440, 180);
   m_layout.put(EditMacD.aEdit[5], 482, 180);
   
   m_layout.put(slabel.mac_eth_s,      10, 30);
   m_layout.put(EditEthMacS.aEdit[0],  10, 60);
   m_layout.put(EditEthMacS.aEdit[1],  52, 60);
   m_layout.put(EditEthMacS.aEdit[2],  94, 60);
   m_layout.put(EditEthMacS.aEdit[3], 136, 60);
   m_layout.put(EditEthMacS.aEdit[4], 178, 60);
   m_layout.put(EditEthMacS.aEdit[5], 220, 60);
   
   m_layout.put(slabel.mac_eth_d,     272, 30);
   m_layout.put(EditEthMacD.aEdit[0], 272, 60);
   m_layout.put(EditEthMacD.aEdit[1], 314, 60);
   m_layout.put(EditEthMacD.aEdit[2], 356, 60);
   m_layout.put(EditEthMacD.aEdit[3], 398, 60);
   m_layout.put(EditEthMacD.aEdit[4], 440, 60);
   m_layout.put(EditEthMacD.aEdit[5], 482, 60);

   add(m_layout);
   
   ////////////////////////
   
   signal_configure_event().connect(sigc::mem_fun(*this, &C_App::on_configure_changed), false);
   
   ////////////////////////
   
   show_all_children();
}
//////////////////////////////////////////////////////////////////////////////////
// [ Destructor ]
//////////////////////////////////////////////////////////////////////////////////
C_App::~C_App(){
  
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_button_send ]
//////////////////////////////////////////////////////////////////////////////////
void C_App::on_button_send(){

   const S_Net_Interface* pSInterface = 0;
   
   pSInterface = CNet.CNInterface.get_pInterface(scombo.interface.get_active_row_number());
   
   if(pSInterface == nullptr){
      cout << "Error get_pInterface:" << scombo.interface.get_active_row_number() << endl;  
      return; 
   }
   
   //////////////////////////////
   
   UCHAR IP_REQUEST[SIZE_IP];
   UCHAR IP_SOURCE[SIZE_IP];
	
   UCHAR MAC_REQUEST[SIZE_MAC];
   UCHAR MAC_SOURCE[SIZE_MAC];
   
   UCHAR MAC_ETH_D[SIZE_MAC];
   UCHAR MAC_ETH_S[SIZE_MAC];
   
   EditEthMacS.getMAC(MAC_ETH_S);
   EditEthMacD.getMAC(MAC_ETH_D);
   
   EditIpS.getIP(IP_SOURCE);
   EditIpD.getIP(IP_REQUEST);
   
   EditMacS.getMAC(MAC_SOURCE);
   EditMacD.getMAC(MAC_REQUEST);
   
   int type = scombo.type.get_active_row_number();

   //////////////////////////////

   S_ArpPacket sArp;
   
   if(type == 0) sArp.Operation = ARP_REQUEST;
   else          
   if(type == 1) sArp.Operation = ARP_RESPONSE;
     
   sArp.pETH_MAC_D = MAC_ETH_D;
   sArp.pETH_MAC_S = MAC_ETH_S;
   
   sArp.pARP_MAC_D = MAC_REQUEST;
   sArp.pARP_MAC_S = MAC_SOURCE;
   
   sArp.pARP_IP_D  = IP_REQUEST;
   sArp.pARP_IP_S  = IP_SOURCE;

   /////////////////////////////////
   
   int cPackets = 0;
   
   type = scombo.count.get_active_row_number();
   
   switch(type){
      case 0: cPackets = 1;    break; 
      case 1: cPackets = 10;   break;
      case 2: cPackets = 100;  break;
      case 3: cPackets = 1000; break;
   }
   
   int cSleep = 0;
   
   type = scombo.sleep.get_active_row_number();
   
   switch(type){
      case 0: cSleep = 1;    break; 
      case 1: cSleep = 10;   break;
      case 2: cSleep = 100;  break;
      case 3: cSleep = 1000; break;
   }
   
   CNet.send(pSInterface, &sArp, cPackets, cSleep);
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_configure_changed ]
//////////////////////////////////////////////////////////////////////////////////
bool C_App::on_configure_changed(GdkEventConfigure* configure_event){
   //m_ScrolledWindow.set_size_request(configure_event->width, configure_event->height - 30);
   return(false);
}
