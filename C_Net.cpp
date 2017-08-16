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
   
   CNRaw.open(pSInterface);
   CNRaw.start(C_NET_ID_ARP, &CA_Arp[0], C_NET_BUFFER);

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
// [ on_arp_data ]
//////////////////////////////////////////////////////////////////////////////////
void C_Net::on_arp_data(int id, int cData){

   if(id == C_NET_ID_ARP){
     
      if(cData < cETHERNET_HEADER + cARP_HEADER) return;

      UCHAR* pBuffer = &CA_Arp[0];
      
      ETHERNET_HEADER* pRCV_ethhdr = (ETHERNET_HEADER*)pBuffer;
      ARP_HEADER*      pRCV_arp    = (ARP_HEADER*)(pBuffer + cETHERNET_HEADER);
   
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
}
