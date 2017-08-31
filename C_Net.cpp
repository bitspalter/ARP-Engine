//////////////////////////////////////////////////////////////////////////////////
// [ Net_Class_Source ]
//////////////////////////////////////////////////////////////////////////////////

#include "C_Net.hpp"

//////////////////////////////////////////////////////////////////////////////////
// [ start ]
//////////////////////////////////////////////////////////////////////////////////
int C_Net::start(){

   if(CNInterface.create() != C_NET_INTERFACE_READY){
      cout << "ERROR: CNInterface.create" << endl;
      return(C_NET_ERROR);
   }

   return(C_NET_READY);
}
//////////////////////////////////////////////////////////////////////////////////
// [ send ]
//////////////////////////////////////////////////////////////////////////////////
int C_Net::send(const S_Net_Interface* pSInterface, S_ArpPacket* pSArp, int cPackets, int cSleep){
  
   if(!pSInterface || !pSArp || !cPackets) return(C_NET_ERROR);

   UCHAR  pData[5000];
   DWORD  cData = 0;
   
   CNArp.getPacket(pData, &cData, pSArp);
   
   CNRaw.open(pSInterface, this);
   CNRaw.start(&CA_Arp[0], C_NET_BUFFER, &this->cData);

   usleep(50000);
   
   for(int n = 0; n < cPackets; n++){
      CNRaw.send(pData, cData);
      usleep(cSleep * 1000);
   }
  
   usleep(50000);
  
   CNRaw.stop();
   CNRaw.close();
  
   return(C_NET_READY);
}
//////////////////////////////////////////////////////////////////////////////////
// [ notify ]
//////////////////////////////////////////////////////////////////////////////////
void C_Net::notify(){
   m_Dispatcher.emit();
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_data ]
//////////////////////////////////////////////////////////////////////////////////
void C_Net::on_data(){

   if(cData < (int)(cETHERNET_HEADER + cARP_HEADER)) return;

   {
      lock_guard<mutex> lock(m_Mutex);
      if(cData < C_NET_BUFFER) memcpy(&CA_Buffer[0], &CA_Arp[0], cData);
      else return;
   }
      
   ETHERNET_HEADER* pRCV_ethhdr = (ETHERNET_HEADER*)&CA_Buffer[0];
   ARP_HEADER*      pRCV_arp    = (ARP_HEADER*)(&CA_Buffer[cETHERNET_HEADER]);
   
   if(pRCV_ethhdr->Type == ETH_TYP_ARP){

      if(pRCV_arp->ARP_OpCode == ARP_REQUEST){
         cout << "ARP_REQUEST" << endl;
      }else
      if(pRCV_arp->ARP_OpCode == ARP_RESPONSE){
         cout << "ARP_RESPONSE" << endl;
      }

      cout << "IP:" << dec 
           << (int)pRCV_arp->ARP_IP_S[0] << "." << (int)pRCV_arp->ARP_IP_S[1] << "." 
           << (int)pRCV_arp->ARP_IP_S[2] << "." << (int)pRCV_arp->ARP_IP_S[3] << endl;
  
      cout << "MAC:" << hex 
           << setfill('0') << setw(2) << (int)pRCV_arp->ARP_MAC_S[0] << ":"
           << setfill('0') << setw(2) << (int)pRCV_arp->ARP_MAC_S[1] << ":" 
           << setfill('0') << setw(2) << (int)pRCV_arp->ARP_MAC_S[2] << ":"
           << setfill('0') << setw(2) << (int)pRCV_arp->ARP_MAC_S[3] << ":" 
           << setfill('0') << setw(2) << (int)pRCV_arp->ARP_MAC_S[4] << ":" 
           << setfill('0') << setw(2) << (int)pRCV_arp->ARP_MAC_S[5] << endl;
   }
}
